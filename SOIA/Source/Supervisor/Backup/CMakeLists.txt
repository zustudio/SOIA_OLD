cmake_minimum_required(VERSION 3.1)

subproject(Backup)
	depends_on_projects(Environment Core Thread File)
	depends_on_projects(Supervisor ToolsCore)

add_PrivatePublic(BackupTool)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()