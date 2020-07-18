#version 330 core
layout (location = 0) out vec4 vFragColor;
uniform sampler2D colorMap;
uniform int iStyle = 0;
uniform vec4 vColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
uniform int iSpikes = 5;
uniform float fThickness = 0.25;
uniform float fAngle = 0.0;
uniform float fBlend = 0.5f;
uniform int iSize = 1;
uniform vec2 vTexCoord0 = vec2(0.0f);
uniform vec2 vTexCoord1 = vec2(0.0f);

//vec2 rotateUV(vec2 uv, float rotation, vec2 mid)
//{
//    return vec2(
//      cos(rotation) * (uv.x - mid.x) + sin(rotation) * (uv.y - mid.y) + mid.x,
//      cos(rotation) * (uv.y - mid.y) - sin(rotation) * (uv.x - mid.x) + mid.y
//    );
//}

void main(void) {
	//if(fAngle != 0.0) {
		float st = sin(fAngle);
		float ct = cos(fAngle);
		mat2 rot = mat2(ct, st, -st, ct);
	//}
	vec2 coordsRaw;
	if (iSize > 1) coordsRaw = ((gl_PointCoord - vec2(0.5)))+vec2(0.5);
	else coordsRaw = ((gl_PointCoord - vec2(0.5)) * rot)+vec2(0.5);
//	vec2 coords = ((gl_PointCoord - vec2(0.5)) * rot)+vec2(0.5);
//	vec2 coordsRaw = ((gl_PointCoord - vec2(0.5)))+vec2(0.5);

	// Texture Coord offset
	vec2 coordsSingle = coordsRaw / iSize;
	float midPoint = (1/iSize/2);
	vec2 coords0 = coordsSingle + vTexCoord0;
	vec2 coords1 = coordsSingle + vTexCoord1;

	//coords0 = rotateUV(coords0, rot, vTexCoord0+midPoint);
	//coords1 = rotateUV(coords1, rot, vTexCoord1+midPoint);


	vec2 p;
	float dotpp, r, theta;
	if (iStyle>2) {
		//p = gl_PointCoord * 2.0 - vec2(1.0);
		p = coordsRaw * 2.0 - vec2(1.0);
		dotpp = dot(p,p);
		r = sqrt(dotpp);
		theta = atan(p.y, p.x);
	}

	vec4 vColor0 = texture(colorMap, coords0);
	vec4 vColor1 = texture(colorMap, coords1);
//	vec4 vTexColor = texture(colorMap, coords);
	vec4 vTexColor = mix(vColor0, vColor1, fBlend);
	vec4 vTintColor = vec4(vTexColor.xyz*vColor.xyz, vTexColor.a*vColor.a);

	if(iStyle==0) {
		if (vTintColor.a < 0.1) discard;
	}
	else if(iStyle==2) {			// Circle
		if(dot(gl_PointCoord-0.5, gl_PointCoord-0.5) > 0.25) discard;
	}
	//else if(iStyle==3) {	// Ellipse
	//}
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
		//if (dotpp > 5.0/cos(theta-(20*(1.0-fThickness))*r)) discard;
		if (dotpp > 5.0/cos(theta-(6*iSpikes)*r)) discard;
	}
	else if(iStyle==9) {	// Star (Rounded)
		if (dotpp > 0.5*(exp(cos(theta*iSpikes)*(1.0-fThickness)))) discard;
		//if (dotpp > cos(theta*iSpikes)) discard;
	}

	vFragColor = vTintColor;
}
