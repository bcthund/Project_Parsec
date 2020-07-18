#version 330 core
uniform sampler2D colorMap0;
uniform sampler2D colorMap1;
out vec4 vFragColor;
in vec2 texCoords;
uniform float intensity = 1.5f;
void main(void) {
 vec4 vColor0 = texture(colorMap0, texCoords.st);
 vec4 vColor1 = texture(colorMap1, texCoords.st);
// vFragColor = vec4((vColor1.rgb * intensity), 1.0);
// vFragColor = vec4((vColor0.rgb + vColor1.rgb * intensity), 1.0);
 vFragColor = vColor0 + vColor1 * intensity;
 vFragColor.a = min(vFragColor.a, 1.0);
// vFragColor = vec4(mix(vColor0.rgb, vColor1.rgb, intensity), 1.0);
}
