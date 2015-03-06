
#include "ReversedExponentialFunction.h"
#include <cmath>

using namespace ZABS::Math;


/*
 *  f(x) = Y_0 - Y_0 * k^(X_0 - x)
 */
float ReversedExponentialFunction::get_f(float x, const std::vector<float> &params)
{
	return params[0] - params[0] * std::pow(params[2], params[1] - x);
}

float ReversedExponentialFunction::get_reverse_x(float f, const std::vector<float> &params)
{
	/* Calculation of reversed:
	 *  f(x) = Y - Y *k^(X -x)
	 *  Y - f(x) = Y * k^(X - x)
	 *  1 - f(x) / Y = k^(X - x)
	 *  log(1 - f(x)/Y) / log(k) = X -x
	 *  x = X - log(1 - f(x)/Y) / log(k)
	*/
	return params[1] - std::log(1 - f / params[0]) / std::log(params[2]);
}