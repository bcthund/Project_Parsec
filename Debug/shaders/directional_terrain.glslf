#version 330 core
uniform vec4  vSunDiffuse;
uniform vec4  vSunAmbient;
uniform vec4  vSunSpecular;
uniform float fSunShiny;
uniform vec4  vMoonDiffuse;
uniform vec4  vMoonAmbient;
uniform vec4  vMoonSpecular;
uniform float fMoonShiny;
uniform vec3  vCamPos;
uniform bool  bUnderwater;
uniform float fTime;
uniform sampler2D texDirt1;
uniform sampler2D texDirt2;
uniform sampler2D texGrass1;
uniform sampler2D texGrass2;
uniform sampler2D texRocky1;
uniform sampler2D texRocky2;
uniform sampler2D texCliff1;
uniform sampler2D texCliff2;
uniform sampler2D texDuDv;
uniform sampler2D texNormal;
in DataOut {
 smooth in vec2 vTexCoords;
 smooth in vec3 vNormal;
 smooth in vec4 vert;
 smooth in vec3 vSunVector;
 smooth in vec3 vMoonVector;
 smooth in vec3 vCamPos;
 smooth in vec3 eyeVec;
 smooth in vec3 vLampVector;
// smooth in vec4 vClipSpace;
 smooth in vec3 vToCamera;
} data;
 smooth in vec4 vEyeSpacePos; 

//fsFog_Functions

layout (location = 0) out vec4 fragmentColor;
void main() {
const float fTexRatio = 1.0f;
const float fShineDamper     = 5.0;
//const float fReflectivity    = 0.2;
const float fReflectivity    = 0.2;
const float fNormalDamper    = 1.0;

//fsFog_Settings

// Specular
 vec3 vToCameraNormal = normalize(data.vToCamera);
 vec3 vSunVectorNormal = -data.vSunVector;
 vec3 vMoonVectorNormal = -data.vMoonVector;
 vec3 vReflectedLightSun = reflect(vSunVectorNormal, data.vNormal);
 vec3 vReflectedLightMoon = reflect(vMoonVectorNormal, data.vNormal);
 float fSpecularSun = max(dot(vReflectedLightSun, vToCameraNormal), 0.0);
 float fSpecularMoon = max(dot(vReflectedLightMoon, vToCameraNormal), 0.0);
 fSpecularSun = pow(fSpecularSun, fShineDamper);
 fSpecularMoon = pow(fSpecularMoon, fShineDamper);
 vec3 vSpecularHighlights = mix(vSunSpecular.rgb * fSpecularSun, vMoonSpecular.rgb * fSpecularMoon, 0.5) * fReflectivity;

//LIGHTING CALCULATION
 float fMaxDarkness = 0.1;
 float nxSun = max(dot(data.vNormal, data.vSunVector), fMaxDarkness);
 float nxMoon = max(dot(data.vNormal, data.vMoonVector), fMaxDarkness);
 vec4 texColor;

// TODO: LAMP
// TODO: Custom lamp color, also add flicker to brightness
// vec3 nLampPos = normalize(vec3(data.vCamPos.x, 1.0, data.vCamPos.z));
 vec3 nLampVector = normalize(data.vLampVector);
 float nxLamp = max(dot(data.vNormal, nLampVector), fMaxDarkness) * 10;
 vec3 attenuation = vec3(1f, 0.0005f, 0.00005f);
 float distance = length(data.vLampVector);
 float fAttFactor = attenuation.x+(attenuation.y*distance) + (attenuation.z*distance*distance);
 vec4 lamp = vec4(vec3(0.91, 0.83, 0.52)*nxLamp, 1.0)/fAttFactor;
// vec4 lamp = vec4(vec3(0.91, 0.83, 0.52)*nxLamp, 1.0)/distance;

//MULTI TEXTURE HANDLING
 float fade=8.0f;
 float t3=0.0f;
 float t2=0.0f;
 float t1=0.0f;
 float t0=0.0f;
 float tot=0.0f;
 if (data.vert.y >= 64) { t3=1.0f; tot=1; }
 else if ((data.vert.y <= 64) && (data.vert.y > 48)) { t3=clamp((data.vert.y-48)/fade, 0.0, 1.0); t2=1-t3; tot=1; }
 else if ((data.vert.y <= 48) && (data.vert.y > 8))  { t2=clamp((data.vert.y-8)/fade, 0.0, 1.0); t1=1-t2; tot=1; }
 else if ((data.vert.y <= 8) && (data.vert.y > -8))  { t1=clamp((data.vert.y+8)/fade, 0.0, 1.0);  t0=1-t1; tot=1; }
 else if (data.vert.y <= -8) { t0=1.0f; tot=1; } 

 vec4 vNewColor0 = vec4(0.0f),
      vNewColor1 = vec4(0.0f),
      vNewColor2 = vec4(0.0f),
      vNewColor3 = vec4(0.0f);
 if(t0>0.0f) vNewColor0 = mix( texture2D(texDirt1,  data.vTexCoords), texture2D(texDirt2,  data.vTexCoords), 1.2-(data.vNormal.y+0.2)) * t0;
 if(t1>0.0f) vNewColor1 = mix( texture2D(texGrass1, data.vTexCoords), texture2D(texGrass2, data.vTexCoords), 1.2-(data.vNormal.y+0.2)) * t1;
 if(t2>0.0f) vNewColor2 = mix( texture2D(texRocky1, data.vTexCoords), texture2D(texRocky2, data.vTexCoords), 1.2-(data.vNormal.y+0.2)) * t2;
 if(t3>0.0f) vNewColor3 = mix( texture2D(texCliff1, data.vTexCoords), texture2D(texCliff2, data.vTexCoords), 1.2-(data.vNormal.y+0.2)) * t3;

 texColor = (vNewColor0 + vNewColor1 + vNewColor2 + vNewColor3);
 vec4 ambient = (vSunAmbient * texColor) + (vMoonAmbient * texColor);
 vec4 diffuse = vec4((vSunDiffuse.rgb*nxSun),1.0) + vec4((vMoonDiffuse.rgb*nxMoon),1.0);
// TODO: This kinda works but needs adjustment
// diffuse += lamp;
 texColor *= diffuse;
//fsFog_texColor

//OUTPUT FINAL COLOR WITH LIGHTING TO SCENE
 fragmentColor = vec4(ambient.rgb + texColor.rgb, 1.0) + vec4(vSpecularHighlights, 1.0);
// fragmentColor = vec4(ambient.rgb + texColor.rgb, 1.0);
 gl_FragDepth = gl_FragCoord.z;
// fragmentColor = vec4(ambient.rgb + texColor.rgb + specular.rgb, 1.0);
}
