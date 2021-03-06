cmake_minimum_required(VERSION 2.8)

#########################################################################
#####################        Project Helpers        #####################
# Use this cmake macros to easily create sub projects for the 			#
# IntelligenceProject solution.											#
#########################################################################

#----------------------- Public Macros to be used -----------------------

macro( solution_folder L_folder_name )
	set(CURRENT_SOLUTION_FOLDER ${L_folder_name} )
endmacro( solution_folder L_folder_name )

macro( subproject L_project_name )
	set(SUBPROJECT_NAME ${L_project_name} )
endmacro()

function( depends_on_projects L_folder_name )
	dmessage(STATUS "===========================" )
	dmessage(STATUS "Checking dependency projects for project: ${SUBPROJECT_NAME}" )
	foreach( L_project_name ${ARGN} )
		set( L_full_name ${L_folder_name}_${L_project_name} )
		dmessage(STATUS "Considering ${L_full_name}" )
		dmessage(STATUS "=> bCPPLIBRARY = ${${L_full_name}_bCPPLIBRARY}" )
		if( "${${L_full_name}_bCPPLIBRARY}" STREQUAL "TRUE")
			list(APPEND DEPENDENCY_PROJECT_NAMES ${L_project_name} )
			dmessage(STATUS "Added ${L_project_name}" )
		endif()
		list(APPEND DEPENDENCY_INCLUDE_DIRS ${${L_full_name}_INCLUDE_DIRS} )
	endforeach()
	dmessage(STATUS "Dependency code-libraries are: ${DEPENDENCY_PROJECT_NAMES}" )
	set( DEPENDENCY_PROJECT_NAMES ${DEPENDENCY_PROJECT_NAMES} PARENT_SCOPE )
	set( DEPENDENCY_INCLUDE_DIRS ${DEPENDENCY_INCLUDE_DIRS} PARENT_SCOPE )
endfunction( depends_on_projects L_folder_name L_project_names )

macro( depends_on_thirdparty L_project_name )
	set( L_full_name "ThirdParty_${L_project_name}" ) 
	set( L_importlib "${${L_full_name}_IMPORTLIB}" )
	set( L_include_dir "${${L_full_name}_INCLUDEDIR}" )
	list(APPEND THIRDPARTY_DEPENDENCY_PROJECTS "${L_project_name}" )
	list(APPEND THIRDPARTY_DEPENDENCY_BINARIES "${L_importlib}" )
	list(APPEND DEPENDENCY_INCLUDE_DIRS "${L_include_dir}" )
endmacro( depends_on_thirdparty L_project_name )

macro( depends_on_system L_system)
	if("${CMAKE_SYSTEM_NAME}" STREQUAL "${L_system}")
		foreach( L_library_name ${ARGN} )
			list(APPEND DEPENDENCY_PROJECT_NAMES ${L_library_name} )
		endforeach()
	endif()
endmacro( depends_on_system )

macro( auto_add_executable )
	dmessage(STATUS "  - Linking ${SUBPROJECT_NAME} with: ${DEPENDENCY_PROJECT_NAMES} ${THIRDPARTY_DEPENDENCY_BINARIES}" )
	
	add_executable( ${SUBPROJECT_NAME} ${CPP_FILES} ${PUBLIC_H_FILES} ${PRIVATE_H_FILES} ) 
	try_add_dependencies( ${SUBPROJECT_NAME} "${THIRDPARTY_DEPENDENCY_PROJECTS}" )
	target_link_libraries( ${SUBPROJECT_NAME} "${DEPENDENCY_PROJECT_NAMES};${THIRDPARTY_DEPENDENCY_BINARIES}")
	
	FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Generated")
	FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/Generated/LibImpExpMacros.generated.h" "\#define LIBIMPEXP")
	
	set_target_properties( ${SUBPROJECT_NAME} PROPERTIES FOLDER "${CURRENT_SOLUTION_FOLDER}" )
	set_target_compile_definitions(EXE)
endmacro( auto_add_executable )

