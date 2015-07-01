
#pragma once

struct LastLeaf
{
	struct Get
	{
		static const bool Result = false;
	};
};

template<typename ContentType, ContentType InContent, typename NextLeaf>
struct ConstExprLeaf
{
	template<int index>
	struct Get : NextLeaf::template Get<index - 1>
	{};

	template<>
	struct Get<0>
	{
		static const ContentType Result = InContent;
	};

	//static const ContentType Content = InContent;
};