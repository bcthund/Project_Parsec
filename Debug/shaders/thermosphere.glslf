#version 330 core
uniform vec4 vDiffuseColor;
uniform sampler2D texColor0;
uniform sampler2D texColor1;
uniform float fS;
uniform float fD;
layout (location = 0) out vec4 fragmentColor;
in Data {
 smooth in vec2 vTexCoords;
} data;
float fAlphaThreshold;
void main(void) {
vec4 texSunRise = texture2D(texColor0, data.vTexCoords);
vec4 texDayTime = texture2D(texColor1, data.vTexCoords);
vec4 texMix = mix(texSunRise, texDayTime, fD);
vec4 diffuse = vec4(vDiffuseColor.rgb, fS);
// fAlphaThreshold = 0.10;
// if (texColor.a <= fAlphaThreshold) discard;
// else {
  fragmentColor = texMix * diffuse;
//  fragmentColor.a = 1.0;
//  fragmentColor = mix(fragmentColor, vec4(fragmentColor.rgb, 0.0), 0.2);
//  fragmentColor = diffuse;
// }
}
