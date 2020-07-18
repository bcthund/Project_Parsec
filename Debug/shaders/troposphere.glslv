#version 330 core
uniform mat4 mvpMatrix;
//uniform mat4 mvMatrix;
//uniform mat4 mpMatrix;
uniform vec3 vLightPos;
in vec4 vVertex;
in vec4 vNormal;
in vec2 vTexCoords;
out Data {
// smooth out vec4 vVert;
 smooth out vec4 vNormal;
 smooth out vec2 vTexCoords;
// smooth out vec3 vBumpLight;
 smooth out vec3 vLightPos;
} data;
void main(void) {
// data.vBumpLight = normalize(vLightPos);
// data.vVert = vVertex;
 data.vNormal = vNormal;
 data.vTexCoords = vTexCoords;
 data.vLightPos = vLightPos;
 gl_Position = mvpMatrix * vVertex;
}
