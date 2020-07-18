#version 330 core
in vec4 vVertex;
uniform mat4 mvpMatrix;
out vec4 vColor;
void main(void) {
//	vec3 vVertN = (normalize(vec3(vVertex.x, vVertex.y, vVertex.z))+1.0f)/2.0f;
//	vec3 vVertN = (normalize(vec3(mvpMatrix * vVertex).xyz)+1.0f)/2.0f;
//	vColor = vec4(1.0f-vVertN.x, 1.0f-vVertN.y, 1.0f-vVertN.z, 1.0f);
//	vColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	gl_Position = mvpMatrix * vVertex;
}
