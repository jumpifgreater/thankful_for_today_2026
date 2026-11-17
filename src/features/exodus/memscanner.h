#pragma once



#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <windows.h>


inline bool isReadable(MEMORY_BASIC_INFORMATION& mbi) {
	if (mbi.State != MEM_COMMIT) {
		return false;
	}

	if (mbi.Type != MEM_PRIVATE &&
		mbi.Type != MEM_MAPPED &&
		mbi.Type != MEM_IMAGE) {
		return false;
	}

	DWORD p = mbi.Protect & 0xff;

	return p == PAGE_READONLY ||
		p == PAGE_READWRITE ||
		p == PAGE_EXECUTE_READ ||
		p == PAGE_EXECUTE_READWRITE;
}


inline bool isMatch(const std::string& text) {
	if (text.ends_with("%22%7D")) {
		return true;
	}

	return false;
}

inline std::string extractValue(const std::string& text) {
	const std::string start = "%3A%22";
	const std::string end = "%22%7D";

	size_t s = text.find(start);
	if (s == std::string::npos)
		return "";

	s += start.length();

	size_t e = text.find(end, s);
	if (e == std::string::npos)
		return "";

	return text.substr(s, e - s);
}


inline void scan(char* bfr, int sz, std::vector<std::string>& results) {
	std::string text(bfr, sz);

	std::string curr;


	for (char c : text) {

		if (c >= 32 && c <= 126) {
			curr += c;
		}
		else {

			if (isMatch(curr)) {
				results.push_back(extractValue(curr));

			}

			curr.clear();
		}
	}


	if (isMatch(curr)) {
		results.push_back(curr);

		std::cout << curr << "\n";
	}
}


inline void scanProcess(std::vector<std::string>& results) {

	MEMORY_BASIC_INFORMATION mbi{};

	std::pair<BOOL, HANDLE> process = gritz::utils::processes::findProcess("Exodus.exe");

	HANDLE exodus{};

	if (process.first)
	{
		exodus = process.second;
	}

	if (exodus != INVALID_HANDLE_VALUE)
	{
		std::cout << "nope";
	}

	uintptr_t addr = 0;

	while (VirtualQueryEx(exodus,(void*)addr,&mbi,sizeof(mbi))) {
		if (isReadable(mbi)) {
			std::vector<char> bfr(mbi.RegionSize);

			SIZE_T read = 0;

			if (ReadProcessMemory(exodus, mbi.BaseAddress, bfr.data(),mbi.RegionSize,&read)) {


				scan(bfr.data(), (int)read, results);
			}
		}


		addr += mbi.RegionSize;
	}

	for (auto res : results)
	{
		std::cout << res << std::endl;
	}


	CloseHandle(exodus);
}