
#pragma once

namespace Environment
{
	template<typename ReturnType, typename... ArgumentTypes>
	class Function
	{
	public:
		virtual ReturnType Execute(ArgumentTypes...) = 0;
	};
}