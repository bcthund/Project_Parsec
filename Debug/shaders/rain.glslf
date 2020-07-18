#version 330 core
out vec4 vFragColor;
in float fAlpha;
void main(void) {
 vFragColor = vec4(0.8f, 0.8f, 0.8f, fAlpha);
// vFragColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);
}
