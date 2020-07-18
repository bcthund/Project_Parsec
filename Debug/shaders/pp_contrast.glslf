#version 330 core
uniform sampler2D colorMap;
out vec4 vFragColor;
in vec2 texCoords;
//in vec2 vTexCoords;
uniform float contrast;
void main(void) {
	vFragColor = texture(colorMap, texCoords.st);
	//float t = 0.5 - contrast * 0.5; 
//	vFragColor.rgb = vFragColor.rgb * contrast + t;
	vFragColor.rgb = (vFragColor.rgb - 0.5f) * (max(contrast, 0)+1.0f) + 0.5f;
}
