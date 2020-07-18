#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
in  vec4 vVertex;
in  vec2 vTexCoords;
out Data {
  out vec2 vTexCoords;
} data;
void main(void) {
 data.vTexCoords = vTexCoords;
 gl_Position = mvpMatrix * vVertex;
}
