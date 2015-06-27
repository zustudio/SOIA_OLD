cmake_minimum_required(VERSION 3.1)


function(PREFIXSUFFIX list_name prefix suffix)
    # create empty list - necessary?
    SET(${list_name}_TMP)

	dmessage(STATUS "PS Input: ${${list_name}}")
 
    # prefix and suffix elements
    foreach(l ${${list_name}})
      list(APPEND ${list_name}_TMP ${prefix}${l}${suffix} )
    endforeach()
	
	dmessage(STATUS "PS Output: ${${list_name}_TMP}" )
 
    # replace list by tmp list
    SET(${list_name} "${${list_name}_TMP}" PARENT_SCOPE)
    UNSET(${list_name}_TMP)
endfunction(PREFIXSUFFIX)


FUNCTION(EXPAND OUTPUT INPUT)
    STRING(REGEX MATCH "\\\${[^}]*}" m "${INPUT}")
    WHILE(m)
        STRING(REGEX REPLACE "\\\${(.*)}" "\\1" v "${m}")
        STRING(REPLACE "\${${v}}" "${${v}}" INPUT "${INPUT}")
        STRING(REGEX MATCH "\\\${[^}]*}" m "${INPUT}")
    ENDWHILE()
    SET("${OUTPUT}" "${INPUT}" PARENT_SCOPE)
ENDFUNCTION()

# scans argn for occurences of ${L_options} and adds args with the same option (or none at all)
# to a specific output list
function(parse_argument_options L_out_prefix L_options )
    dmessage(STATUS "[ Parsing arguments ]")
    dmessage(STATUS "  ${ARGN}")
    
    set(L_found_option NOOPTION)
    foreach( L_arg ${ARGN} )
        set(b_do_append TRUE)
        
        foreach( L_option ${L_options} )
            if( "${L_arg}" STREQUAL "${L_option}" )
                set(L_found_option ${L_option} )
                set(b_do_append FALSE)
            endif()
        endforeach()
        
        dmessage(STATUS "Argument:     ${L_arg}")
        dmessage(STATUS "   do_append: ${b_do_append}")
        dmessage(STATUS "   option:    ${L_found_option}")
        
        if("${b_do_append}" STREQUAL "TRUE")
            list(APPEND L_list_${L_found_option} ${L_arg} )
            set(L_found_option NOOPTION)
        endif()
    endforeach()
    
    # set parent scope vars to results
    list(APPEND L_options NOOPTION) # include no options into saving
    foreach( L_option ${L_options} )
        set(${L_out_prefix}_${L_option} "${L_list_${L_option}}" PARENT_SCOPE )
        dmessage(STATUS "Saving: ${L_out_prefix}_${L_option} = ${L_list_${L_option}}")
    endforeach()
endfunction()
