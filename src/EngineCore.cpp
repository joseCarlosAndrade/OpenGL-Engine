#include"../include/EngineCore.hpp"
#include<sstream>
#include<vector>


Engine::Core::Core(Engine::ENGINE_INIT_MODE mode, version opengl_version) {
    if (!glfwInit()) {
        std::cerr << "Error initializing glfw. " << std::endl;
        exit(EXIT_FAILURE);
    }

    if (mode == Engine::INIT_EVERYTHING) {
        glfwWindowHint(GLFW_SAMPLES, 4); // antialiasing
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version); // opengl version
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    // TODO: implement custom init
}

Engine::Core::~Core() {
    glfwDestroyWindow(mainWindow);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}


Engine::eng_result Engine::Core::createMainWindow(window_size width, window_size height, std::string window_name)  {
    windowHeight = height;
    windowWidth = width;
    mainWindow = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);

    if(mainWindow == NULL) {
        std::cerr << "Window could not be initialized." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(mainWindow);
    if ( glewInit() != GLEW_OK) {
        std::cerr << "ERROR: Glew could not be initialized. Please verify." << std::endl;
        exit(EXIT_FAILURE);
    }

    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // maybe not necessary?
    return true;
}

void Engine::Core::EngineMainLoop() {
    assert(mainWindow!=NULL);
    glfwShowWindow(mainWindow);
    while(!glfwWindowShouldClose(mainWindow)) {
        glClear(GL_COLOR_BUFFER_BIT); // reduces flickering


        glfwSwapBuffers(mainWindow); // swaps double buffers
        glfwPollEvents(); // handles collected events
    }
}