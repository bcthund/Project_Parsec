#version 330 core
in vec4 vVertex;
in vec3 vNormal;
in vec4 vTexCoords;
uniform vec3 vLightPosition;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
//uniform vec4 vClipPlane;
out DataOut {
 smooth out vec2 vTexCoords;
 smooth out vec3 vNormal;
 smooth out vec4 vert;
 smooth out vec3 vLightVector;
 smooth out vec3 bumpLightVector;
} data;
 smooth out vec4 vEyeSpacePos; 
void main() {

// Clip Plane for Reflect/Refract
// gl_ClipDistance[0] = dot(vVertex, vClipPlane);

//Bump Mapping
 vec3 vNorm = vNormal;
 vec3 tangent, binormal;
 tangent  = normalize(cross(vNormal, vec3(0.0, -1.0, 0.0)));
 binormal = normalize(cross(tangent, vNormal));
 mat3 TBNMatrix = mat3(tangent, binormal, vNormal);

//Data Forward
 data.vTexCoords = vTexCoords.st;
// data.vNormal = vec3(normalize(mvMatrix * vec4(vNormal,0.0)));
 data.vNormal = vNormal;
 data.vLightVector = normalize(vLightPosition);//Standard Lighting
// data.bumpLightVector = normalize(vLightPosition-vVertex.xyz);//Bump Map Lighting
 data.bumpLightVector = normalize(vLightPosition);//Bump Map Lighting
 data.bumpLightVector *= TBNMatrix;//Apply Bump Mapping
 data.vert = vVertex;
//vsFog_Calc
 gl_Position = mvpMatrix * vVertex;
}
