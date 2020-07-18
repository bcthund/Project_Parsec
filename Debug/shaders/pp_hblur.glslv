#version 330 core
uniform mat4 mvpMatrix;
in vec4 vVertex;
in vec2 vTexCoords;
out vec2 texCoords;
float fWidth = 1280.0f;// TODO: make uniform
out vec2 blurTexCoords[11];
void main(void) {
 //vec2 centerTexCoords = vVertex.xy * 0.5 + 0.5;
 //float pixelSize = 1.0f/fWidth;// 8.0f
 //for (int i=-5; i<5; i++) {
 // blurTexCoords[i+5] = centerTexCoords + vec2(pixelSize*i, 0.0);
 //}
 gl_Position = mvpMatrix * vVertex;
 texCoords = vTexCoords;
}
