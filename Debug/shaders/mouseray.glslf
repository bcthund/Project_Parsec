#version 330 core
layout (location = 0) out vec4 vFragColor;
uniform vec4 vColor = vec4(1.0f);
//out vec4 vFragColor;
void main(void) {
	vFragColor = vColor;
}
