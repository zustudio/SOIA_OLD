
set(FILE_DIR ${CMAKE_CURRENT_LIST_DIR})

macro( uacrequest_subdirectory_link L_link_name L_target_dir)
	set(L_link_dir "${BINARY_DIRECTORY}/${L_link_name}")
	if(NOT EXISTS "${L_link_dir}")
		if(WIN32)
			to_windows_path( "${L_link_dir}" L_native_link_dir)
			to_windows_path( "${L_target_dir}" L_native_target_dir)
			list(APPEND UAC_REQUESTS "mklink /D ${L_native_link_dir} ${L_native_target_dir}")
		endif()
	endif()
	
endmacro( uacrequest_subdirectory_link L_name L_target_dir)

macro( execute_uacrequests )
	if(NOT "${UAC_REQUESTS}" STREQUAL "")
		if(WIN32)
		
			set(L_uac_sh ${CMAKE_BINARY_DIR}/uac_requests.sh)
			set(L_uac_bat ${CMAKE_BINARY_DIR}/uac_requests.bat)
			file(TO_NATIVE_PATH "${L_uac_bat}" L_uac_bat_native)
			
			# prepare content
			file(READ ${FILE_DIR}/Templates/uac.bat.template L_uac_content)
			foreach( L_uac_request ${UAC_REQUESTS})
				set(L_uac_content "${L_uac_content}
${L_uac_request}")
			endforeach()
			
			# write to files
			file(WRITE ${L_uac_bat} "${L_uac_content}")
			file(WRITE ${L_uac_sh} "\#!/bin/bash/
cmd //c '${L_uac_bat_native}'")
	
			# execute
			execute_process(COMMAND bash ${L_uac_sh})
			
		endif()
	endif()
endmacro( execute_uacrequests )

function( to_windows_path L_linux_path O_windows_path_var)
	message(STATUS "linux path: ${L_linux_path}")
	 
	string(REPLACE "/" "\\" L_path "${L_linux_path}")
	
	set(${O_windows_path_var} "${L_path}" PARENT_SCOPE)
endfunction( to_windows_path L_linux_path )

macro( to_staticlib_name L_name O_full_name)
	to_lib_name(${L_name} "lib" "a" ${O_full_name})
endmacro( to_staticlib_name L_name O_full_name)

macro( to_implib_name L_name 0_full_name)
	to_lib_name(${L_name} "lib" "so" ${0_full_name})
endmacro( to_implib_name L_name 0_full_name)

macro( to_sharedlib_name L_name O_full_name)
	to_lib_name(${L_name} "dll" "so" ${O_full_name})
endmacro( to_staticlib_name L_name O_full_name)

function( to_lib_name L_name L_win_end L_lin_end O_full_name)
	if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
		set(${O_full_name} "${L_name}.${L_win_end}" PARENT_SCOPE)
	elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
		set(${O_full_name} "lib${L_name}.${L_lin_end}" PARENT_SCOPE)
	endif()
endfunction( to_staticlib_name L_name L_win_end L_lin_end O_full_name)

