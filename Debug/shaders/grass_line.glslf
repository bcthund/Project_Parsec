#version 330 core
out vec4 vFragColor;
uniform vec4 vSunDiffuse;
uniform vec4 vMoonDiffuse;
in float fShade;
in float fAlpha;
void main(void) {
 vFragColor = (vec4(0.54f, 0.57f, 0.35f, fAlpha) * fShade) * (vSunDiffuse + vMoonDiffuse);
// vFragColor = (vec4(0.54f, 0.57f, 0.35f, 0.75f) * fShade) * (vSunDiffuse + vMoonDiffuse);
}
