#version 330 core
uniform mat4 mvpMatrix;
uniform vec3 vWorldPos;
in vec3 vNormal;
in vec4 vVertex;
out Data {
 out vec4 vFragColorVs;
 out vec3 normal;
 out mat4 mvp;
} data;
void main(void) {
 data.vFragColorVs = vec4(vNormal.x, vNormal.y, vNormal.z, 1.0);
 data.normal = vNormal;
 data.mvp = mvpMatrix;
// if ( (vVertex.x <= vWorldPos.x-100) || (vVertex.x >= vWorldPos.x+100) || (vVertex.z <= vWorldPos.z-100) || (vVertex.z >= vWorldPos.z+100) ) {
//  gl_Position = vec4(0.0, 0.0, 0.0, 69.0);
// }
// else gl_Position = vVertex;
 gl_Position = vVertex;
}
