#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
in vec4 vVertex;
in vec4 vNormal;
in vec2 vTexCoords;
out Data {
 out vec3 vVert;
 out vec3 vNormal;
 out vec2 vTexCoords;
} data;
void main(void) {
// data.vVert = (mvMatrix * vVertex).xyz;
 data.vVert = vVertex.xyz;
 data.vNormal = vNormal.xyz;
 data.vTexCoords = vTexCoords;
 gl_Position = mvpMatrix * vVertex;
}
