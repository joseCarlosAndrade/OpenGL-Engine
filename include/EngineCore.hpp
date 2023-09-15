#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include<iostream>
#include<fstream>
// glew needs to be imporetd before glfw!!!!!!!!!!!!!!!
#include<GL/glew.h>
#include<GLFW/glfw3.h>


// my custom libs
#include"Matrices.hpp"

#define GLFW_INCLUDE_NONE


// g++ airship.c -lglfw -lGL -lGLEW -lm -o bin/airship

/* Shader operations */
namespace Shaders {
    // Load shaders from a give file
    GLuint LoadShaders(std::string vertex_file, std::string fragment_file);
}



/* Engines main area. Defines the Core, objects and the application attributes. */
namespace Engine {

    /* Engine initialization mode */
    typedef enum {INIT_EVERYTHING, CUSTOM_INITIALIZATION} ENGINE_INIT_MODE;
    typedef unsigned int window_size;
    typedef unsigned int version;
    typedef bool eng_result;

    /* Initializes OpenGL and GLFW main needs. */
    class Core {
        private:
            GLFWwindow *mainWindow;
            window_size windowWidth, windowHeight;

        public:
            /* Initializes engine environment with Glew application. */
            Core(ENGINE_INIT_MODE mode, version opengl_version=4);
            ~Core();

            /* Method to create and initialize main application window. */ // TODO: customize fullscreen mode
            eng_result createMainWindow(window_size width, window_size height, std::string window_name);

            /* ### Engine main loop 
            Once initialized, it only stops when the close button is pressed OR when a defined close key is pressed (TODO). */
            void EngineMainLoop();

            /* Return an id? add directly? */
            eng_result addCalback();
            
            
    };

    class Camera {

    };

    /* Represents a simple object that is inherited by all objects */
    class GameObject {
        public:
        GameObject() {
        }
    };

    class Triangle : public GameObject {

    };

    class TriangleFan : public GameObject {

    };

    class Square : public TriangleFan {

    };

    class Circle : public TriangleFan {

    };

}



#endif