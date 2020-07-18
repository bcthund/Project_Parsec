#version 330 core
uniform sampler2D colorMap;
uniform float flareAlpha;
out vec4 vFragColor;
in vec2 texCoords;
void main(void) {
 vec4 vColor = texture(colorMap, texCoords.st);
 vFragColor = vColor;
 vFragColor.a *= flareAlpha;
}
