#pragma once
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <memory>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <chrono>
#include <sstream>
#include <conio.h>
#include <fstream>

#define NO_MIN_MAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <dpapi.h>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <miniz/miniz.h>

typedef uint8_t byte;

namespace filesystem = std::filesystem;

namespace gritz
{
	enum Paths
	{
		Launch,
		AppData,
		LocalAppData,
		System32
	};
}