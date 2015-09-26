cmake_minimum_required(VERSION 3.1)

subproject(Text)
	depends_on_projects(Environment Core_E CompileTime Time MathematicsCore)

add_Source_and_Public(
	CharMatch
	StringMatch)
in_sub(Dialogue)
	add_Public(
		DialogueInterface)
	add_Source_and_Public(
		StdDialogue
		FileDialogue)
in_sub(Log)
	add_Source_and_Public(
		Logger
		GlobalLogger)
in_sub(Token)
	add_Public(
		TokenArityInterface)
	add_Source_and_Public(
		Token
		TokenArity_Nullary
		TokenArity_Binary
		TokenArity_Parenthesis
		TokenRule
		Tokenizer)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
