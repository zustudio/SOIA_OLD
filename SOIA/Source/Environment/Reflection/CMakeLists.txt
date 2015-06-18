cmake_minimum_required(VERSION 3.1)

project(Reflection)
	depends_on_projects(Environment Core Log CompileTime MathematicsCore)

in_sub(Element)
	add_PrivatePublic(
		Element_ID
		ElementReflection
		ElementReflectionProvider
		RAbstractClass
		RClass
		RContainer
		RElement
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
	add_PrivateClasses(
		RPointerReflection
		VectorAtomReflection)
	add_Public(
		SimpleAtomReflection
		PointerReflectionTemplate
		VectorAtomReflectionTemplate)
in_sub(Function)
	add_PrivatePublic(
		FunctionInterface)
	add_Public(
		Function)
in_sub(Type)
	add_PrivatePublic(
		TypeID
		VoidPointer
		ObjectMirror)
	add_Public(
		TypeName
		ObjectMirrorTemplate)
in_sub(Global)
	add_PrivatePublic(
		ReflectionProviders)
end_sub()


auto_include_directories()
auto_export_directories()
auto_add_shared_library()

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


