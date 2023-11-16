 package lr6.engineTester;


 import lr6.entities.Camera;
 import lr6.entities.Entity;
 import lr6.entities.Light;
 import lr6.models.RawModel;
 import lr6.models.TexturedModel;
 import lr6.primitives.Sphere;
 import lr6.renderEngine.DisplayManager;
 import lr6.renderEngine.Loader;
 import lr6.renderEngine.MasterRenderer;
 import lr6.renderEngine.Renderer;
 import lr6.shaders.StaticShader;
 import lr6.textures.ModelTexture;
 import org.joml.Vector3f;

 import java.util.ArrayList;
 import java.util.List;

 /**
 * Основной цикл игры
 */
public class MainGameLoop {

    public static void main(String[] args) {
        DisplayManager.createDisplay();
        
        Loader loader = new Loader(); // загрузчик моделей
        StaticShader shader = new StaticShader(); // шейдер статических моделей
       // Renderer renderer = new Renderer(shader); // визуализатор моделей

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



        Sphere sphere= new Sphere(3.4f, 100, 100);

        // загружаем массив вершин, текстурных координат и индексов в память GPU
     //   RawModel model = loader.loadToVao(vertices, textureCoords, indices);
        RawModel model = loader.loadToVao(sphere.getVertices(), sphere.getTextureCoords(),sphere.getNormalsArray() ,sphere.getIndices());
        // загружаем модель в память OpenGL
       // RawModel model = OBJLoader.loadObjModel("res/tutorial11/dragon.obj", loader);


        // загрузим текстуру используя загрузчик
        ModelTexture texture = new ModelTexture(loader.loadTexture("res/tutorial11/dragon.png",false));
        ModelTexture texture2 = new ModelTexture(loader.loadTexture("res/tutorial11/dragon.png",false));
        // Создание текстурной модели
        TexturedModel staticModel = new TexturedModel(model, texture);

        Entity entity = new Entity(staticModel,
                new Vector3f(8, 3.8f, -1.7f),
                0, 0, 0,
                1.0f);

        Entity entity2 = new Entity(staticModel,
                new Vector3f(-8, 3.8f, -1.7f),
                0, 0, 0,
                1.0f);

        texture.setShineDamper(0.2f); // коэффицент юлеска материала
        texture.setReflectivity(0.2f);// отражающая способность от 0 до 1
        texture2.setShineDamper(10); // коэффицент юлеска материала
        texture2.setReflectivity(1);// отражающая способность от 0 до 1

        Camera camera = new Camera(0,0,20);
        // создание источника света
       // Light light = new Light(new Vector3f(0, 10, -20), new Vector3f(1.0f, 1, 1.0f));
        Light light = new Light(new Vector3f(0.2f, 0.7f, 0.1f), new Vector3f(1.0f, 0.0f, 1.0f));
        Light light2 = new Light(new Vector3f(-5f, 10f, 12.0f), new Vector3f(1.0f, 0.0f, 1.0f));
        List<Entity> allBox = new ArrayList<>();
        allBox.add(entity);
        allBox.add(entity2);

// запускаем цикл пока пользователь не закроет окно
        MasterRenderer renderer = new MasterRenderer();
        // запускаем цикл пока пользователь не закроет окно
        while (DisplayManager.shouldDisplayClose()) {
          //  entity.increaseRotation(0, 1, 0);
          //  entity2.increaseRotation(0, -1, 0);
            camera.move(); // двигаем камеру
            // рисуем объекты
            for (Entity box : allBox) {
                box.increaseRotation(0, 1, 0);
                renderer.processEntity(box);
            }
            renderer.render(light, camera);
        }

        shader.cleanUp(); // очищаем шейдер статических моделей
        loader.cleanUp(); // очищаем память от загруженной модели
        DisplayManager.closeDisplay();
    }




 }
