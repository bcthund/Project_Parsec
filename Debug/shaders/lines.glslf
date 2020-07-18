#version 330 core
layout (location = 0) out vec4 vFragColor;
//in vec4 vColor;
in vec4 vVertexColor;
//out vec4 vFragColor;
void main(void) {
	vFragColor = vVertexColor;
}
