#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
uniform vec3 vLightPos[32];
in vec4 vVertex;
in vec4 vNormal;
in vec2 vTexCoords;
out Data {
 smooth out vec4 vVert;
 smooth out vec4 vNormal;
 smooth out vec2 vTexCoords;
 smooth out vec3 vLight;
 smooth out vec3 vRayDir[32];
 //smooth out vec3 vLightPos[32];
} data;
void main(void) {
 data.vVert = vVertex;
 data.vNormal = vNormal;
 data.vTexCoords = vTexCoords;
 data.vLight = vLightPos[0] - vVertex.xyz;
 data.vRayDir[0] = vLightPos[0] - vVertex.xyz;
 //for(int light=0; light<32; light++) {
 //	data.vLightPos[light] = vLightPos[light] - vVertex.xyz;
 //}
 //data.vLightPos[0] = vLightPos[0] - vVertex.xyz;
 gl_Position = mvpMatrix * vVertex;
}