macro( auto_add_shared_library )
	dmessage(STATUS "  - Linking ${SUBPROJECT_NAME} with: ${DEPENDENCY_PROJECT_NAMES} ${THIRDPARTY_DEPENDENCY_BINARIES}" )
	add_library(${SUBPROJECT_NAME} SHARED ${CPP_FILES} ${PUBLIC_H_FILES} ${PRIVATE_H_FILES} )
	try_add_dependencies( ${SUBPROJECT_NAME} "${THIRDPARTY_DEPENDENCY_PROJECTS}" )
	target_link_libraries( ${SUBPROJECT_NAME} "${DEPENDENCY_PROJECT_NAMES};${THIRDPARTY_DEPENDENCY_BINARIES}")
	
	FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Generated")
	GENERATE_EXPORT_HEADER(${SUBPROJECT_NAME} EXPORT_MACRO_NAME LIBIMPEXP EXPORT_FILE_NAME "Generated/LibImpExpMacros.generated.h")
	set_target_compile_definitions(SHARED)
	set_target_properties( ${SUBPROJECT_NAME} PROPERTIES FOLDER "${CURRENT_SOLUTION_FOLDER}" )
	set(${CURRENT_SOLUTION_FOLDER}_${SUBPROJECT_NAME}_bCPPLIBRARY TRUE CACHE INTERNAL "${PROJECT_FOLDER}/${SUBPROJECT_NAME}: Is a library with cpp code - thus must be linked against." FORCE )
endmacro( auto_add_shared_library)

macro( auto_add_headeronly_library )
	add_custom_target(${SUBPROJECT_NAME} SOURCES ${PUBLIC_H_FILES})
	set_target_properties( ${SUBPROJECT_NAME} PROPERTIES FOLDER "${CURRENT_SOLUTION_FOLDER}" )
endmacro( auto_add_headeronly_library)

macro( auto_add_interface_library )
	# add_library(${SUBPROJECT_NAME} INTERFACE ${CPP_FILES} ${PUBLIC_H_FILES} ${PRIVATE_H_FILES} )
	add_custom_target(${SUBPROJECT_NAME} SOURCES ${PUBLIC_H_FILES} ${PRIVATE_H_FILES} )
endmacro( auto_add_interface_library )

OPTION( BUILD_UNITTESTS "If enabled, then unittests are being build" ON )
OPTION( RUN_UNITTESTS "If enabled, then unittests are being run every build" ON )
OPTION( CHECK_MEMORY "If enabled, then the unittests are run a second time with drmemory" ON )
macro( auto_add_unittests )
	if( "${BUILD_UNITTESTS}" STREQUAL "ON")

		set(TESTNAME Test${SUBPROJECT_NAME} )
		dmessage(STATUS "[unittest] = Adding unittests =")
		dmessage(STATUS "  [unittest] following unittest files were registered: ")
		dmessage(STATUS "${UNITTEST_FILES}")

set(L_full_name "ThirdParty_unittest-cpp")
set(L_importlib "${${L_full_name}_IMPORTLIB}" )
set(L_include_dir "${${L_full_name}_INCLUDEDIR}" )
dmessage(STATUS "  [unittest] including directories: ${L_include_dir}")

		add_executable(${TESTNAME} ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Main.cpp ${UNITTEST_FILES})
		target_include_directories(${TESTNAME} PRIVATE ${L_include_dir} ${CMAKE_CURRENT_BINARY_DIR}/Generated)
		set_property(TARGET ${TESTNAME} PROPERTY FOLDER "Tests")
		
		target_link_libraries(${TESTNAME} ${SUBPROJECT_NAME} ${L_importlib})
		try_add_dependencies(${TESTNAME} ${L_full_name})
		
		if( "${RUN_UNITTESTS}" STREQUAL "ON" )
			add_custom_command(TARGET ${TESTNAME}
				POST_BUILD COMMAND ${TESTNAME}
				COMMENT "Running tests...")
		endif()
	endif()
endmacro( auto_add_unittests )

