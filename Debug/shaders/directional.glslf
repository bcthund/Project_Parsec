#version 330 core
//GLS_DIRECTIONAL
uniform vec4 vLightDiffuse;
uniform vec4 vLightAmbient;
uniform vec4 vLightSpecular;
uniform float fShiny;
uniform vec3 vCamPos;
uniform sampler2D colorMap;
uniform sampler2D bumpMap;
uniform sampler2D specMap;
uniform sampler2D amboMap;
in DataOut {
 smooth in vec2 vTexCoords;
 smooth in vec3 vNormal;
 smooth in vec4 vert;
 smooth in vec3 vLightVector;
 smooth in vec3 bumpLightVector;
} data;
 smooth in vec4 vEyeSpacePos; 

//fsFog_Functions

layout (location = 0) out vec4 fragmentColor;
void main() {

//fsFog_Settings

//LIGHTING CALCULATION
vec4 texColor, vBumpMap, vSpecMap, vAmboMap;
texColor = vec4(texture2D(colorMap, data.vTexCoords).rgb, 1.0);
//vBumpMap = vec4(texture2D(bumpMap, data.vTexCoords).rgb, 1.0)*2.0-1.0;
//vSpecMap = vec4(texture2D(specMap, data.vTexCoords).rgb, 1.0);
//vAmboMap = vec4(texture2D(specMap, data.vTexCoords).rgb, 1.0);
//float nxLight = max(0.0, dot(data.vNormal.xyz, data.vLightVector));
//vec4 diffuse = vec4((vLightDiffuse.rgb * nxLight), 1.0);
//vec4 ambient = vec4((vLightAmbient*texColor).rgb, 1.0);
//fragmentColor = vec4(ambient.rgb + (texColor.rgb * diffuse.rgb), 1.0);
fragmentColor = vec4(texColor.rgb, 1.0);
}
