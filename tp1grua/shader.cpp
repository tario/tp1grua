#include "stdafx.h"
#include "shader.h"
#include <iostream>
#include <fstream>


glm::mat4 Shader::projectionMatrix;
glm::vec3 Shader::cameraDirection;
glm::vec3 Shader::cameraPosition;
	// carga un programa dadas las rutas del shader de fragmento y shader de vertices
Shader::Shader(std::string fragmentShader, std::string vertexShader) {
	// ********************************************
    // Compiling the shader programms
    //*********************************************
	// Do your GLEW experiments here:
    if (GLEW_ARB_shading_language_100) 
    { 
        std::cout << "GLEW_ARB_shading_language_100" << std::endl;
        int major, minor, revision;
        const GLubyte* sVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
        if (glGetError() == GL_INVALID_ENUM)
        {
            major = 1; minor = 0; revision=51;
        }
        else
        {
            std::string version((char*)sVersion);
            std::cout << version.c_str() << std::endl;
        }

        // Load vertex Shader
        GLuint vertShader = glCreateShader (GL_VERTEX_SHADER);
        if ( 0 == vertShader )
        {
            std::cout << "Error creating vertex shader" << std::endl;
        }

        std::ifstream v_shader_file(vertexShader, std::ifstream::in);
        std::string v_str((std::istreambuf_iterator<char>(v_shader_file)), std::istreambuf_iterator<char>());
        const char* vs_code_array[] = {v_str.c_str()};
        
        glShaderSource( vertShader, 1, vs_code_array, NULL);

        // Compilar el shader
        glCompileShader( vertShader );

        // verificar resultado de la compilacion
        GLint vs_compilation_result;
        glGetShaderiv( vertShader, GL_COMPILE_STATUS, &vs_compilation_result );
        if( GL_FALSE == vs_compilation_result )
        {
            std::cout << "Vertex shader compilation failed!\n" << std::endl;
            GLint logLen;
            glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen );
            if( logLen > 0 )
            {
                char * log = (char *)malloc(logLen);
                GLsizei written;
                glGetShaderInfoLog(vertShader, logLen, &written, log);
                std::cout << "Shader log: " << log << std::endl;
                free(log);
            }
        }

         // Load fragment Shader
        GLuint fragShader = glCreateShader (GL_FRAGMENT_SHADER);

        if ( 0 == fragShader )
        {
            std::cout << "Error creating fragment shader" << std::endl;
        }

        std::ifstream f_shader_file(fragmentShader, std::ifstream::in);
        std::string f_str((std::istreambuf_iterator<char>(f_shader_file)), std::istreambuf_iterator<char>());
        const char* fs_code_array[] = {f_str.c_str()};
        
        glShaderSource( fragShader, 1, fs_code_array, NULL);

        // Compilar el shader
        glCompileShader( fragShader );

        // verificar resultado de la compilacion
        GLint fs_compilation_result;
        glGetShaderiv( fragShader, GL_COMPILE_STATUS, &fs_compilation_result );
        if( GL_FALSE == fs_compilation_result )
        {
            std::cout << "Fragment shader compilation failed!\n" << std::endl;
            GLint logLen;
            glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen );
            if( logLen > 0 )
            {
                char * log = (char *)malloc(logLen);
                GLsizei written;
                glGetShaderInfoLog(fragShader, logLen, &written, log);
                std::cout << "Shader log: " << log << std::endl;
                free(log);
            }
        }
		
		// *******************************************

    // *******************************************
    // Linking the shader programms
    // *******************************************
        this->programHandle = glCreateProgram();
        if ( 0 == this->programHandle )
        {
            std::cout << "Error creating program object" << std::endl;
        }
        else
        {
            glAttachShader( this->programHandle, vertShader );
            glAttachShader( this->programHandle, fragShader );

        }
	}
}
void Shader::link() {

			glLinkProgram( this->programHandle );

            GLint status;
            glGetProgramiv( this->programHandle, GL_LINK_STATUS, &status );
            if( GL_FALSE == status )
            {
                std::cout << "Failed to link shader program!\n" << std::endl;
                GLint logLen;
                glGetProgramiv(this->programHandle, GL_INFO_LOG_LENGTH, &logLen);
                if( logLen > 0 )
                {
                    char * log = (char *)malloc(logLen);
                    GLsizei written;
                    glGetProgramInfoLog(this->programHandle, logLen, &written, log);
                    std::cout << "Program log: \n%s" << std::endl;
                    free(log);
                }
            }
}

void Shader::bindAttribLocation(GLuint location, std::string attrib) {
	glBindAttribLocation(this->programHandle, location, attrib.c_str());
}

int Shader::getUniformLocation(const std::string& attrib) {
	return glGetUniformLocation(programHandle, attrib.c_str());
}

void Shader::ConcreteSetter<int>::apply() {
	glUniform1i(index, x);
}

void Shader::ConcreteSetter<float>::apply() {
	glUniform1f(index, x);
}

void Shader::ConcreteSetter<glm::mat4>::apply() {
	glUniformMatrix4fv(index, 1, 0, glm::value_ptr(x));
}

void Shader::ConcreteSetter<glm::mat3>::apply() {
	glUniformMatrix3fv(index, 1, 0, glm::value_ptr(x));
}

void Shader::ConcreteSetter<glm::vec3>::apply() {
	glUniform3f(index, x[0], x[1], x[2]);
}

void Shader::use() {
	glUseProgram( this->programHandle );

	for (std::vector<Setter*>::iterator it = setters.begin();
		it != setters.end(); it++) {
		(*it)->apply();
	}
}

glm::mat4 Shader::compute_normal_matrix(const glm::mat4& m) {
	return glm::transpose(glm::inverse(m));
}

