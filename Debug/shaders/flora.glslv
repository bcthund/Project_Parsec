#version 330 core
in vec4 vVertex;
in vec4 vOffset;
in vec4 vNormal;
out vec2 vSizeG;
out float fAlpha1;
uniform vec3 vPos;
void main(void) {
// mSkew = mat3(1, tan(fTime), 0, 0, 1, 0, 0, 0, 1);
// float fD = exp(distance(vPos.xyz, vVertex.xyz)/(vSize.z*4));
 float fD = distance((vPos.xyz), (vVertex.xyz))/(512*0.8);
// if(vVertex.y >= 0.0f) fAlpha1 = 0.0f;
 fAlpha1 = 1/pow(fD,10);
// fAlpha1 = 1/fD;
 vSizeG = vNormal.xy;
 gl_Position = (vec4(vVertex.x, vVertex.y, vVertex.z, 1.0f));
}
