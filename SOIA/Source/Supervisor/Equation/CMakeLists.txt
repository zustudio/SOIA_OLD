cmake_minimum_required(VERSION 3.1)

subproject(Equation)
	depends_on_projects(Environment Core_E MathematicsRuntime)
	depends_on_projects(Supervisor Core_S)

add_PrivatePublic(
	TCalculator
	CalculatorGUI)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
