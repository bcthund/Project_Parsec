#version 330 core
in vec4 vVertex;
in vec4 vColor;
uniform mat4 mvpMatrix;
uniform vec3 vPos;
void main(void) {
 float fD = distance(vPos.xyz, vVertex.xyz)/512;
  gl_PointSize = min(40, (1/fD));
  gl_Position = mvpMatrix * vec4(vVertex.x*16, vVertex.y, vVertex.z*16, 1.0f);
// }
}
