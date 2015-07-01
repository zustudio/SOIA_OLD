
#pragma once

namespace Environment
{
	class LIBIMPEXP PointerCounter
	{
	public:
		explicit PointerCounter();
		PointerCounter(const PointerCounter&) = delete;
		PointerCounter(PointerCounter&&) = delete;

		void Increase();
		bool Decrease();

	private:
		int ClonedPointerCount = 0;
	};
}