#pragma once

#include <string>

namespace IA
{
	template<class Super>
	class MText : public Super
	{
	public:
		template<typename... Args>
		MText(const std::string &NewText, Args&&... args) : Super(args...)
		{
			Text = new std::string(NewText);
		}
		virtual ~MText(){}
		std::string* Text;
	};
}
