#version 330 core
//uniform vec4 vColor;
uniform vec4 vDiffuseColor;
uniform vec4 vAmbientColor;
//uniform vec4 vSpecularColor;
uniform sampler2D colorMap;
//uniform sampler2D bumpMap;
layout (location = 0) out vec4 fragmentColor;
in Data {
// smooth in vec3 vVert;
 smooth in vec4 vNormal;
 smooth in vec2 vTexCoords;
// smooth in vec3 vBumpLight;
 smooth in vec3 vLightPos;
} data;
//float fAlphaThreshold;
void main(void) {
// vec4 texColor, vBumpMap, vSpecMap, vAmboMap;
 vec4 texColor;
texColor = texture2D(colorMap, data.vTexCoords);
//vBumpMap = vec4(texture2D(bumpMap, data.vTexCoords).rgb, 1.0)*2.0-1.0;
 float fMaxDarkness = 0.05;
// float nxLight = min(max(fMaxDarkness, dot(data.vNormal.xyz, normalize(data.vLightPos))),1.0);
// float nxLight = min(max(fMaxDarkness, dot(vec3(0.0f, 1.0f, 0.0f), normalize(data.vLightPos))),1.0);
 float nxLight = min(max(fMaxDarkness, dot(vec3(data.vNormal.x, 1.0f, data.vNormal.z), normalize(data.vLightPos))),1.0);
//float nxBump  = max(0.0, dot(vBumpMap.xyz, data.vBumpLight));
//float nxMix = mix(nxLight, nxBump, 0.25);
//vec4 diffuse = vec4((vDiffuseColor.rgb * nxMix), 1.0);
vec4 diffuse = vec4((vDiffuseColor.rgb * nxLight), 1.0);
vec4 ambient = vec4((vAmbientColor * texColor).rgb, 1.0);
 float fAlphaThreshold = 0.10;
 if (texColor.a <= fAlphaThreshold) discard;
 else {
  fragmentColor = vec4(ambient.rgb + (texColor.rgb * diffuse.rgb), texColor.a);
 }
}
