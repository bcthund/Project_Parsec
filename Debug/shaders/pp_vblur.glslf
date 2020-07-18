#version 330 core
uniform sampler2D colorMap;
out vec4 vFragColor;
//in vec2 blurTexCoords[11];
in vec2 texCoords;
uniform float resolution = 720.0f/2;	// divide because of the smaller image size rendered by FBO
uniform float offset[5] = float[](0.0, 1.0, 2.0, 3.0, 4.0);
uniform float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);
void main(void) {
 //float fFactor[11] = float[]( 0.0093, 0.028002, 0.065984, 0.121703, 0.175713, 0.198596, 0.175713, 0.121703, 0.065984, 0.028002, 0.0093 );
 //vFragColor = vec4(0.0, 0.0, 0.0, 0.0);
 //vFragColor += texture(colorMap, blurTexCoords[0]) * fFactor[0];
 //vFragColor += texture(colorMap, blurTexCoords[1]) * fFactor[1];
 //vFragColor += texture(colorMap, blurTexCoords[2]) * fFactor[2];
 //vFragColor += texture(colorMap, blurTexCoords[3]) * fFactor[3];
 //vFragColor += texture(colorMap, blurTexCoords[4]) * fFactor[4];
 //vFragColor += texture(colorMap, blurTexCoords[5]) * fFactor[5];
 //vFragColor += texture(colorMap, blurTexCoords[6]) * fFactor[6];
 //vFragColor += texture(colorMap, blurTexCoords[7]) * fFactor[7];
 //vFragColor += texture(colorMap, blurTexCoords[8]) * fFactor[8];
 //vFragColor += texture(colorMap, blurTexCoords[9]) * fFactor[9];
 //vFragColor += texture(colorMap, blurTexCoords[10])* fFactor[10];
 
	vFragColor = texture2D(colorMap, texCoords) * weight[0];
    for (int i=1; i<5; i++) {
        vFragColor += texture2D(colorMap, (texCoords + (vec2(0.0, offset[i])/resolution)) ) * weight[i];
        vFragColor += texture2D(colorMap, (texCoords - (vec2(0.0, offset[i])/resolution)) ) * weight[i];
    }
}
