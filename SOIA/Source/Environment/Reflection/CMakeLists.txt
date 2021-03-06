cmake_minimum_required(VERSION 3.1)

subproject(Reflection)
	depends_on_projects(Environment Core_E Text CompileTime MathematicsCore)

in_sub(Element)
	add_Public(
		RWrapper
		RWrapperInterface
		RClassTemplate
		ReflectionMacros)
	add_Source_and_Public(
		ElementID
		RClassProvider
		RAbstractClass
		RClass
		RElementBase
		TEST RElement
		RContainer
		RPointer)
in_sub(Atom)
	add_Public(
		Atom
		AtomConverter
		SimpleConverter
		PointerConverter
		VectorConverter)
	add_Source_and_Public(
		AtomConverterHelper
		AtomConverterProvider)
in_sub(Function)
	add_Source_and_Public(
		RFunctionTemplate
		RFunction
		Function)
in_sub(Type)
	add_Public(
		DestructorFunctionTemplate
		TypeName
		MemberMirrorTemplate
		ObjectMirrorTemplate)
	add_Source_and_Public(
		TypeID
		PointerCounter
		TEST VoidPointer
		MemberMirror
		ObjectMirror)
in_sub(Unresolved)
	add_Public(
		ResolveInfoInterface)
	add_Source_and_Public(
		ResolvePointerInfo
		ResolveVectorInfo
		VoidPointerToUnresolvedRObject)
in_sub(Global)
	add_Source_and_Public(
		GlobalContainer
		GlobalReflectionProviders)
end_sub()


auto_add_shared_library()
auto_add_unittests()
auto_include_directories()
auto_export_directories()
