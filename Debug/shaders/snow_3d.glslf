#version 330 core
//GLS_SNOW2
out vec4 vFragColor;
uniform sampler2D colorMap;
//in float fAngle;
//in mat2 rot;
void main(void) {
// vec2 p = (gl_PointCoord * 2.0 - vec2(1.0));
// float fA = dot(p, p);
// if (fA > 1.00f) { discard;
//  if (fA > sin(atan(p.y, p.x)*8.0)) { discard; }
//  else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 0.75-fA); }
// } else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 1.0-fA); }
// vFragColor = texture(colorMap, ((gl_PointCoord - vec2(0.5)) * rot)+vec2(0.5));
	vec4 vColor = texture(colorMap, ((gl_PointCoord - vec2(0.5)) )+vec2(0.5));
	if(vColor.a <= 0.99f) discard;
	else vFragColor = vColor;
}
