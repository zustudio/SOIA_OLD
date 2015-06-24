cmake_minimum_required(VERSION 3.1)

subproject(MathematicsRuntime)
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
	OP_CalculateFunction
	EquationString
	EquationToken
	EquationTokens
	FunctionCache
	FunctionCacheItem
	MathContainer
	D1D1GenericFunction)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()
auto_static_check()