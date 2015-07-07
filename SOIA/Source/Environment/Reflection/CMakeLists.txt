cmake_minimum_required(VERSION 3.1)

subproject(Reflection)
	depends_on_projects(Environment Core Log CompileTime MathematicsCore)

in_sub(Element)
	add_PrivatePublic(
		Element_ID
		ElementReflection
		ElementReflectionProvider
		RAbstractClass
		RClass
		RContainer
		TEST RElement
		RPointer)
	add_Public(
		RClassTemplate
		ReflectionMacros)
in_sub(Atom)
	add_PrivatePublic(
		Atom
		AtomReflection
		AtomReflectionProvider
		ReflectionFactory)
	add_Public(
		SimpleAtomReflection
		PointerReflectionTemplate
		VectorAtomReflectionTemplate)
in_sub(Function)
	add_PrivatePublic(
		RFunctionTemplate
		RFunction
		Function)
in_sub(Type)
	add_PrivatePublic(
		TypeID
		PointerCounter
		TEST VoidPointer
		ObjectMirror)
	add_Public(
		DestructorFunctionTemplate
		TypeName
		ObjectMirrorTemplate)
in_sub(Unresolved)
	add_Public(
		ResolveInfoInterface)
	add_PrivatePublic(
		ResolvePointerInfo
		ResolveVectorInfo
		VoidPointerToUnresolvedRObject)
in_sub(Global)
	add_PrivatePublic(
		ContainerProvider
		ReflectionProviders)
end_sub()


auto_add_shared_library()
auto_add_unittests()
auto_static_check()
auto_include_directories()
auto_export_directories()


#------------------------- ADD CPP UNIT TEST ----------------------------------

#dmessage(STATUS "/////////////// EXTRA ///////////////")
#dmessage(STATUS "// Adding new executable")
#set(THIRD_PARTY_DIRECTORY "${CMAKE_SOURCE_DIR}/../ThirdParty/")
#set(LIB_INCLUDE_DIRECTORY "${THIRD_PARTY_DIRECTORY}UnitTestPP/include/")
#set(LIB_IMPORT_DIR "${THIRD_PARTY_DIRECTORY}UnitTestPP/lib/libUnitTest++.a")
#dmessage(STATUS "Lib is in: ${LIB_IMPORT_DIR}")
#include_directories(${LIB_INCLUDE_DIRECTORY})


#add_library(UnitTest++ STATIC IMPORTED)
#set_target_properties(UnitTest++ PROPERTIES IMPORTED_LOCATION "${LIB_IMPORT_DIR}")

#add_executable(TestReflection ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Main.cpp)

#target_link_libraries(TestReflection UnitTest++)

#add_custom_command(TARGET TestReflection
#	POST_BUILD COMMAND TestReflection
#	COMMENT "Running tests...")

