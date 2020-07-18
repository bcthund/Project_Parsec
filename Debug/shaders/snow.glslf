#version 330 core
out vec4 vFragColor;
uniform sampler2D colorMap;
in float fAngle;
void main(void) {
 float st = sin(fAngle);
 float ct = cos(fAngle);
 mat2 rot = mat2(ct, st, -st, ct);
// vec2 p = rot * (gl_PointCoord * 2.0 - vec2(1.0));
// float fA = dot(p, p);
 vFragColor = texture(colorMap, ((gl_PointCoord - vec2(0.5)) * rot)+vec2(0.5));

// if (fA > 0.25f) {
//  if (fA > sin(atan(p.y, p.x)*8.0)) { discard; }
//  else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 0.75-fA); }
// } else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 0.75-fA); }

//  if (fA > sin(atan(p.y, p.x)*8.0) || fA < (0.1)) { discard; }
//  else { vFragColor = vec4(1.0f, 1.0f, 1.0f, 1.00-fA); }
};

//if (fA < 0.5f)//HALO
//  if (fA < 0.5f)//COOL SHAPE, SECONDARY TEST
// if (fA > atan(p.y, cos(p.x+st)))//TEARDROP LIKE
// if (fA > sin(atan(cos(p.y), p.x)*5.0))//LEAF FUNCTION
