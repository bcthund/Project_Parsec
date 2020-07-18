#version 330 core
uniform mat4 mvpMatrix;
in vec4 vVertex;
in vec2 vTexCoords;
float fWidth = 1280.0f;		// TODO: make uniform
float fHeight = 720.0f;		// TODO: make uniform
out Data {
  out vec2 vTexCoords;
} data;
void main(void) {
 data.vTexCoords = vTexCoords;
// vec2 centerTexCoords = vVertex.xy * 0.5 + 0.5;
// data.vTexCoords = vVertex.xy * 0.5 + 0.5;
 gl_Position = mvpMatrix * vVertex;
}