function( auto_include_directories )
	set(L_auto_include_dirs PUBLIC ${DEPENDENCY_INCLUDE_DIRS} ${PROJECT_Public_DIRS} PRIVATE ${PROJECT_Header_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/Generated ${THIRDPARTY_DIRECTORY}/include)
	dmessage(STATUS "auto-including following directories: ${L_auto_include_dirs}" )
	target_include_directories(${SUBPROJECT_NAME} ${L_auto_include_dirs} )
endfunction( auto_include_directories )

macro( auto_export_directories )
	dmessage(STATUS "auto-exporting following directories: ${PROJECT_Public_DIRS}" )
	list(APPEND L_export_dirs ${PROJECT_Public_DIRS} )
	set(${CURRENT_SOLUTION_FOLDER}_${SUBPROJECT_NAME}_INCLUDE_DIRS ${L_export_dirs} CACHE INTERNAL "${PROJECT_FOLDER}/${SUBPROJECT_NAME}: Include Directories" FORCE )
endmacro( auto_export_directories )

# in_sub()
#    sets variable CURRENT_SUB_NAME, if 'Environment/Reflection/Source/Atomic/' #    is meant, call with in_sub("Atomic")
macro( in_sub L_sub_name )
	end_sub()

	handle_sub_arg( "${ARGN}" )
	SET( SUB_CPP_FILES "")
	SET( SUB_PUBLIC_H_FILES "")
	SET( CURRENT_SUB_NAME ${L_sub_name} )
endmacro( in_sub )

# end_sub()
#    Applies setting of current sub, adds sub files to project files and creates
#    source group for sub
macro( end_sub )
	list( APPEND CPP_FILES ${SUB_CPP_FILES} )
	list( APPEND PUBLIC_H_FILES ${SUB_PUBLIC_H_FILES} )
	list( APPEND PRIVATE_H_FILES ${SUB_PRIVATE_H_FILES} )
	sub_source_group( Source "${SUB_CPP_FILES}" )
	sub_source_group( Public "${SUB_PUBLIC_H_FILES}" )
	sub_source_group( Header "${SUB_PRIVATE_H_FILES}" )
	SET(bSUB_Public_DIR_ADDED FALSE)
	SET(bSUB_Source_DIR_ADDED FALSE)
	SET(bSUB_Header_DIR_ADDED FALSE)
endmacro( end_sub )

# add_Source_and_Public()
#    Call with list of names. Every name is treated as a pair of .h & .cpp files, these are added into
#    the current 'Public' & 'Source' directories
macro( add_Source_and_Public L_file_names )
	dmessage(STATUS "ARGV is: ${ARGV0}" )
	add_Source(${ARGV})
	add_Public(${ARGV})
endmacro( add_Source_and_Public L_file_names )

# add_Source_and_Header()
#    Same as 'add_Source_and_Public()' but .h-files are added to 'Header' folder
macro( add_Source_and_Header L_file_names )
	add_Source(${ARGV})
	add_Header(${ARGV})
endmacro( add_Source_and_Header L_file_names )

#------------------------------ Local helper macros ----------------------------

option( NONCOMPATIBLE_MSVC_OPTIMIZATION "[TODO]" OFF )
function( set_target_compile_definitions L_targettype )
	if(${WIN32})
		set(L_OS Windows)
	else()
		set(L_OS Linux)
	endif()

	set(L_compile_definitions "def_BUILD_TARGETTYPE__${L_targettype};def_BUILD_PROJECTNAME=${SUBPROJECT_NAME};def_BUILD_OS__${L_OS};def_BUILD_NONCOMPATIBLE_MSVC_OPTIMIZATION__${NONCOMPATIBLE_MSVC_OPTIMIZATION}" )
	SET_TARGET_PROPERTIES( ${SUBPROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "${L_compile_definitions}")

endfunction( set_target_compile_definitions L_binary_type )

macro( handle_sub_arg L_arg )
	set(bSUB_DISABLED FALSE)
	if(NOT "${L_arg}" STREQUAL "")
		if(NOT "${L_arg}" STREQUAL "${CMAKE_SYSTEM_NAME}")
			set(bSUB_DISABLED TRUE)
		endif()
	endif()
endmacro( handle_sub_arg L_args )

macro( add_Source L_file_names )
	parse_argument_options(ADD_ROLE "TEST" ${ARGV})
	add_Role( Source cpp SUB_CPP_FILES ${ADD_ROLE_NOOPTION} ${ADD_ROLE_TEST} )
endmacro( add_Source L_file_names )

macro( add_Public L_file_names )
	parse_argument_options(ADD_ROLE "TEST" ${ARGV})
	add_Role( Public h SUB_PUBLIC_H_FILES ${ADD_ROLE_NOOPTION} ${ADD_ROLE_TEST})
	add_unittest( ${ADD_ROLE_TEST} )
endmacro( add_Public L_file_names )

macro( add_Header L_file_names )
	parse_argument_options(ADD_ROLE "TEST" ${ARGV})
	add_Role( Header h SUB_PRIVATE_H_FILES ${ADD_ROLE_NOOPTION} ${ADD_ROLE_TEST})
	add_unittest( ${ADD_ROLE_TEST} )
endmacro( add_Header L_file_names )


macro( add_Role L_role_dir L_role_fileending L_role_filelist )
	if( NOT "${bSUB_DISABLED}" STREQUAL "TRUE" )
		set_sub_dir("${L_role_dir}" "${CURRENT_SUB_NAME}" )
		foreach( L_file_name ${ARGN} )
			set( L_file "${CURRENT_SUB_DIR}${L_file_name}.${L_role_fileending}" )
			list(APPEND ${L_role_filelist}  "${L_file}")
			if( NOT EXISTS "${L_file}" )
				file(WRITE "${L_file}" "")
			endif()
		endforeach()
	endif()
endmacro( add_Role L_role_dir L_role_fileending L_role_filelist )

macro( add_unittest )
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Tests )
	foreach( L_filename ${ARGN} )
		if( "${CURRENT_SUB_NAME}" STREQUAL "" )
			set( L_testfile "${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test_${L_filename}.cpp" )
		else()
			set( L_testfile "${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test_${CURRENT_SUB_NAME}_${L_filename}.cpp" )
		endif()
		list(APPEND UNITTEST_FILES ${L_testfile} )
		if( NOT EXISTS "${L_testfile}" )
			file(WRITE "${L_testfile}" "")
		endif()
	endforeach()
endmacro()


#    Creates source group. The name contains the role (Source | Public | Header), 
#    and if available the sub name.
macro( sub_source_group L_role L_files )
	if( "${CURRENT_SUB_NAME}" STREQUAL "" )
		SET( L_name "${L_role}" )
	else()
		SET( L_name "${L_role}\\${CURRENT_SUB_NAME}")
	endif()

	if( NOT "${L_files}" STREQUAL "" )
		source_group("${L_name}" FILES ${L_files})
		dmessage(STATUS "Creating source group: ${L_name}, with files: ${L_files}")
	else()
		dmessage(STATUS "Source group: not doing anything (L_role=${L_role} | L_files=${L_files}")
	endif()
endmacro( sub_source_group L_role L_files )


macro( set_sub_dir L_role L_sub_name)
	if ( "${L_sub_name}" STREQUAL "")
		dmessage(STATUS "no sub found")
		SET( CURRENT_SUB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${L_role}/" )
	else()
		dmessage(STATUS "sub found: ${L_sub_name}")
		SET(CURRENT_SUB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${L_role}/${L_sub_name}/")
	endif()
	dmessage(STATUS "CURRENT_SUB_DIR is: ${CURRENT_SUB_DIR}" )
	
	if( NOT bSUB_${L_role}_DIR_ADDED )
		list( APPEND PROJECT_${L_role}_DIRS ${CURRENT_SUB_DIR} )
		SET( bSUB_${L_role}_DIR_ADDED TRUE )
	endif( NOT bSUB_${L_role}_DIR_ADDED )

	if( NOT EXISTS "${CURRENT_SUB_DIR}" )
		file( MAKE_DIRECTORY "${CURRENT_SUB_DIR}" )
	endif()
endmacro( set_sub_dir )

function( try_add_dependencies L_project L_dependencies )
	dmessage(STATUS "  - depends on '${L_dependencies}'")
	if (NOT "${L_dependencies}" STREQUAL "")
		add_dependencies( ${L_project} ${L_dependencies} )
	endif()
endfunction( try_add_dependencies L_project L_dependencies ) 
