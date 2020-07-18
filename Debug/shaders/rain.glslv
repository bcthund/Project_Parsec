#version 330 core
in vec4 vVertex;
//in vec4 vColor;
out float fFactor;
uniform mat4 mvpMatrix;
uniform vec3 vPos;
void main(void) {
 float fD = distance(vPos.xyz, vVertex.xyz)/512;
 fFactor = min(5, (1/pow(fD,2)));
// fFactor = 2.0f;
//  gl_PointSize = 1.0f;
  gl_Position = mvpMatrix * vec4(vVertex.x*16, vVertex.y, vVertex.z*16, 1.0f);
// }
}
