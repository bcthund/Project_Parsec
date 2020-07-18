#version 330 core
uniform mat4 mvpMatrix;
in vec4 vVertex;
in vec2 vTexCoords;
out vec2 texCoords;
void main(void) {
 gl_Position = mvpMatrix * vVertex;
 texCoords = vTexCoords;
}
