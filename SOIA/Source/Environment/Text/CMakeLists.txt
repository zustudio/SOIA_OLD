cmake_minimum_required(VERSION 3.1)

subproject(Text)
	depends_on_projects(Environment Core_E CompileTime MathematicsCore)

add_PrivatePublic(
	CharMatch
	StringMatch
	StdDialogue
	FileDialogue)
add_Public(
	DialogueInterface)
in_sub(Token)
	add_Public(
		TokenArityInterface)
	add_PrivatePublic(
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
