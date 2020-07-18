#version 330 core
in vec4 vVertex;
in vec3 vNormal;
in vec4 vTexCoords;
uniform vec3 vSunPos;
uniform vec3 vMoonPos;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform vec3 vCamPos;
uniform float fTime;
out DataOut {
 smooth out vec2 vTexCoords;
 smooth out vec3 vNormal;
 smooth out vec4 vert;
 smooth out vec3 vSunVector;
 smooth out vec3 vMoonVector;
 smooth out vec3 eyeVec;
 smooth out vec3 vToCamera;
 smooth out vec3 vCamPos;
 smooth out float fTime;
 smooth out vec4 vClipSpace;
} data;

void main() {
 float fFreq = 100.0;
 float fTX = 20.0;
 data.vTexCoords = vTexCoords.st;
 data.vNormal = vec3(vNormal.x, vNormal.y, vNormal.z);
 data.vSunVector = normalize(vSunPos).xyz;
 data.vMoonVector = normalize(vMoonPos).xyz;
 data.eyeVec = vCamPos - vVertex.xyz;
 data.vToCamera = (inverse(mvMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - vVertex.xyz;
 data.vCamPos = vCamPos;
 data.vert = vVertex;
 data.fTime = fTime;
 data.vClipSpace = mvpMatrix * vVertex;
 gl_Position = data.vClipSpace;
}
