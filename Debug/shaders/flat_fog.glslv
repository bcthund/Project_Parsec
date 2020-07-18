#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
uniform vec3 vWorldPos;
uniform vec4 vClipPlane;
in vec4 vVertex;
in vec2 vTexCoords;
in vec3 vPos;
 smooth out vec2 vTexCoordIn;
 smooth out vec4 vEyeSpacePos; 
void main(void) {
 gl_ClipDistance[0] = dot(vVertex, vClipPlane);
 vTexCoordIn = vTexCoords;
 gl_Position = mvpMatrix * (vec4(vVertex.xyz, 1));
}
