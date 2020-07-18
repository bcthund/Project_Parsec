#version 330 core
out vec4 vFragColor;
//uniform sampler2D colorMap;
//in float fAngle;
void main(void) {
 vec2 p = (gl_PointCoord * 2.0 - vec2(1.0));
 float fA = dot(p, p);
 if (fA > 1.00f) { discard;
//  if (fA > sin(atan(p.y, p.x)*8.0)) { discard; }
//  else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 0.75-fA); }
// } else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 1.0-fA); }
 } else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 1.0-pow(fA,2)); }
// vFragColor = texture(colorMap, ((gl_PointCoord - vec2(0.5)) * rot)+vec2(0.5));
}
