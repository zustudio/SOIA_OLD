cmake_minimum_required(VERSION 3.1)

project(AnalysisCore)
	depends_on_projects(Environment Core Reflection)
	depends_on_projects(Supervisor DataCore)

add_PrivatePublic(
	Port
	InPort
	OutPort
	AAnalyzer)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()