uniform float factor;
uniform sampler2D colorMap;

#define PI 3.14159

vec4 blink(vec4 color)
{
	//float f1 = cos(factor * 2) / 2.f + 0.5;
	//float f2 = cos(factor * 2 + PI * 2.f / 3) / 2.f + 0.5;
	//float f3 = cos(factor * 2 + PI * 4.f / 3) / 2.f + 0.5;
	
	//vec4 c;
	//c.r = color.r * f1 + color.g * f2 + color.b * f3;
	//c.g = color.g * f1 + color.b * f2 + color.r * f3;
	//c.b = color.b * f1 + color.r * f2 + color.g * f3;
	//c.a = color.a;
	
	return color;
}

vec4 cell_shade(vec4 color)
{
	//vec4 c;
	//const float f = 3.f;
	//c.r = round(color.r * f) / f;
	//c.g = round(color.g * f) / f;
	//c.b = round(color.b * f) / f;
	//c.a = color.a;
	
	return color;
}

void main(void)
{
	gl_FragColor = texture2D(colorMap, gl_TexCoord[0].st) * gl_Color;
	
	//gl_FragColor = cell_shade(gl_FragColor);
	//gl_FragColor = blink(gl_FragColor);
}


