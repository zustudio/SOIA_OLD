cmake_minimum_required(VERSION 3.1)

project(MathematicsRuntime)
	depends_on_projects(Environment Reflection)

add_PrivatePublic(
	Value
	Constant
	Variable
	Operation
	OP_Add
	OP_Substract
	OP_Multiply
	OP_Divide
	OP_GreaterThan
	OP_if
	OP_Select
	EquationString
	EquationToken
	EquationTokens
	FunctionCache
	FunctionCacheItem
	GenericMathFunction
	MathContainer)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()