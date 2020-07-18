#version 330 core
uniform mat4 mvpMatrix;
in vec4 vVertex;
in vec4 vColor;
out vec4 vVertexColor;
//out vec4 vColor;
void main(void) {
	vVertexColor = vColor;
	gl_Position = mvpMatrix * vVertex;
}
