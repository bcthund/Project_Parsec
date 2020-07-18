#version 330 core
in vec4 vVertex;
in vec3 vNormal;
in vec4 vTexCoords;
uniform vec3 vSunPos;
uniform vec3 vMoonPos;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
uniform vec3 vCamPos;
uniform vec4 vClipPlane;
out DataOut {
 smooth out vec2 vTexCoords;
 smooth out vec3 vNormal;
 smooth out vec4 vert;
 smooth out vec3 vSunVector;
 smooth out vec3 vMoonVector;
 smooth out vec3 vCamPos;
 smooth out vec3 eyeVec;
 smooth out vec3 vLampVector;
// smooth out vec4 vClipSpace;
 smooth out vec3 vToCamera;
// smooth out vec3 bumpLightVector;
} data;
 smooth out vec4 vEyeSpacePos; 
void main() {

// data.vClipSpace = mvpMatrix * vVertex;
 data.vToCamera = (inverse(mvMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - vVertex.xyz;
// Clip Plane for Reflect/Refract
 gl_ClipDistance[0] = dot(vVertex, vClipPlane);

//Bump Mapping
vec3 vNorm = normalize(vNormal);
//vec3 tangent, binormal;
//tangent  = normalize(cross(vNormal, vec3(0.0, -1.0, 0.0)));
//binormal = normalize(cross(tangent, vNormal));
//mat3 TBNMatrix = mat3(tangent, binormal, vNormal);

//Data Forward
 data.vTexCoords  = vTexCoords.st;
 data.vNormal     = vNorm;
 data.vSunVector  = normalize(vSunPos).xyz;
 data.vMoonVector = normalize(vMoonPos).xyz;
 data.eyeVec      = vCamPos - vVertex.xyz;
 data.vert        = vVertex;
 data.vCamPos     = vCamPos;
 data.vLampVector = vec3(0, -30, 0) - (mvMatrix * vVertex).xyz;
//vsFog_Calc
 gl_Position = mvpMatrix * vVertex;
}
