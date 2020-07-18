#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;

uniform vec3 vLightPos[32];
uniform vec3 vLightDir[32];
uniform vec3 vDiffuseColor[32];
uniform vec3 vAmbientColor[32];
uniform vec3 vSpecularColor[32];
uniform vec3 vAttenuation[32];
uniform uint uiType[32];
uniform vec3 vDif;
uniform sampler2D colorMap;
layout (location = 0) out vec4 fragmentColor;
in Data {
 smooth in vec3 vVertex;
 smooth in vec4 vNormal;
 smooth in vec2 vTexCoords;
} data;
float fAlphaThreshold;
void main(void) {
	//vec4 texColor, vBumpMap, vSpecMap, vAmboMap;
	vec4 texColor = texture2D(colorMap, data.vTexCoords);
	vec3 diffuse;
	float fMaxDarkness = 0.1;		// Ambient amount

	vec3 vRayDir = vLightPos[0] - (mvMatrix * vec4(data.vVertex.xyz, 1.0f)).xyz;

	if (uiType[0] == uint(1)) {
		float nxLight = min(max(fMaxDarkness, dot(data.vNormal.xyz, normalize(-vLightDir[0]))),1.0);
		diffuse = vDiffuseColor[0].rgb * nxLight;
	}
	else if (uiType[0] == uint(2)) {
		fMaxDarkness = 0.1;
		float fDist = length(vRayDir);
		float fAtt = vAttenuation[0].x + (vAttenuation[0].y * fDist) + (vAttenuation[0].z * fDist * fDist);
		float nxLight = min(max(fMaxDarkness, dot(data.vNormal.xyz, normalize(vRayDir))),1.0);
		diffuse = (vDiffuseColor[0].rgb / fAtt) * nxLight;
	}
	//else if (uiType[0] == uint(3)) {
	//	float fCutOff = cos(radians(15.0f));
	//	float theta = dot(data.vRayDir[0], normalize(-vLightDir[0]));
	//	if(theta > fCutOff) 
	//	{
	//		float nxLight = min(max(fMaxDarkness, dot(data.vNormal.xyz, normalize(-vLightDir[0]))),1.0);
	//		diffuse = vDiffuseColor[0].rgb * nxLight;
	//	}
	//	else diffuse = vDiffuseColor[0].rgb * fMaxDarkness;
	//}
	vec3 ambient = vAmbientColor[0].rgb * texColor.rgb;
	//fAlphaThreshold = 0.01;
	//if (texColor.a <= fAlphaThreshold) discard;
	//else {
		//vec3 minColor = min(ambient.rgb + (texColor.rgb * diffuse.rgb) ,1.0f);
		fragmentColor = vec4(ambient.rgb + (texColor.rgb * diffuse.rgb), texColor.a);
	//	fragmentColor = vec4(1.0);
	//}
	//fragmentColor = vec4(texColor.rgb * vDiffuseColor[0].rgb, 1.0f);
}
