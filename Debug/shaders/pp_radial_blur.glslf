#version 330 core
// https://stackoverflow.com/questions/4579020/how-do-i-use-a-glsl-shader-to-apply-a-radial-blur-to-an-entire-scene
// Patrick Oscity, Jan 2 '11
// Adapted for use

uniform sampler2D colorMap;
uniform vec2 vFocusPoint = vec2(0.5);
layout (location = 0) out vec4 vFragColor;
in vec2 texCoords;

const float sampleDist = 1.0;
//const float sampleStrength = 2.2;
const float sampleStrength = 50.0;

void main(void) {
	float samples[10];
    samples[0] = -0.08;
    samples[1] = -0.05;
    samples[2] = -0.03;
    samples[3] = -0.02;
    samples[4] = -0.01;
    samples[5] =  0.01;
    samples[6] =  0.02;
    samples[7] =  0.03;
    samples[8] =  0.05;
    samples[9] =  0.08;

    vec2 dir = vFocusPoint - texCoords; 
    float dist = sqrt(dir.x*dir.x + dir.y*dir.y); 
    dir = dir/dist; 

    vec4 color = texture2D(colorMap, texCoords); 
    vec4 sum = color;

    for (int i = 0; i < 10; i++)
        sum += texture2D( colorMap, texCoords + dir * samples[i] * sampleDist );

    sum *= 1.0/11.0;
    float t = dist * sampleStrength;
    t = clamp( t ,0.0,1.0);

    vFragColor = mix( color, sum, t );
}
