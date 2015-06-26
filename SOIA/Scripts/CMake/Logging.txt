cmake_minimum_required(VERSION 3.1)

option( DEBUG_MESSAGES "Enables detailed debug messages on cmake configure" OFF )

function( dmessage L_severity L_message )
	if( DEBUG_MESSAGES )
		message(${L_severity} ${L_message} )
	endif()
endfunction( dmessage L_message )

