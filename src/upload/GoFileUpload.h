#pragma once

namespace gritz::upload
{
	class GoFileUpload final
	{
	public:
		static std::string upload(std::vector<uint8_t> data);
		static std::string getServer();
	};
}