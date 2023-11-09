package org.example;


import org.example.io.Keyboard;
import org.example.io.Mouse;
import org.example.models.RawModel;
import org.example.models.TexturedModel;
import org.example.renderEngine.DisplayManager;
import org.example.renderEngine.Loader;
import org.example.renderEngine.Renderer;
import org.example.shaders.StaticShader;
import org.example.texture.ModelTexture;
import org.lwjgl.glfw.GLFW;
import org.lwjgl.opengl.GL11;


public class App {

    public static void main(String[] arg) {

        DisplayManager.createDisplay();

        Loader loader = new Loader(); // загрузчик моделей
        Renderer renderer = new Renderer(); // визуализатор моделей
        StaticShader shader = new StaticShader(); // шейдер статических моделей

        float[] vertices = {
                0.0f, 0.5f, 0f, // V0
                -0.5f, -0.5f, 0f, // V1
                0.5f, -0.5f, 0f, // V2
            //    0.5f, 0.5f, 0f, // V3
        };

        int[] indices = {
                0, 1, 2, // Верхний левый треугольник
             //   3, 1, 2, // Нижний правый треугольник
        };

        float[] textureCoords = {
                0.5f, 0.5f, // V0
                0.8f, 0.0f, // V1
                0.0f, 0.0f, // V2
              //  1.0f, 0.0f, // V3
        };

        // загружаем массив вершин, текстурных координат и индексов в память GPU
        RawModel model = loader.loadToVao(vertices, textureCoords, indices);
        ModelTexture texture = new ModelTexture(loader.loadTexture("res/brickWall.png",false));
        // Создание текстурной модели
        TexturedModel texturedModel = new TexturedModel(model, texture);

        // запускаем цикл пока пользователь не закроет окно
        while (DisplayManager.shouldDisplayClose()) {
            boolean m= Mouse.isButtonDown(GLFW.GLFW_MOUSE_BUTTON_LEFT);
            boolean k=Keyboard.isKeyDown(GLFW.GLFW_KEY_A);
            System.out.println(m);
            if(Keyboard.isKeyDown(GLFW.GLFW_KEY_A)){

                // загрузим текстуру используя загрузчик
                GL11.glClear(GL11.GL_CLEAR); // Очистка экрана и рисование цветом в цветовом буфере
                GL11.glClearColor(0.0f, 1.0f, 0.5f, 1); // Загрузка выбранного цвета в цветовой буфер
            }
              //  entity.increacePosition(-0.1f, 0, 0);
            else if(Keyboard.isKeyDown(GLFW.GLFW_KEY_D)){
                // загрузим текстуру используя загрузчик
                 texture = new ModelTexture(loader.loadTexture("res/brickWall.png",true));
                // Создание текстурной модели
                texturedModel = new TexturedModel(model, texture);
            }
              //  entity.increacePosition(0.1f, 0, 0);

            if(!Keyboard.isKeyDown(GLFW.GLFW_KEY_A))
                renderer.prepare(); // подготовка окна для рисования кадра

            shader.start(); // запускаем шейдер статических моделей
            renderer.render(texturedModel); // рисуем модель
            shader.stop(); // останавливаем шейдер статических моделей

            DisplayManager.updateDisplay();
        }

        shader.cleanUp(); // очищаем шейдер статических моделей
        loader.cleanUp(); // очищаем память от загруженной модели
        DisplayManager.closeDisplay();
    }


}