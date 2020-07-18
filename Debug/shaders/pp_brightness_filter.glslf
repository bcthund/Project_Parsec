#version 330 core
uniform sampler2D colorMap;
out vec4 vFragColor;
//in vec2 vTexCoords;
in vec2 texCoords;
//vec3 factor = vec3(0.2126, 0.7152, 0.0722);
//vec3 factor = vec3(0.0626, 0.7252, 0.2122);
uniform vec3 factor = vec3(0.5, 0.5, 0.5);
//float gradient = 0.75f;
//float gradient = 0.55f;
//float gradient = 0.25f;
uniform float fMax = 0.5;
void main(void) {
	vec4 vColor = texture(colorMap, texCoords.st);
// float brightness = (vColor.r * factor.r) + (vColor.g * factor.g) + (vColor.b * factor.b);
	float brightness = dot(vColor.rgb, factor);

//// float brightness = length(vColor)/2;
//// float brightness = (vColor.r + vColor.g + vColor.b) / 3;
//// vFragColor = vec4(vColor.rgb * (brightness * gradient), 1.0);
// vFragColor = vec4(vColor.rgb * (brightness * gradient), vColor.a);
	if (brightness > fMax) {
		vFragColor = vec4(vColor.rgb, 1.0);
	} else {
		vFragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
