#version 330 core
uniform sampler2D colorMap;
out vec4 vFragColor;
//in vec2 vTexCoords;
in vec2 texCoords;
//vec3 factor = vec3(0.2126, 0.7152, 0.0722);
//vec3 brightness = vec3(1.25, 1.75, 1.25);
uniform vec3 brightness = vec3(1.25, 1.75, 1.25);
//float gradient = 0.75f;
//float gradient = 0.55f;
//float gradient = 0.25f;
//float brightness = 1.25;
void main(void) {
// vec4 vColor = texture(colorMap, texCoords.st);
// float brightness = (vColor.r * factor.r) + (vColor.g * factor.g) + (vColor.b * factor.b);
//// float brightness = length(vColor)/2;
//// float brightness = (vColor.r + vColor.g + vColor.b) / 3;
//// vFragColor = vec4(vColor.rgb * (brightness * gradient), 1.0);
// vFragColor = vec4(vColor.rgb * (brightness * gradient), vColor.a);
//// if (brightness > 0.8) {
////  vFragColor = vec4(vColor.rgb, 1.0);
//// } else {
////  vFragColor = vec4(0.0, 0.0, 0.0, 1.0);
	vFragColor = texture(colorMap, texCoords.st);
	//vFragColor.rgb *= brightness;
	vFragColor.rgb += min(brightness, 1.0f);
}
