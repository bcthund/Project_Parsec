#version 330 core
uniform vec4 vColor;
uniform sampler2D colorMap;
out vec4 vFragColor;
in vec2 vVaryingTexCoords;
void main(void) {
 vec4 vNewColor = vec4(vColor[0], vColor[01], vColor[2], 0.25);
 vFragColor = texture(colorMap, vVaryingTexCoords.st) * vNewColor;
}
