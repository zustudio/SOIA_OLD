
#pragma once

#include <string>
#include <vector>

namespace Environment
{
	class DLLIMPEXP TypeID
	{
	public:
		explicit TypeID(const std::string& InString);
		template<typename T> static TypeID FromType()
		{
			return TypeID(typeid(T).name());
		}
		
		bool operator ==(const TypeID& InOther) const;
		operator std::string() const;

		//checks:
		bool IsPointer() const;

		//operations:
		TypeID Dereference() const;
		TypeID RemoveSuffix_Base() const;

		//helper function
	protected:
		static std::vector<std::string> MatchPattern(const std::string& InInput, const std::string& InPattern);

	private:
		std::string TypeString;
	};
}