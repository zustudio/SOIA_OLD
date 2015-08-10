
#pragma once

#include "MemberMirror.h"

#include "ObjectMirrorTemplate.h"

namespace Environment
{
	template<typename OwnerTypeArg, typename MemberTypeArg>
	class MemberMirrorTemplate : public MemberMirror
	{
	public:
		constexpr MemberMirrorTemplate(MemberTypeArg OwnerTypeArg::* InMemberToMirror, const std::string& InName)
			: MemberMirror(InName),
			MemberToMirror(InMemberToMirror)
		{}
		
		virtual TypeID MemberType() override
		{
			return TypeID::FromType<MemberTypeArg>();
		}

		virtual ObjectMirror* ToObjectMirror(VoidPointer const & InOwner)
		{
			ObjectMirror* newObjectMirror = nullptr;
			OwnerTypeArg* p_owner = InOwner.CastTo<OwnerTypeArg>();

			if (p_owner)
			{
				newObjectMirror = new ObjectMirrorTemplate<MemberTypeArg>(p_owner->*MemberToMirror, Name);
			}

			return newObjectMirror;
		}

		MemberTypeArg OwnerTypeArg::* MemberToMirror;
	};
}
