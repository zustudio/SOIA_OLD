cmake_minimum_required(VERSION 3.1)

project(Reflection)
	depends_on_projects(Environment Core CompileTime MathematicsCore)

in_sub(Element)
	add_PrivatePublic(
		Element_ID
		ElementReflection
		ElementReflectionProvider
		RAbstractClass
		RClass
		RContainer
		RElement
		RFunction
		RPointer)
	add_Public(
		RClassTemplate
		RFunctionInterface)
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
in_sub(Type)
	add_PrivatePublic(
		TypeID
		VoidPointer)
in_sub(Global)
	add_PrivatePublic(
		ReflectionProviders)
end_sub()


auto_include_directories()
auto_export_directories()
auto_add_shared_library()


