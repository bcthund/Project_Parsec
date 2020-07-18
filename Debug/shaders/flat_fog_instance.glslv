#version 330 core
uniform vec3 vWorldPos;
uniform mat4 mvMatrix;
//uniform mat4 mtMatrix;
uniform vec4 vClipPlane;
in vec4 vVertex;
in vec2 vTexCoords;
in vec4 vOffset;
in vec4 vExtra;
out vec4 vExtraG;
//out mat4 mvMatrixG;
//out float fHeight;
 smooth out vec2 vTexCoordIn;
 smooth out vec4 vEyeSpacePos; 
void main(void) {
// Clip Plane for Reflect/Refract
 gl_ClipDistance[0] = dot(vVertex, vClipPlane);
// mat4 mShear = mat4(1, sin(vVertex.w+fTime*10)/100, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
 vTexCoordIn = vTexCoords;
// mvMatrixG = mvMatrix;
 vExtraG = vExtra;
// fHeight = vOffset.y;
//vsFog_Calc
// if (gl_InstanceID > 0) gl_Position = mvpMatrix * (vVertex + vec4(vPos[0], 0.0, vPos[2], 0.0));
// else gl_Position = mvpMatrix * vVertex;
// gl_Position = mvpMatrix * vVertex;
// gl_Position = mvpMatrix * (vec4(vVertex.xyz, 1) * mShear);
// gl_Position = mvMatrix * vec4(vVertex.x+vOffset.x, vVertex.y+vOffset.y, vVertex.z+vOffset.z, 1.0f);
//  mat4 mRot = mat4( cos(fRot),0.0f,sin(fRot),0.0f,
// 0.0f,1.0f,  0.0f,0.0f,
// -sin(fRot),0.0f,cos(fRot),0.0f,
// 0.0f,0.0f,0.0f,1.0f );
//  mat4 mBB = mat4 ( 1.0,              mvMatrix[1][0], 0.0,             mvMatrix[3][0],
//                    0.0,              mvMatrix[1][1], 0.0,             mvMatrix[3][1],
//                    0.0,              mvMatrix[1][2], 1.0,             mvMatrix[3][2],
//                    mvMatrix[0][3],  mvMatrix[1][3], mvMatrix[2][3], mvMatrix[3][3]);
//  mat4 mBB = mat4 ( 1.0,              0.0,0.0,             mvMatrix[0][3],
//                    0.0,              1.0,0.0,             mvMatrix[1][3],
//                    0.0,              0.0,1.0,             mvMatrix[2][3],
//                    mvMatrix[3][0],  mvMatrix[3][1], mvMatrix[3][2], mvMatrix[3][3]);
// Cylindrical Billboarding
 gl_Position = vec4(vVertex.x+vOffset.x, vVertex.y+vOffset.y, vVertex.z+vOffset.z, 1.0f);
// Spherical Billboarding
// gl_Position = mvMatrix * vec4(vVertex.x+vOffset.x, vVertex.y+vOffset.y, vVertex.z+vOffset.z, 1.0f);
}
