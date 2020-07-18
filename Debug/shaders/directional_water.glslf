#version 330 core
uniform vec4  vSunDiffuse;
uniform vec4  vSunAmbient;
uniform vec4  vSunSpecular;
uniform float fSunShiny;
uniform vec4  vMoonDiffuse;
uniform vec4  vMoonAmbient;
uniform vec4  vMoonSpecular;
uniform float fMoonShiny;
uniform bool  bReflect;

uniform sampler2D texReflect;
uniform sampler2D texRefract;
uniform sampler2D texDuDv;
uniform sampler2D texNormal;
uniform sampler2D texDepth;

uniform vec3 vEyeVec;
in DataOut {
 smooth in vec2 vTexCoords;
 smooth in vec3 vNormal;
 smooth in vec4 vert;
 smooth in vec3 vSunVector;
 smooth in vec3 vMoonVector;
 smooth in vec3 eyeVec;
 smooth in vec3 vToCamera;
 smooth in vec3 vCamPos;
 smooth in float fTime;
 smooth in vec4 vClipSpace;
} data;
const float fTexRatio        = 40.0;
const float dudvStrength     = 0.05;
const float fRefractStrength = 0.2;
const float fShineDamper     = 20.0;
const float fReflectivity    = 0.5;
const float fNormalDamper    = 3.0;
const float fBlendDepth      = 32.0;

//fsFog_Functions

layout (location = 0) out vec4 fragmentColor;
void main() {

//fsFog_Settings0

// START CALCULATION
 vec2 ndc = (data.vClipSpace.xy/data.vClipSpace.w)/2.0+0.5;
 vec2 reflectCoords = vec2(ndc.x, -ndc.y);
 vec2 refractCoords = vec2(ndc.x, ndc.y);

// Depth Functions
 float near = 10.0;// TODO: Make uniform
 float far = 150000.0;// TODO: Make uniform
 float fDepth = texture(texDepth, refractCoords).r;
 float fFloorDist = 2.0 * near * far / (far + near - (2.0 * fDepth - 1.0) * (far - near));
 fDepth = gl_FragCoord.z;
 float fWaterDist = 2.0 * near * far / (far + near - (2.0 * fDepth - 1.0) * (far - near));
 float fWaterDepth = fFloorDist - fWaterDist;

// DuDv Distortion
 float sin_factor = (sin(data.fTime)+1)/2;
 float cos_factor = (cos(data.fTime)+1)/2;
// vec2 vRotate = vec2(data.vTexCoords.x - (sin_factor+1)/2, data.vTexCoords.y - (sin_factor+1)/2) * mat2(cos_factor, sin_factor, -sin_factor, cos_factor) * fTexRatio;
// vRotate = vec2(vRotate.x + (sin_factor+1)/2, vRotate.y + (sin_factor+1)/2);
 vec2 dudvDistortion1 = texture(texDuDv, vec2(data.vTexCoords.x + sin_factor, data.vTexCoords.y)*fTexRatio).rg * 0.1;
 dudvDistortion1 = data.vTexCoords*fTexRatio + vec2(dudvDistortion1.x, dudvDistortion1.y + cos_factor);
 vec2 dudvDistortion = (texture(texDuDv, dudvDistortion1).rg * 2.0 - 1.0) * dudvStrength * clamp(fWaterDepth/fBlendDepth, 0.0, 1.0);
// vec2 dudvDistortion = (texture(texDuDv, vRotate).rg * 2.0 - 1.0) * dudvStrength;
 if (bReflect==true) {
  reflectCoords += dudvDistortion;
  reflectCoords.x = clamp(reflectCoords.x, 0.001, 0.999);
  reflectCoords.y = clamp(reflectCoords.y, -0.999, -0.001);
 }
 refractCoords += dudvDistortion;
 refractCoords = clamp(refractCoords, 0.001, 0.999);

// Normal
 vec4 normalColor = texture(texNormal, dudvDistortion1);
// vec4 normalColor = texture(texNormal, vRotate);
 vec3 normal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b * fNormalDamper, normalColor.g * 2.0 - 1.0);
normal = normalize(normal);

// Fresnel Effect
 vec3 viewVector = normalize(vEyeVec);
 float fRefractFactor = dot(viewVector, normal);
 fRefractFactor = pow(fRefractFactor, fRefractStrength);
 fRefractFactor = clamp(fRefractFactor, 0.0, 1.0);

// Specular
 vec3 vToCameraNormal = normalize(data.vToCamera);
 vec3 vSunVectorNormal = -data.vSunVector;
 vec3 vMoonVectorNormal = -data.vMoonVector;
 vec3 vReflectedLightSun = reflect(vSunVectorNormal, normal);
 vec3 vReflectedLightMoon = reflect(vMoonVectorNormal, normal);
 float fSpecularSun = max(dot(vReflectedLightSun, vToCameraNormal), 0.0);
 float fSpecularMoon = max(dot(vReflectedLightMoon, vToCameraNormal), 0.0);
 fSpecularSun = pow(fSpecularSun, fShineDamper);
 fSpecularMoon = pow(fSpecularMoon, fShineDamper);
 vec3 vSpecularHighlights = ((vSunSpecular.rgb * fSpecularSun) + (vMoonSpecular.rgb * fSpecularMoon)) * fReflectivity * clamp(fWaterDepth/fBlendDepth, 0.0, 1.0);

//Reflect/Refract
 vec4 reflectColor;
 if (bReflect==true) {
  reflectColor = texture(texReflect, reflectCoords);
 }
 vec4 refractColor = texture(texRefract, refractCoords);

// Output, Water Hue
 if (bReflect==true) {
  fragmentColor = mix(reflectColor, refractColor, fRefractFactor);
  fragmentColor = mix(fragmentColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2) + vec4(vSpecularHighlights, 1.0);
  fragmentColor.a = clamp(fWaterDepth/fBlendDepth, 0.0, 1.0);
 } else {
  fragmentColor = mix(refractColor, vec4(0.0, 0.1, 0.3, 1.0), fRefractFactor) + vec4(vSpecularHighlights, 1.0);
 }
// fragmentColor = vec4(vec3(fWaterDepth/100), 1.0);
}
