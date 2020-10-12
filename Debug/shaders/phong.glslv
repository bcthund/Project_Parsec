#version 330 core
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mpMatrix;
in vec4 vVertex;
in vec4 vNormal;
in int vIndex;
in vec2 vTexCoords;
in vec3 vData1;
out Data {
 out vec3 vVert;
 out vec3 vNormal;
 out vec2 vTexCoords;
 out vec3 vData1;
 out vec2 vMoistureCoords;
} data;
void main(void) {
// data.vVert = (mvMatrix * vVertex).xyz;
 data.vVert = vVertex.xyz;
 data.vNormal = vNormal.xyz;
 data.vTexCoords = vTexCoords;
 
 data.vData1.r = 0.0f;
 data.vData1.g = 0.0f;
 data.vData1.b = 0.0f;
 //data.vData1 = vec4(mvpMatrix * vec4(vData1, 0.0f)).xyz;
 //data.vData1 = vData1 * normalize(vVertex.xyz);
 //data.vData1.g = (vData1.b*(1.0f-(vVertex.y/15000.0f)+0.5f));
//  data.vData1.g = 1.0f-(vVertex.y/15000.0f)+0.5f);
//  data.vData1.g = (1.0f-(vVertex.y/15000.0f));
//  data.vData1.r = (vVertex.y/15000.0f);
//  data.vData1.g = vData1.b;
//   data.vData1.b = vData1.b * (vVertex.y/15000.0f);

//  if(vVertex.y>=0.0f) data.vData1.b = vData1.b;//*2.0f;
//  else data.vData1.b = 1.0f;
 data.vData1.b = vData1.b;
 
 data.vMoistureCoords   = vec2(vData1.b, 1.0-((vVertex.y+5000)/50000));
 //data.vMoistureCoords   = vec2(vData1.b, 1.0-((vVertex.y-10000)/150000));
 //data.vMoistureCoords = vec2(vData1.b, vVertex.y/150000.0f);
 //data.vMoistureCoords = vec2(vData1.b, (vVertex.y-5000.0f)/150000.0f);
 //data.vMoistureCoords = vec2(vData1.b, vVertex.y/150000.0f);
 
 gl_Position = mvpMatrix * vVertex;
}
