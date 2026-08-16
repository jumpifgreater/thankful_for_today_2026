#pragma once

namespace gritz
{
	namespace paths
	{
		inline std::string paths[4];

		inline void initPaths()
		{
			paths[Launch] = std::filesystem::current_path().string();

			char* bfr = nullptr;

			if (_dupenv_s(&bfr, nullptr, "APPDATA") == 0)
			{
                if (bfr)
                {
                    paths[AppData] = bfr;
                }

				free(bfr);
			}

            if (_dupenv_s(&bfr, nullptr, "LOCALAPPDATA") == 0)
            {
                if (bfr)
                {
                    paths[LocalAppData] = bfr;
                }

                free(bfr);
            }

			paths[System32] = "C:\\Windows\\System32";
		}
	}

	namespace utils::processes
	{
        inline std::pair<bool, HANDLE> findProcess(const char* processName)
        {
            HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
            PROCESSENTRY32 pe{ sizeof pe };
            if (Process32First(ss, &pe))
            {
                do
                {
                    if (_stricmp(processName, pe.szExeFile) == 0)
                    {
                        CloseHandle(ss);
                        HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe.th32ProcessID);
                        if (!h)
                        {
                            printf("OpenProcess failed: %lu\n", GetLastError());
                            return { false, nullptr };
                        }
                        return { true, h };
                    }
                } while (Process32Next(ss, &pe));
            }
            CloseHandle(ss);
            return { false, nullptr };
        }
	}
}