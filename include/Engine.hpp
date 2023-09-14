#include<iostream>
#include<GLFW/glfw3.h>
#include<GL/glew.h>

// g++ airship.c -lglfw -lGL -lGLEW -lm -o bin/airship

namespace Engine {
    class Core {

        public:
            Core();
            ~Core();
    };

    class GameObject {

    };

    class Triangle : public GameObject {

    };

    class TriangleFan : public GameObject{

    };

    class Square : public TriangleFan {

    };

    class Circle : public TriangleFan {

    };

}