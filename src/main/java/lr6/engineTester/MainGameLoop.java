 package lr6.engineTester;


 import lr6.Primitives.Sphere;
 import lr6.entities.Entity;
 import lr6.io.Keyboard;
 import lr6.io.Mouse;
 import lr6.models.RawModel;
 import lr6.models.TexturedModel;
 import lr6.renderEngine.DisplayManager;
 import lr6.renderEngine.Loader;
 import lr6.renderEngine.Renderer;
 import lr6.shaders.StaticShader;
 import lr6.textures.ModelTexture;
 import org.joml.Vector3f;
 import org.lwjgl.glfw.GLFW;

 import java.util.ArrayList;
 import java.util.List;

 /**
 * Основной цикл игры
 */
public class MainGameLoop {

    public static void main(String[] args) {

 Sphere sphere= new Sphere(1.0f, 20, 20);



        DisplayManager.createDisplay();
        
        Loader loader = new Loader(); // загрузчик моделей
        Renderer renderer = new Renderer(); // визуализатор моделей
        StaticShader shader = new StaticShader(); // шейдер статических моделей

        float[] vertices = {
                0.0f, 0.5f, -0.4f, // V0
                -0.5f, -0.5f, -0.5f, // V1
                0.5f, -0.5f, -0.5f, // V2
               //  0.0f, -1.0f, 0f, // V1
        };

        int[] indices = {
                0, 1, 2,
             //   2,3,0

        };

        float[] textureCoords = {
                0.5f, 0.5f, // V0
                0.8f, 0.0f, // V1
                0.0f, 0.0f, // V2
            //    0.7f, 0.1f, // V0
        };

        List<Integer> indices2 =new ArrayList<>();
        List<Float> vertices2 = new ArrayList<>();
        List<Float> textureCoords2 =new ArrayList<>();
        List<Float> outNormals =new ArrayList<>();


        int[] indices22 = indices2.stream().mapToInt(i->i).toArray();

        float[] vertices22= new float[vertices2.size()];
        for(int i=0; i<vertices2.size();i++)
            vertices22[i] = vertices2.get(i);

        float[] textureCoords22 = new float[textureCoords2.size()];
        for (int i=0; i<textureCoords2.size();i++)
            textureCoords22[i]=textureCoords2.get(i);

       // Float[] outNormals22 =(Float[]) outNormals.toArray();

        // загружаем массив вершин, текстурных координат и индексов в память GPU
     //   RawModel model = loader.loadToVao(vertices, textureCoords, indices);
        RawModel model = loader.loadToVao(sphere.getVertices(), sphere.getTextureCoords(), sphere.getIndices());

        // загрузим текстуру используя загрузчик
        ModelTexture texture = new ModelTexture(loader.loadTexture("res/brickWall.png",false));
        // Создание текстурной модели
        TexturedModel staticModel = new TexturedModel(model, texture);
        
        Entity entity = new Entity(staticModel,
                new Vector3f(0.0f, 0, 0),
                0, 0, 0,
                1.0f);


        
        // запускаем цикл пока пользователь не закроет окно
        while (DisplayManager.shouldDisplayClose()) {
            if(Keyboard.isKeyDown(GLFW.GLFW_KEY_A))
                entity.increacePosition(-0.1f, 0, 0);
            else if(Keyboard.isKeyDown(GLFW.GLFW_KEY_D))
                entity.increacePosition(0.1f, 0, 0);
            if (Mouse.isButtonDown(GLFW.GLFW_MOUSE_BUTTON_LEFT))
                entity.increaseRotation(0, 0, 1);
            else if (Mouse.isButtonDown(GLFW.GLFW_MOUSE_BUTTON_RIGHT))
                entity.increaseRotation(0, 0, -1);

            renderer.prepare(); // подготовка окна для рисования кадра

            shader.start(); // запускаем шейдер статических моделей
            renderer.render(entity, shader); // рисуем объект
            shader.stop(); // останавливаем шейдер статических моделей

            DisplayManager.updateDisplay();
            }

        
        shader.cleanUp(); // очищаем шейдер статических моделей
        loader.cleanUp(); // очищаем память от загруженной модели
        DisplayManager.closeDisplay();
    }




 }
