
#include "LinearFunction.h"

using namespace ZABS::Math;

float LinearFunction::get_f(float x, const std::vector<float> &params)
{
	return params[0] * x + params[1];
}

float LinearFunction::get_reverse_x(float f, const std::vector<float> &params)
{
	/* Calculation of reversed:
	 *	f(x) = m*x + b;
	 *	y = m*x + b;
	 *	y - b = m*x;
	 *	(y - b) / m = x;
	*/
	return (f - params[1]) / params[0];
}