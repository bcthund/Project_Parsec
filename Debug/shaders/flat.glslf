//#version 330 core
//uniform vec3 vLightPos[32];
//uniform vec3 vLightDir[32];
//uniform vec3 vDiffuseColor[32];
//uniform vec3 vAmbientColor[32];
//uniform vec3 vSpecularColor[32];
//uniform vec3 vDif;
//uniform sampler2D colorMap;
//layout (location = 0) out vec4 fragmentColor;
//in Data {
// smooth in vec3 vVert;
// smooth in vec4 vNormal;
// smooth in vec2 vTexCoords;
//} data;
//float fAlphaThreshold;
//void main(void) {
	//vec4 texColor, vBumpMap, vSpecMap, vAmboMap;
//	vec4 texColor = texture2D(colorMap, data.vTexCoords);
//	float fMaxDarkness = 0.0;		// Ambient amount
//	float nxLight = min(max(fMaxDarkness, dot(data.vNormal.xyz, normalize(-vLightDir[0]))),1.0);
//	vec3 diffuse = vDiffuseColor[0].rgb * nxLight;
//	vec3 ambient = vAmbientColor[0].rgb * texColor.rgb;
	//fAlphaThreshold = 0.01;
	//if (texColor.a <= fAlphaThreshold) discard;
	//else {
//		fragmentColor = vec4(ambient.rgb + (texColor.rgb * diffuse.rgb), texColor.a);
	//	fragmentColor = vec4(1.0);
	//}
	//fragmentColor = vec4(texColor.rgb * vDiffuseColor[0].rgb, 1.0f);
//}

#version 330 core
uniform sampler2D colorMap;
layout (location = 0) out vec4 fragmentColor;
in Data {
 smooth in vec3 vVert;
 smooth in vec4 vNormal;
 smooth in vec2 vTexCoords;
 smooth in vec3 vColor;
} data;
void main(void) {
	//vec4 texColor, vBumpMap, vSpecMap, vAmboMap;
	vec4 texColor = texture2D(colorMap, data.vTexCoords);
	//fAlphaThreshold = 0.01;
	//if (texColor.a <= fAlphaThreshold) discard;
	//else {
		//fragmentColor = vec4(data.vColor.rgb * texColor.rgb, texColor.a);
		fragmentColor = vec4(data.vColor.rgb, 1.0f);
	//	fragmentColor = vec4(1.0);
	//}
	//fragmentColor = vec4(texColor.rgb * vDiffuseColor[0].rgb, 1.0f);
}
