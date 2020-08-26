#version 330 core
in vec2 vPassTexCoords;
uniform vec2 vRes;
uniform vec2 vPos;
uniform vec2 vSize;
uniform int iRadius = 0;
uniform int iBorder = 1;
uniform bool bRoundBorder = false;
uniform vec4 vWindowColor;
uniform vec4 vBorderColor;
uniform bool bEnableStipple = false;
uniform ivec2 stippleSize = ivec2(0, 0);
uniform int stipplePattern[256];
uniform float stippleScale = 1.0;	// Scale doesn't work
uniform vec4 stippleColor = vec4(0.0, 0.0, 0.0, 1.0);
uniform bool bTextured = false;
//uniform float fScroll;
uniform sampler2D colorMap;
layout (location = 0) out vec4 vFragColor;
//int stipplePatternScaled[1024];
//int stippleScaleActual;

// VERY SLOW and not correct anyway
//void scaleStipple() {
//	stippleScaleActual = min(stippleScale, 4);
//	int i = 0;
//	for(int n=0; n<(stippleSize.x*stippleSize.y)*stippleScaleActual; n+=stippleScale) {
//		for(int t=0; t<stippleScaleActual; t++) {
//			stipplePatternScaled[n+t] = stipplePattern[i];
//		}
//		i++;
//	}
//}

void main(void) {
	vec2 vScreen = (gl_FragCoord.xy-(vRes/2.0f)); //+vec2(0.5,0.5);
	//ivec2 vScreen = ivec2(gl_FragCoord.xy - 0.5); //+vec2(0.5,0.5);

	// Border
	bool bBorderTL = false;
	bool bBorderTR = false;
	bool bBorderBL = false;
	bool bBorderBR = false;

	// Radius Points
	vec2 vTopLeft     = vec2(vPos.x-(vSize.x/2.0f)+iRadius, vPos.y+(vSize.y/2.0f)-iRadius);
	vec2 vTopRight    = vec2(vPos.x+(vSize.x/2.0f)-iRadius, vPos.y+(vSize.y/2.0f)-iRadius);
	vec2 vBottomLeft  = vec2(vPos.x-(vSize.x/2.0f)+iRadius, vPos.y-(vSize.y/2.0f)+iRadius);
	vec2 vBottomRight = vec2(vPos.x+(vSize.x/2.0f)-iRadius, vPos.y-(vSize.y/2.0f)+iRadius);

	// Center Anchor
	bool bRight  = (vScreen.x < vPos.x+(vSize.x/2.0f)) && (vScreen.x > vTopRight.x);
	bool bLeft   = (vScreen.x > vPos.x-(vSize.x/2.0f)) && (vScreen.x < vTopLeft.x);
	bool bTop	 = (vScreen.y < vPos.y+(vSize.y/2.0f)) && (vScreen.y > vTopLeft.y);
	bool bBottom = (vScreen.y > vPos.y-(vSize.y/2.0f)) && (vScreen.y < vBottomRight.y);

	bool bRadius;
	if(iBorder>0) {
		if(bTop&&bLeft) {
			bBorderTL = (length(vScreen.xy-vTopLeft)>=iRadius-iBorder) && ((length(vScreen.xy-vTopLeft)<iRadius) || !bRoundBorder);
			bRadius = length(vScreen.xy-vTopLeft)>iRadius;
		}
		else if(bTop&&bRight) {
			bBorderTR = (length(vScreen.xy-vTopRight)>=iRadius-iBorder) && ((length(vScreen.xy-vTopRight)<iRadius) || !bRoundBorder);
			bRadius = length(vScreen.xy-vTopRight)>iRadius;
		}
		else if(bBottom&&bLeft) {
			bBorderBL = (length(vScreen.xy-vBottomLeft)>=iRadius-iBorder) && ((length(vScreen.xy-vBottomLeft)<iRadius) || !bRoundBorder);
			bRadius = length(vScreen.xy-vBottomLeft)>iRadius;
		}
		else if(bBottom&&bRight) {
			bBorderBR = (length(vScreen.xy-vBottomRight)>=iRadius-iBorder) && ((length(vScreen.xy-vBottomRight)<iRadius) || !bRoundBorder);
			bRadius = length(vScreen.xy-vBottomRight)>iRadius;
		}
	}

	if(bRadius) {
		if(bBorderTL||bBorderTR||bBorderBL||bBorderBR) {
			vFragColor = vBorderColor;
			//vFragColor = vec4(0.0, 0.0, 0.0, 1.0);
		}
		else discard;
	}
	//else if((bTop&&bRight)||(bTop&&bLeft)||(bBottom&&bLeft)||(bBottom&&bRight)) vFragColor = vec4(1, 0, 0, 1);
	else {
		//bool bStipple = stipplePattern[int(mod(coord.x, stippleSize.x) + mod(-coord.y, stippleSize.y) * stippleSize.x)] == 1;
		//scaleStipple();
		vec2 coord = vec2((gl_FragCoord.xy*stippleScale) - 0.5);	// Scale doesn't work
		bool bStipple = stipplePattern[int(mod(coord.x, stippleSize.x) + mod(-coord.y, stippleSize.y) * stippleSize.x)] == 1;
		//bool bStipple = stipplePatternScaled[int(mod(coord.x, stippleSize.x*stippleScaleActual) + mod(-coord.y, stippleSize.y*stippleScaleActual) * (stippleSize.x*stippleScaleActual))] == 1;

		bool bLeftEdge   = vScreen.x <= (vPos.x-(vSize.x/2.0f)+iBorder);
		bool bRightEdge  = vScreen.x >= (vPos.x+(vSize.x/2.0f)-iBorder);
		bool bTopEdge    = vScreen.y >= (vPos.y+(vSize.y/2.0f)-iBorder);
		bool bBottomEdge = vScreen.y <= (vPos.y-(vSize.y/2.0f)+iBorder);

		if( (iBorder>0) && (bLeftEdge||bRightEdge||bTopEdge||bBottomEdge||bBorderTL||bBorderTR||bBorderBL||bBorderBR) ) {
			vFragColor = vBorderColor;
		}
		else if (bEnableStipple && bStipple) {
			vFragColor = stippleColor;
		}
		else {
            if (bTextured) vFragColor = texture(colorMap, vPassTexCoords.st) * vWindowColor;
            else vFragColor = vWindowColor;
        }
	}
}
