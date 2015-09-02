/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

namespace Environment
{
	//////////////////////////////////////////////////////////////////////////////////////////
	/// \class		Atom
	/// \brief		Base class for every custom Atom, lets objects be serialized and treated as atomic.
	/// \detailed	Child classes define their serialization via following functions the must provide:
	///				 - static Child StaticToObject(const std::string&)
	///				 - static std::string StaticToString(const Child&)
	class Atom
	{
	};
}
