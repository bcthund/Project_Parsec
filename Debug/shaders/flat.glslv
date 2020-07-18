//#version 330 core
//GLS_FLAT
//uniform mat4 mvpMatrix;
//uniform mat4 mvMatrix;
//uniform mat4 mpMatrix;
//in vec4 vVertex;
//in vec4 vNormal;
//in vec2 vTexCoords;
//out Data {
// smooth out vec4 vVert;
// smooth out vec4 vNormal;
// smooth out vec2 vTexCoords;
//} data;
//void main(void) {
// data.vVert = vVertex;
// data.vNormal = vNormal;
// data.vTexCoords = vTexCoords;
// gl_Position = mvpMatrix * vVertex;
//}

#version 330 core
//GLS_FLAT
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
uniform vec3 vLightPos[32];
uniform vec3 vLightDir[32];
uniform vec3 vDiffuseColor[32];
uniform vec3 vAmbientColor[32];
uniform vec3 vSpecularColor[32];
in vec4 vVertex;
in vec4 vNormal;
in vec2 vTexCoords;
out Data {
 smooth out vec4 vVert;
 smooth out vec4 vNormal;
 smooth out vec2 vTexCoords;
 smooth out vec3 vColor;
} data;
void main(void) {
	float fMaxDarkness = 0.0;		// Ambient amount
	float nxLight = min(max(fMaxDarkness, dot(vNormal.xyz, normalize(-vLightDir[0]))),1.0);
	vec3 diffuse = vDiffuseColor[0].rgb * nxLight;
	vec3 ambient = vAmbientColor[0].rgb;

	data.vVert = vVertex;
	data.vNormal = vNormal;
	data.vTexCoords = vTexCoords;
	data.vColor = ambient.rgb + diffuse.rgb;
	gl_Position = mvpMatrix * vVertex;
}
