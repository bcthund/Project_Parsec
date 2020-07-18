#version 330 core
uniform vec4 vColor;
uniform sampler2D colorMap;
out vec4 vFragColor;
in vec2 vPassTexCoords;
void main(void) {
	vec4 vTexColor = texture(colorMap, vPassTexCoords.st);
//" if (theColor.a <= 0.01) discard;
//" else vFragColor = effect(theColor, colorMap, vPassTexCoords.st, vVert);
//" else vFragColor = theColor;
//	if(vColor.a <= 0.4f) discard;
//	else vFragColor = vColor;
//	vFragColor = min(vTexColor * vColor, 1.0f);
	vFragColor = vTexColor * vColor;
}
