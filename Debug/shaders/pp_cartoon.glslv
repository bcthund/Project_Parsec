#version 330 core
uniform mat4 mvpMatrix;
uniform vec3 vSunPos;
in vec4 vVertex;
in vec2 vTexCoords;
out Data {
  out vec2 vTexCoords;
} data;
void main(void) {
 gl_Position = mvpMatrix * vVertex;
 data.vTexCoords = vTexCoords;
}
