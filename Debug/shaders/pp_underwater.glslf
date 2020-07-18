#version 330 core
uniform vec4 vColor;
uniform sampler2D colorMap;
uniform sampler2D texDuDv;
uniform float fTime;
in Data {
  in vec2 vTexCoords;
} data;
out vec4 vFragColor;
void main(void) {
 const float fTexRatio = 1.0;
 const float dudvStrength = 0.01;
 vec2 vRc = data.vTexCoords;
 float sin_factor = (sin(fTime)+1)/2;
 float cos_factor = (cos(fTime)+1)/2;
 vec2 dudvDistortion1 = texture(texDuDv, vec2(data.vTexCoords.x + sin_factor, data.vTexCoords.y)*fTexRatio).rg * 0.1;
 dudvDistortion1 = data.vTexCoords*fTexRatio + vec2(dudvDistortion1.x, dudvDistortion1.y + cos_factor);
 vec2 dudvDistortion = (texture(texDuDv, dudvDistortion1).rg * 2.0 - 1.0) * dudvStrength;
 vRc += dudvDistortion;
 vRc = clamp(vRc, 0.001, 0.999);
 vec4 refractColor = texture(colorMap, vRc);
 vFragColor = mix(refractColor, vec4(vColor.rgb, 1.0), vColor.a);
}
