GL_ARGS=-lglfw -lGL -lGLEW

all: tests/engine_test.cpp 
	mkdir -p bin/
	
	g++ tests/engine_test.cpp src/EngineCore.cpp -o bin/engineTest -lglfw -lGL -lGLEW

run_test:
	./bin/engineTest