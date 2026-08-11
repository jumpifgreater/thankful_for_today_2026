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
}