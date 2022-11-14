#include "../pch.h"
#include "StringCommon.h"

std::string Trim(const std::string& str)
{
	auto result = str;
	result.erase(str.find_last_not_of(' ') + 1); // suffixing spaces
	result.erase(0, str.find_first_not_of(' ')); // prefixing spaces

	return result;
}

std::string GetCurrentDateTimeString()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d%m%Y%H%M%S", timeinfo);
	std::string str(buffer);

	return str;
}