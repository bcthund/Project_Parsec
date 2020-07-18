#version 330 core
uniform mat4 mvpMatrix;
in vec4 vVertex;
in vec2 vTexCoords;
out vec2 texCoords;
float fHeight = 720.0f;// TODO: make uniform
out vec2 blurTexCoords[11];
void main(void) {
 vec2 centerTexCoords = vVertex.xy * 0.5 + 0.5;
 float pixelSize = 1.0f/fHeight;// 16.0f
 //for (int i=-5; i<5; i++) {
 // blurTexCoords[i+5]=centerTexCoords + vec2(0.0, pixelSize*i);
 //}
 gl_Position = mvpMatrix * vVertex;
 texCoords = centerTexCoords + vec2(0.0, pixelSize);
}
