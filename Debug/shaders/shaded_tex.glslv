#version 330 core
uniform mat4 mvpMatrix;
in vec4 vVertex;
in vec2 vTexCoords;
out vec2 vVaryingTexCoords;
void main(void) {
 vVaryingTexCoords = vTexCoords;
 gl_Position = mvpMatrix * vVertex;
}
