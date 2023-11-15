package lr6.renderEngine;

import lr6.textures.Texture;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;
import lr6.models.RawModel;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

public class Loader {
    private List<Integer> vaos = new ArrayList<>();
    private List<Integer> vbos = new ArrayList<>();
    private List<Integer> textures = new ArrayList<>();


    public RawModel loadToVao(float[] positions, float[] textureCoords,float[] normals, int[] indices){
        int vaoId= createVao();
        bindIndicesBuffer(indices);
        storeDataInAttributeList(0, 3, positions);
        storeDataInAttributeList(1, 2, textureCoords);
        // VAO #2 имеет 3х мерные Векторы(xyz), векторы нормали
        storeDataInAttributeList(2, 3, normals);

        unbindVao(); // отвязываем VAO
        // возвращаем загруженную модель: id и количество вершин
        return new RawModel(vaoId,indices.length);
    }

    private void unbindVao() {
        GL30.glBindVertexArray(0);
    }
    private void storeDataInAttributeList(int attributeNumber, int coordinateSize, float[] data) {
        int vboId = GL15.glGenBuffers(); // инициализация пустого VBO
        vbos.add(vboId); // добавляем в список очередной идентификатор VBO
        // Указываем OpenGL, что сейчас мы будем что-то делать вот с этим VBO
        // для этого используем точку связывания GL_ARRAY_BUFFER
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboId);
        // Создаем FloatBuffer наших данных
        FloatBuffer buffer = storeDataInFloatBuffer(data);
        // Выделяем память GPU и загружаем в нее наши данные
        // STATIC говорит о том, что мы не собираемся модифицировать данные,
        // а DRAW — о том, что данные будут использованы для отрисовки чего-то
        GL15.glBufferData(GL15.GL_ARRAY_BUFFER, buffer, GL15.GL_STATIC_DRAW);
        // Откуда брать данные для массива атрибутов, а также в каком формате эти данные находятся
        // Аргументы:
        // - номер списка атрибутов VAO
        // - размер компонента (для вершины нужно 3(xyz), для тектурной координаты 2(uv))
        // - тип компонента
        // - остальные normalized, stride и pointer
        GL20.glVertexAttribPointer(attributeNumber, coordinateSize, GL11.GL_FLOAT, false, 0, 0);
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, 0); // отвязываем VBO
    }


    private void bindIndicesBuffer(int[] indices) {
        int vboId= GL15.glGenBuffers();
        vbos.add(vboId);
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER,vboId);
        IntBuffer buffer= storeDataIntBuffer(indices);
        GL15.glBufferData(GL15.GL_ELEMENT_ARRAY_BUFFER,buffer, GL15.GL_STATIC_DRAW);
    }

    private FloatBuffer storeDataInFloatBuffer(float[] data) {
        FloatBuffer buffer = BufferUtils.createFloatBuffer(data.length);
        buffer.put(data).flip();
        return buffer;
    }

    private IntBuffer storeDataIntBuffer(int[] indices) {
        IntBuffer buffer = BufferUtils.createIntBuffer(indices.length);
        buffer.put(indices).flip();
        return buffer;
    }

    private int createVao() {
        int vaoId = GL30.glGenVertexArrays(); // инициализация пустого VAO
        vaos.add(vaoId); // добавляем в список очередной идентификатор VAO
        GL30.glBindVertexArray(vaoId); // связываем vao по id c OpenGL
        return vaoId;
    }

    public int loadTexture(String fileName,boolean bilinearFilteringWithMipMapOverlay) {
        int textureId = 0;
        try {
            Texture texture = new Texture(fileName,bilinearFilteringWithMipMapOverlay);
            textureId = texture.getId();
            textures.add(textureId);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return textureId;
    }


    public void cleanUp() {
        for (int vaoId : vaos)
            GL30.glDeleteVertexArrays(vaoId);
        for (int vboId : vbos)
            GL15.glDeleteBuffers(vboId);
        for (int texture : textures)
            GL11.glDeleteTextures(texture);
    }

}