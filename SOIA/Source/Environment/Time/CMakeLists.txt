cmake_minimum_required(VERSION 3.1)

subproject(Time)
	depends_on_projects(Environment Core_E)

add_Source_and_Public(CurrentTime)
add_Public(
	Interpolator
	InterpolationFunction
	InstantInterpolation
	LinearInterpolation
	LimitedExponentialInterpolation
	SmoothInterpolation)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
