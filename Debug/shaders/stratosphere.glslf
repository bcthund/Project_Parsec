#version 330 core
uniform vec4 vSunDiffuse;
uniform vec4 vSunAmbient;
uniform vec4 vSunSpecular;
uniform float fSunShiny;
uniform vec4 vMoonDiffuse;
uniform vec4 vMoonAmbient;
uniform vec4 vMoonSpecular;
uniform float fMoonShiny;
uniform sampler2D colorMap;
uniform sampler2D bumpMap;
uniform vec3 vCamPos;
layout (location = 0) out vec4 fragmentColor;
in Data {
 smooth in vec3 vNormal;
 smooth in vec3 vVert;
 smooth in vec2 vTexCoords;
 smooth in vec3 vSunVector;
 smooth in vec3 vMoonVector;
 smooth in vec3 vCamVector;
} data;
float fAlphaThreshold;

//fs_GetTangent

void main(void) {
//Discard low alpha values
 float fScale = 5;
 fAlphaThreshold = 0.01;
 vec4 texColor, vBumpMap, vAmboMap;
 texColor = texture2D(colorMap, data.vTexCoords*fScale);
 if (texColor.a <= fAlphaThreshold) discard;
 else {

//Bump Mapping
//  vec3 tangent, binormal;
//  tangent  = normalize(cross(data.vNormal, vec3(0.0, 1.0, 0.0)));
//  binormal = normalize(cross(tangent, data.vNormal));
//  mat3 TBNMatrix = mat3(tangent, binormal, data.vNormal);
//  mat3 TBNMatrix = GetTangent(data.vNormal);
//  vec3 vBumpV1 = data.vSunVector*TBNMatrix;
//  vec3 vBumpV2 = data.vMoonVector*TBNMatrix;
  vec3 vBumpV1 = vec3(data.vSunVector.x, data.vSunVector.y, data.vSunVector.z);
  vec3 vBumpV2 = data.vMoonVector;

//EX: vec4 normalColor = texture(texNormal, dudvDistortion1);
//EX: vec3 normal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b * fNormalDamper, normalColor.g * 2.0 - 1.0);
//EX: normal = normalize(normal);
//  vBumpMap = vec4(texture2D(bumpMap, data.vTexCoords*fScale).rgb, 1.0) * 2.0-1.0;
  vec4 normalColor = texture(bumpMap, data.vTexCoords*fScale);
  vec3 normal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b, normalColor.g * 2.0 - 1.0);
  normal = normalize(normal);
  float fMaxDarkness = 0.1;
//  float nxSun  = max(fMaxDarkness, dot(vec3(0.0f, 1.0f, 0.0f),  vBumpV1));
  float nxSun  = max(fMaxDarkness, dot(normal,  vBumpV1));
//  float nxSun  =          max(fMaxDarkness, dot(vBumpMap.xyz, vBumpV1));
  float nxBump = max(fMaxDarkness, dot(normal, vBumpV1));
  float nxMoon = min(0.5, max(fMaxDarkness, dot(normal, vBumpV2)));

//Specular
//float fSpecPow = 0.0;
  vec3 specular;
  float fSpecStrength = 0.5;
  if (nxSun != 0.0) {
// vec3  vCamVector = normalize(vCamPos.xyz - data.vVert.xyz);
 vec3  vCamVector = normalize(data.vCamVector);
 vec3  vHalf = normalize(vec3(data.vSunVector.x, data.vSunVector.y, data.vSunVector.z) + vec3(vCamVector.x, vCamVector.y, vCamVector.z));
 float nxHalf = max(0.0, dot(normal, vHalf));
 float fSpecPow = pow(nxHalf, fSunShiny);
    specular = (vSunSpecular.rgb * fSpecPow * fSpecStrength);
  }

//Colors
//  vec4 diffuse = vec4((vSunDiffuse.rgb*((nxSun+nxBump)/2)*texColor.rgb)+(vMoonDiffuse.rgb*nxMoon*texColor.rgb), 1.0);
  vec4 diffuse = vec4((vSunDiffuse.rgb*(nxSun)*texColor.rgb)+(vMoonDiffuse.rgb*nxMoon*texColor.rgb), 1.0);
  vec4 ambient = vec4((vSunAmbient * texColor).rgb + (vMoonAmbient * texColor).rgb, 1.0);
//  fragmentColor = vec4(ambient.rgb + diffuse.rgb + specular.rgb, texColor.a);
  fragmentColor = vec4(ambient.rgb + diffuse.rgb, texColor.a);
//  fragmentColor = vec4(ambient.rgb + diffuse.rgb, 1.0);
 }
}
