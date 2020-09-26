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

uniform bool bWater = false;

// Single Texture
//uniform sampler2D colorMap;

// Multi-Texture
uniform sampler2D texDirt1;
uniform sampler2D texDirt2;
uniform sampler2D texGrass1;
uniform sampler2D texGrass2;
uniform sampler2D texRocky1;
uniform sampler2D texRocky2;
uniform sampler2D texCliff1;
uniform sampler2D texCliff2;
uniform sampler2D texMud1;
uniform sampler2D texMud2;
uniform sampler2D texWater;

// float fHigh         =  64.0f;
// float fMid          =  48.0f;
// float fLow          =   8.0f;
// float fBottom       =  -8.0f;

float fHigh         =  10000.0f;
float fMid          =   8000.0f;
float fLow          =   1000.0f;
float fLevel        =   -500.0f;
float fBottom       =  -1000.0f;

float fadeHigh      =   2000.0f;//8.0f;
float fadeMid       =   2000.0f;//8.0f;
float fadeLow       =   1000.0f;//8.0f;
float fadeLevel     =    500.0f;//8.0f;
//float fadeBottom    =    100.0f;//8.0f;

layout (location = 0) out vec4 fragmentColor;
in Data {
 in vec3 vVert;
 in vec3 vNormal;
 in vec2 vTexCoords;
} data;

// Types:
//	1: Directional
//	2: Omni
//	3: Spot Light (Hard)
//	4: Spot Light (Soft)
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
		float nxLight = max(maxDarkness, dot(data.vNormal, normalize(vRayDir)));
		vReturnDiffuse = (diffuse / fAtt) * nxLight;
	}
	else {
		float fInnerCutoff = 10.0f;
		float fOuterCutoff = 15.0f;
		vec3 vRayDir = lightPos - data.vVert;
		float fDist = length(vRayDir);
		float fAtt = attenuation.x + (attenuation.y * fDist) + (attenuation.z * fDist * fDist);
		float theta = degrees(acos( dot(-normalize(vRayDir), normalize(lightDir)) ));
		float fIntensity = 1.0f;
		if (type == 4) {
			float fEpsilon = fInnerCutoff - fOuterCutoff;
			fIntensity = clamp((theta - fOuterCutoff) / fEpsilon, 0.0, 1.0);
		}
		if(theta < fOuterCutoff) 
		{
			float nxLight = max(maxDarkness, dot(data.vNormal, normalize(-lightDir)));
			float fMaxDiffuse = max(maxDarkness, (fIntensity / attenuation.x) * nxLight);
			vReturnDiffuse = (diffuse/fAtt) * fMaxDiffuse;
		}
		else vReturnDiffuse = (diffuse/fAtt) * maxDarkness;
	}
return vReturnDiffuse;
}

void main(void) {

    // Standard single texture2D
	vec4 texColor;// = texture2D(colorMap, data.vTexCoords);
	vec3 diffuse = vec3(0);
	vec3 ambient = vec3(0);
	float fMaxDarkness = 0.0;
	float fAlpha = 1.0f;

	// Calculate all lights
	for(int light=0; light<iNumLights; light++) {
		diffuse += AddLight(iType[light], vLightDir[light], vLightPos[light], vDiffuseColor[light], vAmbientColor[light], vSpecularColor[light], vAttenuation[light], fMaxDarkness);
		ambient += vAmbientColor[light].rgb;
	}
	vec3 gamma = vec3(1.0/2.2);
	
	vec3 finalColor;
	
	if(bWater) {
        texColor = texture2D(texWater, data.vTexCoords);
        finalColor = texColor.rgb * (ambient.rgb + diffuse.rgb);
        fAlpha = 0.75f;
	}
	else {
        //MULTI TEXTURE HANDLING
        float t4=0.0f;
        float t3=0.0f;
        float t2=0.0f;
        float t1=0.0f;
        float t0=0.0f;
        float tot=0.0f;
        if (data.vVert.y >= fHigh) { t4=1.0f; tot=1; }
        else if ((data.vVert.y <= fHigh)  && (data.vVert.y > fMid))     { t4=clamp((data.vVert.y-fMid)/fadeHigh,     0.0, 1.0); t3=1-t4; tot=1; }
        else if ((data.vVert.y <= fMid)   && (data.vVert.y > fLow))     { t3=clamp((data.vVert.y-fLow)/fadeMid,      0.0, 1.0); t2=1-t3; tot=1; }
        else if ((data.vVert.y <= fLow)   && (data.vVert.y > fLevel))   { t2=clamp((data.vVert.y-fLevel)/fadeLow,    0.0, 1.0); t1=1-t2; tot=1; }
        else if ((data.vVert.y <= fLevel) && (data.vVert.y > fBottom))  { t1=clamp((data.vVert.y-fBottom)/fadeLevel, 0.0, 1.0); t0=1-t1; tot=1; }
        else if (data.vVert.y <= fBottom) { t0=1.0f; tot=1; } 

        vec4 vNewColor0 = vec4(0.0f),
            vNewColor1 = vec4(0.0f),
            vNewColor2 = vec4(0.0f),
            vNewColor3 = vec4(0.0f),
            vNewColor4 = vec4(0.0f);
        if(t0>0.0f) vNewColor0 = mix( texture2D(texMud1,   data.vTexCoords), texture2D(texMud2,   data.vTexCoords), 1.30-(data.vNormal.y+0.1)) * t0;
        if(t1>0.0f) vNewColor1 = mix( texture2D(texDirt1,  data.vTexCoords), texture2D(texDirt2,  data.vTexCoords), 1.30-(data.vNormal.y+0.1)) * t1;
        if(t2>0.0f) vNewColor2 = mix( texture2D(texGrass1, data.vTexCoords), texture2D(texGrass2, data.vTexCoords), 1.30-(data.vNormal.y+0.1)) * t2;
        if(t3>0.0f) vNewColor3 = mix( texture2D(texRocky1, data.vTexCoords), texture2D(texRocky2, data.vTexCoords), 1.30-(data.vNormal.y+0.1)) * t3;
        if(t4>0.0f) vNewColor4 = mix( texture2D(texCliff1, data.vTexCoords), texture2D(texCliff2, data.vTexCoords), 1.30-(data.vNormal.y+0.1)) * t4;

        texColor = (vNewColor0 + vNewColor1 + vNewColor2 + vNewColor3 + vNewColor4);
    
        finalColor = texColor.rgb * (ambient.rgb + diffuse.rgb);
        //fragmentColor = vec4(pow(finalColor, gamma), texColor.a);
    }
	fragmentColor = vec4(pow(finalColor, gamma), fAlpha);
	
// 	fragmentColor = vec4(texColor.rgb * (vec3(-data.vVert.y/5000.0f, data.vVert.y/5000.0f, 1.0f)*2), 1.0f);
// 	fragmentColor = vec4(texColor.rgb + (vec3(-data.vVert.y/15000.0f, data.vVert.y/15000.0f, 0.0f)), 1.0f);
}
