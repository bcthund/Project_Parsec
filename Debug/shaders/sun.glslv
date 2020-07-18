#version 330 core
//GLS_SUN
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
in vec4 vVertex;
in vec2 vTexCoords;
in vec3 vPos;
out vec2 vPassTexCoords;
void main(void) {
 vPassTexCoords = vTexCoords;
 gl_Position = mvpMatrix * vec4(vVertex.x, vVertex.y, vVertex.z, 1.0f);
}
