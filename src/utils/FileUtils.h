#pragma once

namespace gritz::utils::files
{
	inline void copyFile(std::filesystem::path from, std::filesystem::path to)
	{
		if (std::filesystem::exists(from) != 0)
		{
			return;
		}

		std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing);
	}

	inline void read(filesystem::path path, byte* bfr, int sz)
	{
		std::ifstream file(path, std::ios::binary);
		file.read(reinterpret_cast<char*>(bfr), sz);
	}

	inline std::vector<byte*> readList(std::vector<std::pair<filesystem::path, size_t>> pairs)
	{
		std::vector<byte*> bytes;

		for (auto pair : pairs)
		{
			std::ifstream file(pair.first, std::ios::binary);
			std::vector<byte*> bfr(pair.second);
			file.read(reinterpret_cast<char*>(bfr.data()), pair.second);

			bytes.insert(bytes.end(), bfr.begin(), bfr.end());
		}

		return bytes;
	}
}