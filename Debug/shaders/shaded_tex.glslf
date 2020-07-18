#version 330 core
uniform vec4 vColor;
uniform sampler2D colorMap;
out vec4 vFragColor;
in vec2 vVaryingTexCoords;
void main(void) {
// INTERLACED MODE
// if (mod(gl_FragCoord.y, 2) >= 1) vFragColor = texture(colorMap, vVaryingTexCoords.st) * vColor;
// else discard;
 vFragColor = texture(colorMap, vVaryingTexCoords.st) * vColor;
}
