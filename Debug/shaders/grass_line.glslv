#version 330 core
in vec4 vVertex;
in vec4 vNormal;
in vec4 vOffset;
in vec4 vColor;
in vec4 vExtra;
out vec4 vData;
uniform vec3 vPos;
void main(void) {
// float fD = exp(distance((vPos.xyz), vVertex.xyz+vec3(vOffset[0], 0.0f, vOffset[1]))/(vVertex[3]*4));
 float fD = exp(distance((vPos.xyz), vVertex.xyz+vec3(vOffset[0], 0.0f, vOffset[1]))/(vVertex[3]));
 vData[0] = vOffset[2];// Height modifier
 vData[1] = vOffset[3];// Discard height
 vData[2] = 1/fD;// Alpha
 vData[3] = vExtra[2];// Shade
 float fY = (vNormal[int(vExtra[1])]*vOffset.x)+(vNormal[int(vExtra[1])+1]*vOffset.y) + vVertex.y;
 gl_Position = (vec4(vVertex.x+vOffset.x, fY, vVertex.z+vOffset.y, 1.0f));
}
