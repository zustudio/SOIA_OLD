cmake_minimum_required(VERSION 3.1)

subproject(MathematicsCore)
	depends_on_projects(Environment Core_E)


in_sub(Functions)
	add_Source_and_Public(
		ExponentialFunction
		LinearFunction
		ReversedExponentialFunction)
	add_Public(
		D1D1FunctionInterface)
in_sub(Random)
	add_Source_and_Public(
		Random)
in_sub(DataStructures)
	add_Public(
		Matrix2D
		TEST Range
		Vector2D
		VectorND)
end_sub()

auto_add_shared_library()
auto_add_unittests()
auto_include_directories()
auto_export_directories()
