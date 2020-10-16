#version 440 core
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
    data.vVert = vVertex.xyz;
    data.vNormal = vNormal.xyz;
    data.vTexCoords = vTexCoords;

//     data.vData1.r = 0.0f;
//     data.vData1.g = 0.0f;
//     data.vData1.b = 0.0f;
    data.vData1.r = vData1.r;   // Moisture
    data.vData1.g = vData1.g;   // Altitude Offset
    data.vData1.b = vData1.b;   // Extra Data
 
//  data.vMoistureCoords   = vec2(vData1.b, 1.0-((vVertex.y+5000)/50000));
//     data.vMoistureCoords   = vec2(vData1.b, ((vVertex.y+5000)/50000));
    data.vMoistureCoords   = vec2(vData1.r, ((vVertex.y+2500)/50000)+vData1.g );    // VISUALIZE MOISTURE
//     data.vMoistureCoords   = vec2(vData1.g, ((vVertex.y+2500)/50000)+vData1.g );    // VISUALIZE ALTITUDE OFFSET
//     data.vMoistureCoords   = vec2((vData1.b>1-(vData1.r/10)), ((vVertex.y+2500)/50000)+vData1.g );    // VISUALIZE TREES
//     data.vMoistureCoords   = vec2(vData1.b, ((vVertex.y+10000)/50000));
 
 gl_Position = mvpMatrix * vVertex;
}
