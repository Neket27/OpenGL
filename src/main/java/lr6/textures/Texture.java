package lr6.textures;

import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL30;
import org.lwjgl.stb.STBImage;
import org.lwjgl.system.MemoryStack;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL11C.glTexParameteri;
import static org.lwjgl.opengl.GL43.GL_TEXTURE_2D;

public class Texture {

    private final int id;

    public Texture(int id) {
        this.id = id;

    }

    public Texture(String fileName, boolean bilinearFilteringWithMipMapOverlay)throws Exception{
        //this.id=loadTexture(fileName) или как сделано, создаём объект исполььзуя конструктор выше через this
        this(loadTexture(fileName,bilinearFilteringWithMipMapOverlay));
    }

    private static int loadTexture(String fileName, boolean bilinearFilteringWithMipMapOverlay)throws Exception{
        int width, height;
        // Будет содержать декодированное изображение (так как каждый пиксель
        // использует четыре байта, его размер будет 4 ширины по высоте)
        ByteBuffer buf;

        // Загрузка файла текстуры
        try(MemoryStack stack=MemoryStack.stackPush()) {
            IntBuffer w = stack.mallocInt(1);
            IntBuffer h = stack.mallocInt(1);
            IntBuffer channels = stack.mallocInt(1);

            buf = STBImage.stbi_load(fileName, w, h, channels, 4);
            if (buf == null)
                throw new Exception("Файл текстуры [" + fileName + "] не загружен: " + STBImage.stbi_failure_reason());
            // получение высоты и ширины картинки
            width = w.get();
            height = h.get();
        }
        //создание новой текстуры
        int texturedId= GL11.glGenTextures();
        // присоединяем текстуру
        GL11.glBindTexture(GL11.GL_TEXTURE_2D,texturedId);

        // Говорит OpenGL, как распаковать байты RGBA. Каждый компонент имеет размер 1 байт.
        GL11.glBindTexture(GL11.GL_UNPACK_ALIGNMENT,1);

        // Этот параметр в основном говорит о том, что когда пиксель рисуется
        // без прямой связи один к одному с координатой текстуры, он выбирает
        // ближайшую точку текстуры.
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//        if(!bilinearFilteringWithMipMapOverlay)
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//        else
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // уровень детализации текстуры
        //  GL11.glTexParameterf(GL11.GL_TEXTURE_2D, GL14.GL_TEXTURE_LOD_BIAS, 0.5f);

        // Выгрузка данных текстуры
        // [1] GL_TEXTURE_2D - Определяет целевую текстуру (ее тип)
        // [2] level - указывает номер уровня детализации. Уровень 0 - это базовый уровень изображения. Уровень n - это n-е уменьшенное изображение mipmap
        // [3] internal format - Определяет количество цветовых компонентов в текстуре.
        // [4] width - Определяет ширину текстурного изображения
        // [5] height - Определяет высоту текстурного изображения
        // [6] border - Это значение должно быть нулевым
        // [7] format - Определяет формат данных пикселей: в данном случае RGBA.
        // [8] type - Определяет тип данных данных пикселей. Для этого мы используем неподписанные байты.
        // [9] data - Буфер, в котором хранятся наши данные
        GL11.glTexImage2D(GL11.GL_TEXTURE_2D, 0, GL11.GL_RGBA, width, height, 0,
                GL11.GL_RGBA, GL11.GL_UNSIGNED_BYTE, buf);

        // Генерация Мип-карта
        // Мип-карта - это набор изображений с уменьшенным разрешением,
        // созданный из высокодетализированной текстуры. Эти изображения с
        // более низким разрешением будут использоваться автоматически при
        // масштабировании нашего объекта.
        GL30.glGenerateMipmap(GL11.GL_TEXTURE_2D);

        // освобождаем буфер
        STBImage.stbi_image_free(buf);
        return texturedId;
    }

    public void cleanup(){
        GL11.glDeleteTextures(id);
    }

    public int getId(){
        return id;
    }

}
