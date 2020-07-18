#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
uniform vec3 vWorldPos;
uniform bvec4 vBools;
uniform float fTime;
uniform vec4 vClipPlane;
in vec4 vVertex;
in vec2 vTexCoords;
in vec3 vPos;
//out Data {
 smooth out vec2 vTexCoordIn;
//} data;
 smooth out vec4 vEyeSpacePos; 
void main(void) {
// Clip Plane for Reflect/Refract
 gl_ClipDistance[0] = dot(vVertex, vClipPlane);
// vec3 vLook = vWorldPos - vPos;
//normalize( vLook );
// vec3 vUp = vec3( 0.0, 1.0, 0.0 );
// vec3 vRight = cross( vLook, vUp );
// mat4 mBB = mat4( vRight[0], vRight[1], vRight[2], 0.0, 0.0, 1.0, 0.0, 0.0, vLook[0], vLook[1], vLook[2], 0.0, vPos[0], vPos[1], vPos[2], 1.0 );
 mat4 mShear = mat4(1, sin(vVertex.w+fTime*10)/100, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
 vTexCoordIn = vTexCoords;
//vsFog_Calc
// if (gl_InstanceID > 0) gl_Position = mvpMatrix * (vVertex + vec4(vPos[0], 0.0, vPos[2], 0.0));
// else gl_Position = mvpMatrix * vVertex;
// gl_Position = mvpMatrix * vVertex;
 if(vBools.x==true) gl_Position = mvpMatrix * (vec4(vVertex.xyz, 1) * mShear);
 else gl_Position = mvpMatrix * (vec4(vVertex.xyz, 1));
// gl_Position = mvpMatrix * (vec4(vVertex.xyz, 1) * mShear);
}
