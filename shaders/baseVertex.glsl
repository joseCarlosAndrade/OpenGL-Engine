#version 330 core

// layout location refers to the buffer that will give the inputs for vertexPosition_modelspace
// it needs to be the same on the src cpp file
layout(location =0) in vec3 vertexPosition_modelspace; // in variables

void main() {
    // gl position is a built in variable that needs to be assigned 
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
}