#version 440 core
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
// uniform sampler2D texDirt1;
// uniform sampler2D texDirt2;
// uniform sampler2D texGrass1;
// uniform sampler2D texGrass2;
// uniform sampler2D texRocky1;
// uniform sampler2D texRocky2;
// uniform sampler2D texCliff1;
// uniform sampler2D texCliff2;
// uniform sampler2D texMud1;
// uniform sampler2D texMud2;
// uniform sampler2D texSnow1;
// uniform sampler2D texSnow2;
// uniform sampler2D texBeach1;
// uniform sampler2D texBeach2;
// uniform sampler2D texSand1;
// uniform sampler2D texSand2;
//layout (binding=20) uniform sampler2DArray tex3D;
//layout (binding=20) uniform sampler3D tex3D;
layout (binding=0) uniform sampler3D tex3D_0;
layout (binding=1) uniform sampler3D tex3D_1;
layout (binding=2) uniform sampler3D tex3D_2;
layout (binding=3) uniform sampler3D tex3D_3;
layout (binding=4) uniform sampler3D tex3D_4;
// uniform sampler2D texAtlas;
// uniform sampler2D texMoisture;
uniform sampler2D texWater;

layout (location = 0) out vec4 fragmentColor;
in Data {
 in vec3 vVert;
 in vec3 vNormal;
 in vec2 vTexCoords;
 in vec3 vData1;        // [0] = Moisture, [1] = Altitude Offset, [2] = undefined
 in vec2 vMoistureCoords;
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
    vec4 texColor;
	vec3 finalColor;
    vec3 diffuse = vec3(0);
	vec3 ambient = vec3(0);
	float fMaxDarkness = 0.05;
	float fAlpha = 1.0f;
	//vec3 gamma = vec3(1.0/2.2);
	vec3 gamma = vec3(1.0/1.25);
	
    for(int light=0; light<iNumLights; light++) {
		diffuse += AddLight(iType[light], vLightDir[light], vLightPos[light], vDiffuseColor[light], vAmbientColor[light], vSpecularColor[light], vAttenuation[light], fMaxDarkness);
		ambient += vAmbientColor[light].rgb;
	}

	if(bWater) {
        texColor = texture2D(texWater, data.vTexCoords);
        finalColor = texColor.rgb * (ambient.rgb + diffuse.rgb);
        fAlpha = 0.65f;
	}
	else {
        // Testing of 3D Layers
    //     vec4 vNewColor0 = texture(tex3D_0, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t));
    //     vec4 vNewColor0 = texture(tex3D_1, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t));
    //     vec4 vNewColor0 = texture(tex3D_2, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t));
    //     vec4 vNewColor0 = texture(tex3D_3, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t));
    //     vec4 vNewColor0 = texture(tex3D_4, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t));
    
        // Testing of Tree Noise
//         if(data.vMoistureCoords.s>0.5f) texColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//         else texColor = vec4(0.0f, 1-(data.vData1.r/5.0f), (data.vData1.r/5.0f), 1.0f);

        // Setup
        float t0=0.0f;
        float t1=0.0f;
        float t2=0.0f;
        float t3=0.0f;
        float t4=0.0f;
        float fade=0.75f;
        vec4 vNewColor0 = vec4(0.0f),
            vNewColor1 = vec4(0.0f),
            vNewColor2 = vec4(0.0f),
            vNewColor3 = vec4(0.0f),
            vNewColor4 = vec4(0.0f);
        
        // Moisture Levels
        float f4_Wet    = 5.0f,
              f3_Moist  = 4.0f,
              f2_Mud    = 3.0f,
              f1_Dry    = 2.0f,
              f0_Barren = 1.0f;
        
        // Calculate Moisture Influence
        if (data.vMoistureCoords.s >= f4_Wet) { t4=1.0f; }
        else if ((data.vMoistureCoords.s <= f4_Wet)   && (data.vMoistureCoords.s > f3_Moist))   { t4=clamp((data.vMoistureCoords.s-f3_Moist)/fade,  0.0, 1.0); t3=1-t4; }
        else if ((data.vMoistureCoords.s <= f3_Moist) && (data.vMoistureCoords.s > f2_Mud))     { t3=clamp((data.vMoistureCoords.s-f2_Mud)/fade,    0.0, 1.0); t2=1-t3; }
        else if ((data.vMoistureCoords.s <= f2_Mud)   && (data.vMoistureCoords.s > f1_Dry))     { t2=clamp((data.vMoistureCoords.s-f1_Dry)/fade,    0.0, 1.0); t1=1-t2; }
        else if ((data.vMoistureCoords.s <= f1_Dry)   && (data.vMoistureCoords.s > f0_Barren))  { t1=clamp((data.vMoistureCoords.s-f0_Barren)/fade, 0.0, 1.0); t0=1-t1; }
        else if (data.vMoistureCoords.s  <= f0_Barren) { t0=1.0f; } 

        // Apply Influence
        if(t0>0.0f) vNewColor0 = texture(tex3D_0, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t)) * t0;
        if(t1>0.0f) vNewColor1 = texture(tex3D_1, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t)) * t1;
        if(t2>0.0f) vNewColor2 = texture(tex3D_2, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t)) * t2;
        if(t3>0.0f) vNewColor3 = texture(tex3D_3, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t)) * t3;
        if(t4>0.0f) vNewColor4 = texture(tex3D_4, vec3(data.vTexCoords.s, data.vTexCoords.t, data.vMoistureCoords.t)) * t4;
        texColor = (vNewColor0 + vNewColor1 + vNewColor2 + vNewColor3 + vNewColor4);
    }
    
    //vec3 texColor = vNewColor0.rgb + vec3(0.1f);
    finalColor = texColor.rgb * (ambient.rgb + diffuse.rgb);
    fragmentColor = vec4(pow(finalColor, gamma), fAlpha);
//     fragmentColor = vec4(finalColor, fAlpha);
}
