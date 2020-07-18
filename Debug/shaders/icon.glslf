#version 330 core
uniform vec4 vColor;
uniform sampler2D colorMap;
out vec4 vFragColor;
in vec2 vPassTexCoords;
vec3 blackColor = vec3(0.0, 0.0, 0.0);
void main(void) {
 vec4 theColor = texture(colorMap, vPassTexCoords.st) * vColor;
 if ((theColor.xyz == blackColor) && (theColor.a > 0.01)) theColor.a=1.0f;
 if (theColor.a <= 0.01) discard;
 else vFragColor = theColor;
}
