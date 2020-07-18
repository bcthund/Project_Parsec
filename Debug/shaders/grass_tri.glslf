#version 330 core
out vec4 vFragColor;
in float fShade;
in float fAlpha;
uniform vec4 vSunDiffuse;
uniform vec4 vMoonDiffuse;
void main(void) {
 vFragColor = (vec4(0.54f, 0.57f, 0.35f, fAlpha) * fShade) * (vSunDiffuse + vMoonDiffuse);
}
