#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

using namespace std;

Shader::Shader(const string &vertex, const string &fragment){
    string shaderStr = getFile(vertex);
	const GLchar *vShaderSrc = shaderStr.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vShaderSrc, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Filename:" << vertex << "\n";
		cout << "vertex shader compilation failed\n" << infoLog << endl;
        exit(1);
	}

    shaderStr = getFile(fragment);
	const GLchar *fShaderSrc = shaderStr.c_str();

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "Filename:" << fragment << "\n";
		cout << "fragment shader compilation failed\n" << infoLog << endl;
        exit(1);
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout << "shader linking failed\n" << infoLog << endl;
        exit(1);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const string &vertex, const string &fragment, const string &geometry){
    //
    string shaderStr = getFile(vertex);
	const GLchar *vShaderSrc = shaderStr.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vShaderSrc, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Filename:" << vertex << "\n";
		cout << "vertex shader compilation failed\n" << infoLog << endl;
        exit(1);
	}
    //
    shaderStr = getFile(fragment);
	const GLchar *fShaderSrc = shaderStr.c_str();

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "Filename:" << fragment << "\n";
		cout << "fragment shader compilation failed\n" << infoLog << endl;
        exit(1);
	}
    //
    shaderStr = getFile(geometry);
	const GLchar *gShaderSrc = shaderStr.c_str();

	GLuint geometryShader;
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &gShaderSrc, NULL);
	glCompileShader(geometryShader);

	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
        cout << "Filename:" << geometry << "\n";
		cout << "geometry shader compilation failed\n" << infoLog << endl;
        exit(1);
	}
    //

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glAttachShader(program, geometryShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout << "shader linking failed\n" << infoLog << endl;
        exit(1);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}

Shader::~Shader(){
	glDeleteProgram(program);
}

void Shader::use() const {
    glUseProgram(program);
}

GLuint Shader::getLocation() const {
	return program;
}

string Shader::getFile(const string &filename){
	ifstream in(filename, ios::in | ios::binary);
	if(in){
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		return(contents.str());
	}
    cerr << "Unable to open file: " << filename << endl;
    exit(1);
}
