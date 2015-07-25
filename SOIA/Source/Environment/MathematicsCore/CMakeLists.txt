cmake_minimum_required(VERSION 3.1)

subproject(MathematicsCore)
	depends_on_projects(Environment Core_E)


in_sub(Functions)
	add_PrivatePublic(
		ExponentialFunction
		LinearFunction
		ReversedExponentialFunction)
	add_Public(
		D1D1FunctionInterface)
in_sub(Random)
	add_PrivatePublic(
		Random)
in_sub(DataStructures)
	add_Public(
		Matrix2D
		Range
		Vector2D
		VectorND)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
