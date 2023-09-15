#include"../include/EngineCore.hpp"


using namespace Engine;

int main(int argc, char ** argv) {
    std::cout << "Initializing engine core: " << std::endl;
    Core engine_core (INIT_EVERYTHING);

    std::cout << "Init window: " << std::endl;
    engine_core.createMainWindow(500, 500, "My little window");
    engine_core.EngineMainLoop();
}