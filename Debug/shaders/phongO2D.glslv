#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
uniform vec3 vObjPos;
uniform vec3 vCamPos;
in vec4 vVertex;
in vec4 vNormal;
in vec2 vTexCoords;
out Data {
 out vec3 vVert;
 out vec3 vNormal;
 out vec2 vTexCoords;
} data;
void main(void) {
 vec3 vUp = vec3(0.0, 1.0, 0.0);
 vec3 vObjXZ = vec3(vObjPos.x, 0.0, vObjPos.z);		// Cylindrical billboarding
 vec3 vLook = normalize(vObjXZ - vCamPos);			// Cylindrical billboarding
// vec3 vLook = normalize(vObjPos - vCamPos);		// Spherical billboarding
 vec3 vRight = cross(vUp, vLook);
 mat4 mBB = mat4(	vRight.x,	vRight.y,	vRight.z,	0.0f,
					0.0f,		1.0f,		0.0f,		0.0f,
					vLook.x,	vLook.y,	vLook.z,	0.0f,
					0.0f,		0.0f,		0.0f,		1.0f );

 vec4 vObjBB = (vVertex * transpose(mBB)) + vec4(vObjPos, 0.0);

 data.vVert = vObjBB.xyz;
 data.vNormal = vNormal.xyz;
 data.vTexCoords = vTexCoords;
 gl_Position = mvpMatrix * vObjBB;
//  gl_Position = mvpMatrix * vVertex;
}
