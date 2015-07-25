cmake_minimum_required(VERSION 3.1)

subproject(SOIA)
	depends_on_projects(Environment File Log Reflection MathematicsCore CompileTime Graphics)
	depends_on_projects(Supervisor ToolsCore ElementExplorer Backup Console Equation OS)

add_Private(Main)
end_sub()

auto_add_executable()
auto_include_directories()