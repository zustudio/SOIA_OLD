cmake_minimum_required(VERSION 3.1)

subproject(CompileTime)

in_sub(Generic)
	add_Public(
		IndexPack
		ConstExprDynamicList)
in_sub(Number)
	add_Public(
		Vector4Int
		Vector8Int
		IntExpressions
		MultipleOperandMathematics)
in_sub(String)
	add_Public(
		CharReplacer
		ConstExprChar
		CharArrayLiteral
		TypeCharArrayLiteral)
in_sub(Traits)
	add_Public(
		TypeTraits
		OperatorTraits)
end_sub()

auto_add_headeronly_library()
auto_export_directories()
