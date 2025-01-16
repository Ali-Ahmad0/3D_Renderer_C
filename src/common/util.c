#include "util.h"
#include <math.h>

// I have no idea how this works
uint32_t hsv_to_rgb(float h, float s, float v)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	float rf;
	float gf;
	float bf;

	// Ensure valid hsv
	h = fmod(h, 360.0f);
	if (h < 0)
		h += 360.0f;
	s = s > 1.0f ? 1.0f : (s < 0.0f ? 0.0f : s);
	v = v > 1.0f ? 1.0f : (v < 0.0f ? 0.0f : v);

	float c = v * s;
	float x = c * (1 - fabsf(fmod(h / 60.0f, 2) - 1));
	float m = v - c;

	if (h >= 0 && h < 60)
	{
		rf = c; gf = x; bf = 0;
	}
	else if (h >= 60 && h < 120)
	{
		rf = x; gf = c; bf = 0;
	}
	else if (h >= 120 && h < 180)
	{
		rf = 0; gf = c; bf = x;
	}
	else if (h >= 180 && h < 240)
	{
		rf = 0; gf = x; bf = c;
	}
	else if (h >= 240 && h < 300)
	{
		rf = x; gf = 0; bf = c;
	}
	else
	{
		rf = c; gf = 0; bf = x;
	}

	// Convert to 8-bit color values
	r = (uint8_t)((rf + m) * 255);
	g = (uint8_t)((gf + m) * 255);
	b = (uint8_t)((bf + m) * 255);

	return (r << 16) | (g << 8) | b;
}