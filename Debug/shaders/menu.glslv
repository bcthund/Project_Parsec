#version 330 core
uniform mat4 mvpMatrix;
uniform float fScroll;
in vec4 vVertex;
in vec2 vTexCoords;
out vec2 vPassTexCoords;
void main(void) {
    vPassTexCoords = vec2(vTexCoords.s, vTexCoords.t+fScroll);
    //vPassTexCoords = vTexCoords;
	gl_Position = mvpMatrix * vVertex;
}
