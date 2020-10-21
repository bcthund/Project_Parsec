#version 330 core
layout (location = 0) out vec4 vFragColor;
uniform int iStyle = 0;
uniform vec4 vColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
uniform int iSpikes = 5;
uniform float fThickness = 0.25;
uniform float fAngle = 0.0;
void main(void) {
	float st = sin(fAngle);
	float ct = cos(fAngle);
	mat2 rot = mat2(ct, st, -st, ct);
	vec2 coords = ((gl_PointCoord - vec2(0.5)) * rot)+vec2(0.5);
	vec2 p;
	float dotpp, r, theta;
	if (iStyle>2) {
		p = coords * 2.0 - vec2(1.0);
		dotpp = dot(p,p);
		r = sqrt(dotpp);
		theta = atan(p.y, p.x);
	}
	if(iStyle==0) {
		if (vColor.a < 0.1) discard;
	}
	else if(iStyle==2) {			// Circle
		if(dot(gl_PointCoord-0.5, gl_PointCoord-0.5) > 0.25) discard;
	}
	else if(iStyle==4) {	// Rose
		if (dotpp > cos(theta*iSpikes)) discard;
	}
	else if(iStyle==5) {	// Rose Outline
		if (dotpp > cos(theta*iSpikes) || dotpp < cos(theta*iSpikes)*(1.0-fThickness)) discard;
	}
	else if(iStyle==6) {	// Ring
		if (dotpp > r || dotpp < r*(1.0-fThickness)) discard;
	}
	else if(iStyle==7) {	// Spiral (clipped)
		if (dot(gl_PointCoord-0.5, gl_PointCoord-0.5) > 0.25) discard;
		if (dotpp > 5.0/cos(theta-(6*iSpikes)*r)) discard;
	}
	else if(iStyle==8) {	// Spiral
		if (dotpp > 5.0/cos(theta-(6*iSpikes)*r)) discard;
	}
	else if(iStyle==9) {	// Star (Rounded)
		if (dotpp > 0.5*(exp(cos(theta*iSpikes)*(1.0-fThickness)))) discard;
	}

 	vFragColor = vColor;
// 	vFragColor = vec4(vColor.xyz, 1.0f);
// 	vFragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
