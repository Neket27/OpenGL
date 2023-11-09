 package lr7.engineTester;


 import lr7.models.RawModel;
 import org.joml.Vector3f;
 import org.lwjgl.glfw.GLFW;
 import lr7.entities.Entity;
 import lr7.io.Keyboard;
 import lr7.models.TexturedModel;
 import lr7.renderEngine.DisplayManager;
 import lr7.renderEngine.Loader;
 import lr7.renderEngine.Renderer;
 import lr7.shaders.StaticShader;
 import lr7.textures.ModelTexture;

/**
 * Основной цикл игры
 */
public class MainGameLoop {

    public static void main(String[] args) {
        DisplayManager.createDisplay();
        
        Loader loader = new Loader(); // загрузчик моделей
        Renderer renderer = new Renderer(); // визуализатор моделей
        StaticShader shader = new StaticShader(); // шейдер статических моделей

        float[] vertices = {
                0.0f, 0.5f, 0f, // V0
                -0.5f, -0.5f, 0f, // V1
                0.5f, -0.5f, 0f, // V2
        };

        int[] indices = {
                0, 1, 2,

        };

        float[] textureCoords = {
                0.5f, 0.5f, // V0
                0.8f, 0.0f, // V1
                0.0f, 0.0f, // V2
        };
        
        // загружаем массив вершин, текстурных координат и индексов в память GPU
     //   RawModel model = loader.loadToVao(vertices, textureCoords, indices);
        RawModel model = loader.loadToVao(vertices, textureCoords, indices);
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
            if(Keyboard.isKeyDown(GLFW.GLFW_KEY_A)) {
               // System.out.println(Keyboard.isKeyDown(GLFW.GLFW_KEY_A));
                texture = new ModelTexture(loader.loadTexture("res/brickWall.png",true));
                staticModel = new TexturedModel(model, texture);
                entity = new Entity(staticModel,
                        new Vector3f(0, 0, 0),
                        0, 0, 0,
                        1.0f);
            }
               // entity.increacePosition(-0.1f, 0, 0);
//            else if(Keyboard.isKeyDown(GLFW.GLFW_KEY_D))
//            //    entity.increacePosition(0.1f, 0, 0);
//            if (Mouse.isButtonDown(GLFW.GLFW_MOUSE_BUTTON_LEFT))
//             //   entity.increaseRotation(0, 0, 1);
//            else if (Mouse.isButtonDown(GLFW.GLFW_MOUSE_BUTTON_RIGHT))
//             //   entity.increaseRotation(0, 0, -1);

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
