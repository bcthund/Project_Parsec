#version 330 core
in vec4 vVertex;
in vec4 vColor;
out float fAngle;
uniform mat4 mvpMatrix;
//uniform vec3 vPos;
uniform float fTime = 1.0f;
void main(void) {
// float fMove = sin(fTime*4)*500;
// float fMove = fract(fTime)*1000;
// if (fTime>1.0f) {
//  int iF = int(fTime);
//  fMove = fTime - iF;
// }
 fAngle = fTime*10;
 gl_PointSize = vVertex.z;
// gl_Position = mvpMatrix * vec4(vVertex.x, vVertex.y-fMove, 0.0f, 1.0f);
 gl_Position = mvpMatrix * vec4(vVertex.x, vVertex.y, 0.0f, 1.0f);
// gl_Position = mvpMatrix * vec4(fTime, fTime, 1.0f, 1.0f);
}
