cmake_minimum_required(VERSION 3.1)

project(Console)

add_PrivatePublic(ConsoleService)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()