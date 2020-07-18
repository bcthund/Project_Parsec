#version 330 core
in vec4 vVertex;
in vec4 vColor;
//out float fAngle;
//out mat2 rot;
uniform mat4 mvpMatrix;
uniform float fTime = 1.0f;
uniform vec3 vPos;
void main(void) {
 float fAngle = fTime*10;
 float fD = distance(-vPos.xyz, vVertex.xyz)/25000;
//	float fD = distance(vec3(0.0f), vVertex.xyz)/4096;
//	float fD = 128;

//  float st = sin(fAngle);
//  float ct = cos(fAngle);
//  rot = mat2(ct, st, -st, ct);
  //gl_PointSize = min(40, (1/fD));
  gl_PointSize = 1/fD;
  gl_Position = mvpMatrix * vec4(vVertex.x, vVertex.y, vVertex.z, 1.0f);
}
