#version 330 core
uniform mat4 mvpMatrix;
in vec4 vVertex;
//out vec4 vColor;
void main(void) {
	gl_Position = mvpMatrix * vVertex;
}
