#pragma once
#include <utils/Utils.h>
#include <webhook/Webhook.h>
#include <upload/GoFileUpload.h>
#include <upload/ZipFile.h>

namespace gritz
{
	class cGritz final
	{
	private:

	public:
		void Start(char** args);
	};
}