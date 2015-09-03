cmake_minimum_required(VERSION 3.1)

subproject(MathematicsRuntime)
	depends_on_projects(Environment Text Reflection)

add_PrivatePublic(
	DynamicMathFunction
	Value
	Constant
	Variable
	MR_Function
	Operation
	OP_Add
	OP_Substract
	OP_Multiply
	OP_Divide
	OP_GreaterThan
	OP_Select
	OP_CalculateFunction
	FunctionCache
	FunctionCacheItem
	DefinitionSet
	TEST MathContainer)
end_sub()

auto_add_shared_library()
auto_add_unittests()
auto_include_directories()
auto_export_directories()
auto_static_check()