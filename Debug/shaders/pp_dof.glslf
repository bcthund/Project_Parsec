#version 330 core
uniform sampler2D colorMap;
uniform sampler2D depthMap;
out vec4 vFragColor;
in Data {
  in vec2 vTexCoords;
} data;
float fFocalDistance = 0.1f;
//float fAperture = 0.002f;
float fAperture = 0.0015f;
//float near = 1.0;// TODO: Make uniform
//float far = 40000.0;// TODO: Make uniform

float sampleBias(vec2 uv) {
  float d = abs(texture2D(depthMap, uv).r - fFocalDistance);
  return min(d*fAperture, 0.005);
//  float fBlurNear = 0.001f;
//  float fBlurFar = 0.002f;
//  float d = abs(texture2D(depthMap, uv).r - fBlurNear);
//  return min(d*fBlurFar, 0.005);
}

void main(void) {
//  float near = 1.0;// TODO: Make uniform
//  float far = 40000.0;// TODO: Make uniform
  vec3 outColor = vec3(0.0, 0.0, 0.0);
  vec2 delta = vec2(1, 0);
  float bias = sampleBias(data.vTexCoords);
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 4) ).rgb * 0.051/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 3) ).rgb * 0.0918/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 2) ).rgb * 0.12245/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 1) ).rgb * 0.1531/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 0) ).rgb * 0.1633/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 1) ).rgb * 0.1531/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 2) ).rgb * 0.12245/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 3) ).rgb * 0.0918/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 4) ).rgb * 0.051/2;

  delta = vec2(0, 1);
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 4) ).rgb * 0.051/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 3) ).rgb * 0.0918/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 2) ).rgb * 0.12245/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 1) ).rgb * 0.1531/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 0) ).rgb * 0.1633/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 1) ).rgb * 0.1531/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 2) ).rgb * 0.12245/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 3) ).rgb * 0.0918/2;
  outColor+=texture2D(colorMap, (data.vTexCoords - bias * delta * 4) ).rgb * 0.051/2;
  vFragColor = vec4(outColor.rgb, 1.0);
//  vFragColor = vec4( texture2D(colorMap, data.vTexCoords).rgb, 1.0);
}
