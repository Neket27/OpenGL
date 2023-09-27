#include "ShaderFuncs.h"
#include <fstream>
#include <vector>
GLuint LoadShader(std::string filename, GLenum type)
{
	std::ifstream fin;
	fin.open(filename);
	if (fin) {
		std::string textshader;
		char c= fin.get();
		while (c!=-1) {
			textshader += c;
			c = fin.get();
		}
		fin.close();
		GLuint s = glCreateShader(type);
		char* buf = new GLchar[textshader.length() + 1];
		strcpy_s(buf, textshader.length()+1 , textshader.c_str());
		glShaderSource(s, 1, &buf, NULL);
		glCompileShader(s);
		GLint isCompiled = 0;
		glGetShaderiv(s, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(s, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(s, maxLength, &maxLength, &errorLog[0]);
			for (GLchar c : errorLog)
				std::cout << c;
		}
		delete[] buf;
		return s;
	}
	else {
		std::cout << "ERROR: No such file";
		return -1;
	}
}
