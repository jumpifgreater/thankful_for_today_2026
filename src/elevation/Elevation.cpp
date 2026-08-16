#include "Elevation.h"

bool gritz::Elevation::isElevated()
{
    bool isElevated = false;
    HANDLE token = nullptr;
    TOKEN_ELEVATION elevation;
    DWORD dwSz;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
    {
        if (token)
        {
            CloseHandle(token);
            token = nullptr;
        }

        return isElevated;
    }

    if (!GetTokenInformation(token, TokenElevation, &elevation, sizeof elevation, &dwSz))
    {
        if (token)
        {
            CloseHandle(token);
            token = nullptr;
        }

        return isElevated;
    }

    isElevated = elevation.TokenIsElevated;

    return isElevated;
}

bool gritz::Elevation::elevate()
{
    HANDLE token = nullptr;
    // have no idea wtf this is
    LUID luid;
    TOKEN_PRIVILEGES tp{};

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token))
    {
        printf("a\n");
        return false;
    }

    LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid);
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    bool ok = AdjustTokenPrivileges(token, FALSE, &tp, 0, nullptr, nullptr) && GetLastError() == ERROR_SUCCESS;
    CloseHandle(token);

    if (!ok)
    {
        printf("b\n");
        return false;
    }

    std::pair<bool, HANDLE> processPair = gritz::utils::processes::findProcess("winlogon.exe");

    if (processPair.first == false)
    {
        return false;
    }

    HANDLE winlogon = processPair.second;
    HANDLE winlogonToken = nullptr;

    if (!OpenProcessToken(winlogon, TOKEN_QUERY | TOKEN_DUPLICATE, &winlogonToken))
    {
        CloseHandle(winlogon);
        return false;
    }

    HANDLE impersonationToken = nullptr;

    if (!DuplicateTokenEx(winlogonToken, TOKEN_QUERY | TOKEN_IMPERSONATE, nullptr, SecurityImpersonation, TokenImpersonation, &impersonationToken))
    {
        printf("e\n");
        CloseHandle(winlogonToken);
        CloseHandle(winlogon);
        return false;
    }

    // nullptr sets to current
    if (!SetThreadToken(nullptr, impersonationToken))
    {
        printf("f\n");
        CloseHandle(winlogon);
        CloseHandle(winlogonToken);
        CloseHandle(impersonationToken);
        return false;
    }

    CloseHandle(winlogon);
    CloseHandle(winlogonToken);
    CloseHandle(impersonationToken);

    return true;
}