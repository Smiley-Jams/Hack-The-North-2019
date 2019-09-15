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
		// dump data to file:
		//std::ofstream myfile;
		//myfile.open("bodyData");
		//myfile << data.dump();
		//myfile.close();

		std::string myData = data.dump();
		std::string myData2;
		for (size_t i = 0; i < myData.length(); ++i) {
			if (myData[i] == '"') {
				myData2 += "\\\"";
			}
			else {
				myData2 += myData[i];
			}
		}

		std::string syscall("curl -X POST \"");
		syscall += url;
		syscall += "\" -H \"Content-Type: application/json\" ";
		for (const auto& header : headers)
		{
			syscall += " -H \"";
			syscall += header;
			syscall += "\"";
		}
		if (data.size() > 0) {
			//syscall += "-d bodyData";
			syscall += " -d \"";
			syscall += myData2;
			//syscall += "{\"wallet_id\": \"108df35ef2b021125f799998fd991502\",\"wallet_password\" : \"12345\"}";
			syscall += "\" -o temp.txt";
		}
		else {
			syscall += "-o temp.txt";
		}
		system(syscall.c_str());

		// Then get this info from a file
		std::ifstream file("temp.txt");
		std::stringstream strStream;
		strStream << file.rdbuf();
		if (strStream.str().length() == 0)
			return json();
		return json::parse(strStream.str());
	}

	json PostRequestBinary(const std::string& url, const std::vector<std::string>& headers, const std::string data)
	{
		// dump data to file:
		//std::ofstream myfile;
		//myfile.open("bodyData");
		//myfile << data.c_str();
		//myfile.close();



		std::string syscall("curl -X POST \"");
		syscall += url;
		//syscall += "\" -H \"Content-Type: application/x-binary\" ";
		for (const auto& header : headers)
		{
			syscall += "\" -H \"";
			syscall += header;
			syscall += "\"";
		}
		syscall += " --data-binary \"@bodyData\"";
		syscall += " -o temp.txt";
		system(syscall.c_str());

		// Then get this info from a file
		std::ifstream file("temp.txt");
		std::stringstream strStream;
		strStream << file.rdbuf();
		if (strStream.str().length() == 0)
			return json();
		return json::parse(strStream.str());
	}
}