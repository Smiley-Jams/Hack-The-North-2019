#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace Network 
{
	std::string GetRequest(const std::string& url, const std::vector<std::string>& headers)
	{
		std::string syscall("curl \"");
		syscall += url;
		syscall += "\"";
		for (const auto& header : headers)
		{
			syscall += " -H \"";
			syscall += header;
			syscall += "\"";
		}
		syscall += " -o temp.txt";
		system(syscall.c_str());

		// Then get this info from a file
		std::ifstream file("temp.txt");
		std::stringstream strStream;
		strStream << file.rdbuf();
		return strStream.str();
	}
}