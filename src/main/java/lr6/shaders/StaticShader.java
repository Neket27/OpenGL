package lr6.shaders;

import lr6.entities.Camera;
import lr6.entities.Light;
import lr6.toolbox.Maths;
import org.joml.Matrix4f;
import org.joml.Vector3f;
import org.joml.Vector4f;

/**
 * Шейдер для создания всех статических моделей
 */
public class StaticShader extends ShaderProgram {

    // указываем пути в константы для загрузки шейдеров
    private static final String VERTEX_FILE = "src/main/java/lr6/shaders/vertexShader.txt";
    private static final String FRAGMENT_FILE = "src/main/java/lr6/shaders/fragmentShader.txt";

    // идентификатор юниформы матрицы трансформации
    private int location_transformationMatrix;
    // идентификатор юниформы матрицы проекции
    private int location_projectionMatrix;
    // идентификатор юниформы матрицы вида
    private int location_viewMatrix;

    private int location_lightPosition; // позиция источника света
    private int location_lightColour; // цвет источника света

    private int location_shineDamper; // коэффициент блеска материала
    private int location_reflectivity; // отражательная способность материала
    private int location_backgroundColour; // фоновый цвет

    public StaticShader() {
        super(VERTEX_FILE, FRAGMENT_FILE);
    }

    @Override
    protected void bindAttributes() {
        // связываем списки атрибутов VAO с шейдером
        super.bindAttribute(0, "position");
        super.bindAttribute(1, "textureCoords");
        super.bindAttribute(2, "normal");
    }

    @Override
    protected void getAllUniformLocations() {
        // регестрируем юниформы
        location_transformationMatrix = super.getUniformLocation("transformationMatrix");
        location_projectionMatrix = super.getUniformLocation("projectionMatrix");
        location_viewMatrix = super.getUniformLocation("viewMatrix");
        location_lightPosition = super.getUniformLocation("lightPosition");
        location_lightColour = super.getUniformLocation("lightColour");
        location_shineDamper = super.getUniformLocation("shineDamper");
        location_reflectivity = super.getUniformLocation("reflectivity");
        location_backgroundColour = super.getUniformLocation("backgroundColour");
    }

    /**
     * Загрузка позиции и цвета источника света, в юниформу
     * @param light источник света
     */
    public void loadLight(Light light) {
        super.loadVector(location_lightPosition, light.getPosition());
        super.loadVector(location_lightColour, light.getColour());
                                                            // фоновый цвет
        super.loadVector(location_backgroundColour,new Vector3f(1.0f, 0.0f, 1.0f));
    }

    /**
     * Загрузка данных, матрицы трансформации, в юниформу
     * @param matrix матрица преобразования
     */
    public void loadTransformationMatrix(Matrix4f matrix) {
        super.loadMatrix(location_transformationMatrix, matrix);
    }

    /**
     * Загрузка данных, матрицы вида, в юниформу
     * @param camera камера
     */
    public void loadViewMatrix(Camera camera) {
        Matrix4f viewMatrix = Maths.createViewMatrix(camera);
        super.loadMatrix(location_viewMatrix, viewMatrix);
    }

    /**
     * Загрузка данных, матрицы проекции, в юниформу
     * @param matrix матрица проекции
     */
    public void loadProjectionMatrix(Matrix4f matrix) {
        super.loadMatrix(location_projectionMatrix, matrix);
    }

    /**
     * Загрузка переменных блеска/отражения
     * @param damper коэффициент блеска материала
     * @param reflectivity отражательная способность материала
     */
    public void loadShineVariables(float damper, float reflectivity) {
        super.loadFloat(location_shineDamper, damper);
        super.loadFloat(location_reflectivity, reflectivity);
    }
}

