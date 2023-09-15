#ifndef SHADERS_H
#define SHADERS_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#include"EngineCore.hpp"

GLuint Shaders::LoadShaders(std::string vertex_file, std::string fragment_file) {
    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    GLuint frgamentID = glCreateShader(GL_FRAGMENT_SHADER);

    // vertex code
    std::string vertexCode;

    std::ifstream vertexStream(vertex_file, std::ios::in);
    
    if(vertexStream.is_open()) {
        std::stringstream sstr;
        sstr << vertexStream.rdbuf();

        vertexCode = sstr.str();
        vertexStream.close();
    } else {
        std::cerr << "Could not open vertex file. " << std::endl;
        exit(EXIT_FAILURE);
    }

    // fragment code
    std::string fragmentCode;

    std::ifstream fragmentStream(fragment_file, std::ios::in);
    
    if(fragmentStream.is_open()) {
        std::stringstream sstr;
        sstr << fragmentStream.rdbuf();

        fragmentCode = sstr.str();
        fragmentStream.close();
    } else {
        std::cerr << "Could not open fragment file. " << std::endl;
        exit(EXIT_FAILURE);
    }


    // requiring gpu slots
	GLuint program = glCreateProgram();
	// GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	// GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// associating shader sources with glsl code
    char const * vPointer = vertexCode.c_str();
    char const * fPointer = fragmentCode.c_str();
	glShaderSource(vertexID, 1, &vPointer, NULL);
	glShaderSource(frgamentID, 1, &fPointer, NULL);

	glCompileShader(vertexID); // compiling

	// error handling
	GLint isCompiled = 0;

	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		int infoLength = 512;
		glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &infoLength);

		char info[infoLength];
		glGetShaderInfoLog(vertexID, infoLength, NULL, info);

		std::cerr << "Error compiling vertex. " << info << std::endl;          
	}
	glCompileShader(frgamentID);

    isCompiled = 0;
    glGetShaderiv(frgamentID, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        // log length
        int infoLength = 512;
        glGetShaderiv(frgamentID, GL_INFO_LOG_LENGTH, &infoLength);

        // retriebing
        char info[infoLength];                                        
        glGetShaderInfoLog(frgamentID, infoLength, NULL, info);         
                                                                      
        std::cerr << "Error compiling shader. " << info << std::endl;          
                                                                      
    }                 

	// associating the created programns to main code
	glAttachShader(program, vertexID);
	glAttachShader(program, frgamentID);

	// linking
	glLinkProgram(program);
	// glUseProgram(program);


    // Check the program (snippet from : https://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/)
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	glDetachShader(program, vertexID);
	glDetachShader(program, frgamentID);
	
	glDeleteShader(vertexID);
	glDeleteShader(frgamentID);

	return program;
}


#endif