
#pragma once

// include SOIA
#include "TokenCollapserInterface.h"

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
		TokenRule(std::regex const & InRegex, std::shared_ptr<TokenCollapserInterface> InTokenCollapser);
		virtual ~TokenRule();

		//----- access -----
		void Clear();
		bool ParseNextToken(ContainerAwareIteratorSet<std::string>& InTextIterators, std::list<Token*> & OutTokenList);
		bool PeekNextToken(ContainerAwareIteratorSet<std::string> const & InTextIterators, std::string & OutTokenText) const;
		bool CollapseTokens();

		////////////////////////////////////////////////////////////////
		// Variables
	private:
		std::regex Regex;
		std::shared_ptr<TokenCollapserInterface> TokenCollapser;
		std::vector<Token*> ParsedTokens;
	};
}