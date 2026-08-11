#pragma once

namespace gritz
{
	namespace paths
	{
		inline std::string paths[3];

		inline void initPaths()
		{
			paths[Launch] = std::filesystem::current_path().string();

			char* bfr = nullptr;

			if (_dupenv_s(&bfr, nullptr, "APPDATA") != 0)
			{
				paths[AppData] = bfr;
				free(bfr);
			}

			paths[System32] = "C:\\Windows\\System32";
		}
	}

	namespace utils::processes
	{
		inline bool isProcessRunning(const char* processName)
		{
			HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

			PROCESSENTRY32 pe{ sizeof pe };

			if (Process32First(ss, &pe))
			{
				do
				{
					if (_stricmp(processName, pe.szExeFile) == 0)
					{
						return true;
					}
				} while (Process32Next(ss, &pe));
			}
		}
	}
}