
#pragma once

// include SOIA
#include "TokenArityInterface.h"

// include std
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <regex>

// class
namespace Environment
{
	class LIBIMPEXP TokenRule
	{
		////////////////////////////////////////////////////////////////
		// Functions
	public:

		//----- init -----
		TokenRule(int InIdentifier, std::regex const & InRegex, std::shared_ptr<TokenArityInterface> InTokenCollapser);
		TokenRule(std::regex const & InRegex, std::shared_ptr<TokenArityInterface> InTokenCollapser);
		virtual ~TokenRule();

		//----- access -----
		void Clear();
		bool ParseNextToken(ContainerAwareIteratorSet<std::string>& InTextIterators, std::list<Token*> & OutTokenList);
		int PeekNextToken(ContainerAwareIteratorSet<std::string> const & InTextIterators, std::string & OutTokenText) const;
		bool CollapseTokens();

		////////////////////////////////////////////////////////////////
		// Variables
	private:
		std::regex Regex;
		std::shared_ptr<TokenArityInterface> TokenCollapser;
		std::vector<Token*> ParsedTokens;
		int Identifier;
	};
}