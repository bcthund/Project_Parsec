#version 330 core
uniform vec4 vColor;
uniform sampler2D colorMap;
out vec4 vFragColor;
in vec2 vPassTexCoords;
//fs_GetRand
//fs_Bloom
void main(void) {
 vec4 theColor = texture(colorMap, vPassTexCoords.st) * vColor;
  //vFragColor = theColor*2.0;
	vFragColor = theColor;
	vFragColor.a = 1.0;
}
