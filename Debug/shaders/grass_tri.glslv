#version 330 core
in vec4 vVertex;
in vec4 vNormal;
in vec4 vOffset;
in vec4 vColor;
in vec4 vExtra;
out mat3 mData;
uniform vec3 vPos;
void main(void) {
 float fD = exp(distance((vPos.xyz), vVertex.xyz+vec3(vOffset[0], 0.0f, vOffset[1]))/(vVertex[3]*4));
 mData[0][0] = vOffset[2];// Height modifier
 mData[0][1] = vOffset[3];// Discard height
 mData[0][2] = (1/fD);// Alpha
 mData[1][0] = vExtra[2];// Shade
 mData[1][1] = vExtra[0];// Width modifier
 float fY = vVertex.y+(vNormal[int(vExtra[1])]*vOffset.x)+(vNormal[int(vExtra[1])+1]*vOffset.y);
 gl_Position = (vec4(vVertex.x+vOffset.x, fY, vVertex.z+vOffset.y, 1.0f));
}
