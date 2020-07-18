#version 330 core
uniform mat4 mvpMatrix;
//uniform mat4 mvMatrix;
//uniform mat4 mpMatrix;
uniform vec3 vLightPos;
in vec4 vVertex;
in vec4 vNormal;
in vec2 vTexCoords;
out Data {
 smooth out vec2 vTexCoords;
} data;
void main(void) {
 data.vTexCoords = vTexCoords;
 gl_Position = mvpMatrix * vVertex;
}
