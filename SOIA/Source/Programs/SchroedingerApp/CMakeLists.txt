cmake_minimum_required(VERSION 3.1)

subproject(SchroedingerApp)
	depends_on_projects(Environment Reflection File MathematicsRuntime Graphics Log)

add_PrivatePublic(Main)
end_sub()

auto_include_directories()
auto_add_executable()
