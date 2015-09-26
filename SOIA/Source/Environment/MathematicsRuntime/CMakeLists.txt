cmake_minimum_required(VERSION 3.1)

subproject(MathematicsRuntime)
	depends_on_projects(Environment Text Reflection)

add_Source_and_Public(
	DynamicMathFunction
	Value
	Constant
	Variable
	MR_Function
	MR_AppliedFunction
	Operation
	OP_Add
	OP_Substract
	OP_Multiply
	OP_Divide
	OP_GreaterThan
	OP_Select
	FunctionCache
	FunctionCacheItem
	DefinitionSet
	TEST MathContainer)
end_sub()

auto_add_shared_library()
auto_add_unittests()
auto_include_directories()
auto_export_directories()