#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform vec3 vSunPos;
uniform vec3 vMoonPos;
uniform float fTime;
in vec4 vVertex;
in vec4 vNormal;
in vec2 vTexCoords;
out Data {
 smooth out vec3 vNormal;
 smooth out vec3 vVert;
 smooth out vec2 vTexCoords;
 smooth out vec3 vSunVector;
 smooth out vec3 vMoonVector;
 smooth out vec3 vCamVector;
} data;
void main(void) {
 data.vNormal = vec3(vNormal.x, vNormal.y, vNormal.z);
 data.vVert = vVertex.xyz;
// data.vSunVector = normalize(vSunPos-(vVertex.xyz));
// data.vMoonVector = normalize(vMoonPos-(vVertex.xyz));
 data.vCamVector = (inverse(mvMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - vVertex.xyz;
 data.vSunVector = normalize(vSunPos);
 data.vMoonVector = normalize(vMoonPos);
 data.vTexCoords = vec2(vTexCoords.s+(fTime/1000), vTexCoords.t+(fTime/1000));
 gl_Position = mvpMatrix * vVertex;
}
