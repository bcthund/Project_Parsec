#version 330 core
uniform vec4 vColor;
uniform vec4 vDiffuseColor;
uniform vec4 vAmbientColor;
uniform vec4 vSpecularColor;
uniform vec3 vLightPos;
uniform sampler2D colorMap;
layout (location = 0) out vec4 fragmentColor;
//inout Data {
smooth in vec2 vTexCoord;
//} data;
smooth in vec4 vEyeSpacePosOut; 
vec4 vEyeSpacePos = vEyeSpacePosOut;
float fAlphaThreshold;
//fsFog_Functions
void main(void) {
//fsFog_Settings0

//Calc Texel
// vec4 texColor = texture(colorMap, data.vTexCoords.st) * vColor;

//Lighting Calc
 vec3 vLightVector = normalize(vLightPos);
 vec4 texColor = texture2D(colorMap, vTexCoord);
 float fMaxDarkness = 0.05;
 float nxLight = max(dot(vec3(vLightVector.x, 1.0, vLightVector.z), vLightVector), fMaxDarkness);
 vec4 diffuse = vec4(vDiffuseColor.rgb * nxLight, 1.0);
 vec4 ambient = vec4((vAmbientColor*texColor).rgb, 1.0);

//Discard low alpha values
// fAlphaThreshold = 0.50;
 fAlphaThreshold = 0.01;
 if (texColor.a <= fAlphaThreshold) discard;
 else {
//fsFog_texColor
 texColor.rgb *= diffuse.rgb;
// fragmentColor = texColor;
 fragmentColor = vec4(ambient.rgb + texColor.rgb, texColor.a);
 }
}
