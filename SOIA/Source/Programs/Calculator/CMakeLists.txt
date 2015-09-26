cmake_minimum_required(VERSION 3.1)

subproject(Calculator)
	depends_on_projects(Environment Core_E MathematicsRuntime Graphics)

add_Private(Main)
add_PrivatePublic(CalculatorWindow)
end_sub()

auto_add_executable()
auto_include_directories()
auto_export_directories()