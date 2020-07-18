#version 330 core
uniform vec4 vColor;
uniform sampler2D colorMap;
in vec2 vPassTexCoords;
in vec3 vPassVertex;
layout (location = 0) out vec4 vFragColor;

void main(void) {
	vec4 theColor = texture(colorMap, vPassTexCoords.st) * vColor;
	//vec4 theColor = texture(colorMap, vPassTexCoords.st);
	if (theColor.a <= 0.01) discard;
	//if (theColor.a <= 0.99) discard;
	else vFragColor = theColor;
}
