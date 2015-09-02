
#pragma once

namespace Environment
{
	template <typename T, typename _ = void>
	struct is_vector
	{
		static const bool value = false;
	};

	template<class T>
	struct is_vector<std::vector<T> >
	{
		static bool const value = true;
	};
}