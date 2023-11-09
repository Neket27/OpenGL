package org.example.shaders;

import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL20;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 * Общая шейдерная программа содержащая все атрибуты и методы, которые
 * каждый шейдер будет иметь
 */
public abstract class ShaderProgram {

    /** идентификатор программы */
    private int programId;
    /** идентификатор вершинного шейдера */
    private int vertexShaderId;
    /** идентификатор фрагментного шейдера */
    private int fragmentShaderId;

    /**
     * Конструктор шейдерной программы
     * @param vertexFile путь к файлу вершинного шейдера
     * @param fragmentFile путь к файлу фрагментного шейдера
     */
    public ShaderProgram(String vertexFile,String fragmentFile) {
        // загрузка шейдеров в OpenGL
        vertexShaderId = loadShader(vertexFile, GL20.GL_VERTEX_SHADER);
        fragmentShaderId = loadShader(fragmentFile, GL20.GL_FRAGMENT_SHADER);
        
        // создание шейдерной программы
        programId = GL20.glCreateProgram(); // инициализация шейдерной программы
        if (programId == 0)
            throw new RuntimeException("Немогу создать шейдер");
        
        // связываем шейдеры с программой
        GL20.glAttachShader(programId, vertexShaderId);
        GL20.glAttachShader(programId, fragmentShaderId);
        
        bindAttributes();
        
        // присоединяем шейдерную программу
        GL20.glLinkProgram(programId);
        if(GL20.glGetProgrami(programId, GL20.GL_LINK_STATUS) == GL11.GL_FALSE)
            throw new RuntimeException("Ошибка присоединения шейдерной программы: " + GL20.glGetProgramInfoLog(programId, 1024));
        
        // проверяем шейдерную программу
        GL20.glValidateProgram(programId);
        if(GL20.glGetProgrami(programId, GL20.GL_VALIDATE_STATUS) == GL11.GL_FALSE)
            System.err.println("Ошибка проверки шейдерной программы: " + GL20.glGetProgramInfoLog(programId, 1024));
    }
    
    /**
     * Подключение атрибутов
     */
    protected abstract void bindAttributes();
    
    /**
     * Связывание атрибута с программой
     * @param attributeNumber номер списка атрибута в VAO
     * @param variableName наименование переменной
     */
    protected void bindAttribute(int attributeNumber, String variableName) {
        GL20.glBindAttribLocation(programId, attributeNumber, variableName);
    }
    
    /**
     * Метод загрузки и компиляция шейдера в OpenGL в зависимости от типа
     * @param file путь к файлу
     * @param type тип шейдера
     * @return идентификатор созданного шейдера
     */
    private static int loadShader(String file, int type) {
        StringBuilder shaderSource = new StringBuilder();
	try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;
            while((line = reader.readLine()) != null) {
		shaderSource.append(line).append("//\n");
            }
            reader.close();
	} catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
	}
        // инициализируем шейдер определенного типа
	int shaderID = GL20.glCreateShader(type); 
        if (shaderID == 0)
            throw new RuntimeException("Ошибка создания шейдера. Тип: " + type);
        // загружаем в шейдер исходный код
	GL20.glShaderSource(shaderID, shaderSource);
        // компилируем шейдерный код
	GL20.glCompileShader(shaderID);
	if (GL20.glGetShaderi(shaderID, GL20.GL_COMPILE_STATUS) == GL11.GL_FALSE)
            throw new RuntimeException("Ошибка компиляции шейдерной программы: " + GL20.glGetShaderInfoLog(shaderID, 1024));
	return shaderID;
    }
    
    /**
     * Запуск шейдерной программы.
     */
    public void start() {
        GL20.glUseProgram(programId);
    }
    
    /**
     * Прекращение использования программы
     */
    public void stop() {
        GL20.glUseProgram(0);
    }
    
    /**
     * Очистка и освобождение ресурсов
     */
    public void cleanUp() {
        stop(); // остановка программы
        // отсоединяем от программы и удаляем шейдеры 
        if(vertexShaderId != 0) {
            GL20.glDetachShader(programId, vertexShaderId);
            GL20.glDeleteShader(vertexShaderId);
        }
        if(fragmentShaderId != 0) {
            GL20.glDetachShader(programId, fragmentShaderId);
            GL20.glDeleteShader(fragmentShaderId);
        }
        // освобождение ресурсов программы
        if(programId != 0)
            GL20.glDeleteProgram(programId);  
    }
}
