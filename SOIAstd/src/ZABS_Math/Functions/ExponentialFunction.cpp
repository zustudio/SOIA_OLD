
#include "ExponentialFunction.h"

#include <cmath>

using namespace ZABS::Math;

/*
 * Returns f(x) = a*k^x
*/
float ExponentialFunction::get_f(float x, const std::vector<float> &params)
{
	return params[0] * std::pow(params[1], x);
}

/*
 * Returns x_0 => f(x_0) = f
*/
float ExponentialFunction::get_reverse_x(float f, const std::vector<float> &params)
{
	/*
	 *	f = a * k^x
	 *	f/a = k^x
	 *	log_k(f/a) = x
	 *	x = log(f/a) / log(k)
	*/
	return std::log(f / params[0]) / std::log(params[1]);
}