#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "json.hpp"

#include <msgpack.hpp>

using json = nlohmann::json;

namespace Network 
{
	json GetRequest(const std::string& url, const std::vector<std::string>& headers)
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
		return json::parse(strStream.str());
	}

	// NOTE: Don't need to include content-type for post request, already handled
	json PostRequest(const std::string& url, const std::vector<std::string>& headers, const json& data)
	{
		std::string syscall("curl -X POST \"");
		syscall += url;
		syscall += "\" -H \"Content-Type: application/json\" ";
		for (const auto& header : headers)
		{
			syscall += " -H \"";
			syscall += header;
			syscall += "\"";
		}
		syscall += " -d '";
		syscall += data.dump();
		syscall += "' -o temp.txt";
		system(syscall.c_str());

		// Then get this info from a file
		std::ifstream file("temp.txt");
		std::stringstream strStream;
		strStream << file.rdbuf();
		return json::parse(strStream.str());
	}
}