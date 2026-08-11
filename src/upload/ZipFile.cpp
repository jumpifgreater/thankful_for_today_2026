#include "ZipFile.h"

std::vector<uint8_t> gritz::upload::zip::ZipFile::create(std::string tokenString)
{
	mz_zip_archive archive{};

	if (!mz_zip_writer_init_heap(&archive, 0, 0))
	{
		return {};
	}

	addEntry(archive, "yo wsp G", "example/message.txt");

	std::vector<uint8_t> result;

	void* heapData = nullptr;
	size_t heapSz = 0;

	if (mz_zip_writer_finalize_heap_archive(&archive, &heapData, &heapSz))
	{
		uint8_t* bytes = static_cast<uint8_t*>(heapData);

		result.assign(bytes, bytes + heapSz);
	}

	mz_zip_writer_end(&archive);

	return result;
}

void gritz::upload::zip::ZipFile::addEntry(mz_zip_archive& archive, std::vector<uint8_t> data, std::string entryName)
{
	mz_zip_writer_add_mem(&archive, entryName.c_str(), data.data(), data.size(), MZ_DEFAULT_COMPRESSION);
}

void gritz::upload::zip::ZipFile::addEntry(mz_zip_archive& archive, std::string data, std::string entryName)
{
    mz_zip_writer_add_mem(&archive, entryName.c_str(), data.data(), data.size(), MZ_DEFAULT_COMPRESSION);
}