#version 330 core
out vec4 vFragColor;
in vec2 vTexCoord;
in float fAlpha;
uniform sampler2D colorMap;
uniform vec4 vSunDiffuse;
uniform vec4 vMoonDiffuse;
void main(void) {
 vec4 vColor = texture(colorMap, vTexCoord.st);
 if(vColor.a <= 0.1) discard;
// else vFragColor = (vColor*vec4(1.0f, 1.0f, 1.0f, fAlpha)) * (vSunDiffuse + vMoonDiffuse);
 else vFragColor = (vColor*vec4(1.0f, 1.0f, 1.0f, 1.0f)) * (vSunDiffuse + vMoonDiffuse);
}
