#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform int  iNumLights;
uniform int  iType[32];
uniform vec3 vLightDir[32];
uniform vec3 vLightPos[32];
uniform vec3 vDiffuseColor[32];
uniform vec3 vAmbientColor[32];
uniform vec3 vSpecularColor[32];
uniform vec3 vAttenuation[32];
uniform sampler2D colorMap;
layout (location = 0) out vec4 fragmentColor;
in Data {
 in vec3 vVert;
 in vec3 vNormal;
 in vec2 vTexCoords;
} data;

vec3 AddLight(int type, vec3 lightDir, vec3 lightPos, vec3 diffuse, vec3 ambient, vec3 specular, vec3 attenuation, float maxDarkness) {
	vec3 vReturnDiffuse = vec3(0);
	if (type == 1) {
		float nxLight = max(maxDarkness, dot(data.vNormal, normalize(-lightDir)));
		vReturnDiffuse = diffuse * nxLight;
	}
	else if (type == 2) {
		maxDarkness = 0.1;
		vec3 vRayDir = lightPos - data.vVert;
		float fDist = length(vRayDir);
		float fAtt = attenuation.x + (attenuation.y * fDist) + (attenuation.z * fDist * fDist);
		//float fAtt = attenuation.x / ((1+attenuation.y * fDist) * (1+attenuation.z * fDist * fDist));
		//float fAtt = fDist * attenuation.x;
		float nxLight = max(maxDarkness, dot(data.vNormal, normalize(vRayDir)));
		vReturnDiffuse = (diffuse / fAtt) * nxLight;
	}
	else {
		//float fInnerCutoff = cos(radians(15.0f));
		//float fOuterCutoff = cos(radians(20.0f));
		float fInnerCutoff = 5.0f;
		float fOuterCutoff = 20.0f;
		vec3 vRayDir = lightPos - data.vVert;
		//float fDist = length(vRayDir);
		//float fAtt = attenuation.x + (attenuation.y * fDist) + (attenuation.z * fDist * fDist);
		//vec3 vRayDir = normalize(lightPos - data.vVert);
		float theta = degrees(acos( dot(-normalize(vRayDir), normalize(lightDir)) ));
		//float theta = dot(-vRayDir, normalize(vLightDir[0]));
		float fIntensity = 1.0f;
		if (type == 4) {
			float fEpsilon = fInnerCutoff - fOuterCutoff;
			fIntensity = clamp((theta - fOuterCutoff) / fEpsilon, 0.0, 1.0);
		}
		//if(theta > fInnerCutoff) 
		if(theta < fOuterCutoff) 
		{
			//float nxLight = min(max(maxDarkness, dot(data.vNormal, normalize(-lightDir))),1.0);
			float nxLight = max(maxDarkness, dot(data.vNormal, normalize(-lightDir)));
			float fMaxDiffuse = max(maxDarkness, (fIntensity / attenuation.x) * nxLight);
			//vReturnDiffuse = diffuse * fMaxDiffuse;
			//vReturnDiffuse = (diffuse / fAtt) * fMaxDiffuse;
			vReturnDiffuse = diffuse * fMaxDiffuse;
		}
		else vReturnDiffuse = diffuse * maxDarkness;
	}
return vReturnDiffuse;
}

void main(void) {
    float fAlphaThreshold = 0.01;
	//vec4 texColor, vBumpMap, vSpecMap, vAmboMap;
	vec4 texColor = texture2D(colorMap, data.vTexCoords);
	if(texColor.a < fAlphaThreshold) discard;
	else {
        vec3 diffuse = vec3(0);
        vec3 ambient = vec3(0);
        float fMaxDarkness = 0.0;

        for(int light=0; light<iNumLights; light++) {
            diffuse += AddLight(iType[light], vLightDir[light], vLightPos[light], vDiffuseColor[light], vAmbientColor[light], vSpecularColor[light], vAttenuation[light], fMaxDarkness);
            //ambient += vAmbientColor[light].rgb * texColor.rgb;
        }
        //fragmentColor = vec4(ambient.rgb + (texColor.rgb * diffuse.rgb), texColor.a);
        vec3 gamma = vec3(1.0/2.2);
        vec3 finalColor = ambient.rgb + (texColor.rgb * diffuse.rgb);
        fragmentColor = vec4(pow(finalColor, gamma), texColor.a);
    }
}
