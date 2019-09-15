#pragma once
#include <string>
#include <stdint.h>
#include "Network.h"
#include "Base64.h"
#include <iostream>

#include <msgpack.hpp>

using namespace std;
namespace Blockchain
{

	struct TypedData
	{
		uint32_t wood;
		uint32_t ore;
		uint32_t wool;

		uint32_t lastPos_x;
		uint32_t lastPos_y;
	};

	string Typed2Base64(const TypedData td)
	{
		return base64_encode(reinterpret_cast<const unsigned char*>(&td), sizeof(TypedData));
	}

	TypedData Base642Typed(string base64)
	{
		TypedData* td;
		string decoded = base64_decode(base64);
		td = const_cast<TypedData*>(reinterpret_cast<const TypedData*>(decoded.c_str()));
		return *td;
	}

	// Hardcoded for now.
	const string SELF_TOKEN = "CYGMDLIRK5JRAM7AQARPR2CSKFLOQ5BDLSHJKVZNEC23PV7VMOXQ====";
	const string SELF_ADDRESS = "CYGMDLIRK5JRAM7AQARPR2CSKFLOQ5BDLSHJKVZNEC23PV7VMOXZXIQP5I";
	const string FRIEND_TOKEN = "EX2ZAQFUQXFVH3YW5PT74QNJDUJIKMLFSW7QGZIICBZ6IDNTCNDA====";
	const string FRIEND_ADDRESS = "EX2ZAQFUQXFVH3YW5PT74QNJDUJIKMLFSW7QGZIICBZ6IDNTCNDPPMGO54";


	// A single, local host and const wallet for now.
	const string algo_api_host = "http://127.0.0.1:8080/";
	const string algo_api_token = "19c8a10c2cfab0be1888542355f64107d50ed828d467c66a6389b1de9e3a676b";
	const vector<string> algo_api_header = { "X-Algo-API-Token: " + algo_api_token };

	const string kmd_api_host = "http://127.0.0.1:7833/";
	const string kmd_api_token = "376741c79304b08b3fc1b616d37802d7ccf31f77bcf79f0100fc36f2efec0151";
	const vector<string> kmd_api_header = { "X-KMD-API-Token: " + kmd_api_token };

	// An ephemeral handle
	string GetWalletHandle()
	{
		json body;
		body["wallet_id"] = "108df35ef2b021125f799998fd991502";
		body["wallet_password"] = "12345";
		json result = Network::PostRequest(kmd_api_host + "v1/wallet/init", kmd_api_header, body);

		return result["wallet_handle_token"];
	}

	// Generate and return new account key
	string NewUserKey()
	{
		json body;
		body["wallet_handle_token"] = GetWalletHandle();
		json result = Network::PostRequest(kmd_api_host + "v1/key", kmd_api_header, body);
		return result["address"];
	}

	json WriteTransaction(TypedData data)
	{

		json transactionParams = Network::GetRequest(algo_api_host + "v1/transactions/params", algo_api_header);
		std::cout << transactionParams << std::endl;

		std::string mybase64 = Typed2Base64(data);

		json transaction;
		transaction["amt"] = 0;
		transaction["fee"] = 1000;
		transaction["fv"] = transactionParams["lastRound"] - 100;
		transaction["gen"] = transactionParams["genesisID"];
		//string tHash = transactionParams["genesishashb64"];
		transaction["gh:b32"] = "JBR3KGFEWPEE5SAQ6IWU6EEBZMHXD4CZU6WCBXWGF57XBZIJHIRA====";
		transaction["lv"] = transactionParams["lastRound"] + 100;
		transaction["note:b64"] = mybase64;
		transaction["rcv:b32"] = FRIEND_TOKEN;
		transaction["snd:b32"] = SELF_TOKEN;
		transaction["type"] = "pay";

		std::string myData1 = transaction.dump();
		std::string myData2;
		for (size_t i = 0; i < myData1.length(); ++i) {
			if (myData1[i] == '"') {
				myData2 += "\\\"";
			}
			else {
				myData2 += myData1[i];
			}
		}

		std::string syscall("bash -c \"echo '" + myData2 + "' | msgpacktool -e -b32 > temp2.txt 2>&1\"");
		system(syscall.c_str());

		std::ifstream file("temp2.txt");
		std::stringstream strStream;
		strStream << file.rdbuf();
		std::string sysResult = strStream.str();

		std::string result = base64_encode(reinterpret_cast<const unsigned char*>(sysResult.c_str()), sysResult.size());

		json myData;
		myData["transaction"] = result;
		myData["wallet_handle_token"] = GetWalletHandle();
		myData["wallet_password"] = "12345";

		// Sign transaction
		json signedData = Network::PostRequest(kmd_api_host + "v1/transaction/sign", kmd_api_header, myData);
		std::cout << signedData << std::endl;

		std::string thing1 = signedData["signed_transaction"];
		std::string syscall2("bash -c \"echo '" + thing1 + "' | base64 -d > bodyData 2>&1\"");
		system(syscall2.c_str());

		std::string sysResult2;
		// Post to the network
		json postedData = Network::PostRequestBinary(algo_api_host + "v1/transactions", algo_api_header, sysResult2);
		std::cout << postedData << std::endl;

		//std::string txid = postedData["txId"];
		//json recentOne2 = Network::GetRequest(algo_api_host + "v1/transactions/pending/" + "QJAR5SK6DVC5DHSDEPQIGA3AZPIJZBJJ4RGNL7IIKMCQETX6IQBA", algo_api_header);
		//std::cout << recentOne2 << std::endl;

		//json recentOne = Network::GetRequest(algo_api_host + "v1/account/" + FRIEND_ADDRESS + "/transaction/" + "QJAR5SK6DVC5DHSDEPQIGA3AZPIJZBJJ4RGNL7IIKMCQETX6IQBA", algo_api_header);
		//std::cout << recentOne << std::endl;



		return postedData;
	}

	// Done at load: then we simulate over it.
	TypedData ReadTransactions() {
		json transactionParams = Network::GetRequest(algo_api_host + "v1/transactions/params", algo_api_header);
		std::cout << transactionParams << std::endl;

		std::string lastRound = std::to_string((int)transactionParams["lastRound"] + 1);
		std::string firstRound = std::to_string((int)((transactionParams["lastRound"] - 5)));
		// Gets a list of transactions since last tick
		std::vector<std::string> header = { "X-Algo-API-Token: " + algo_api_token };
		TypedData tdSum{ 0, 0,0, 0, 0 };
		try {

			json transactions = Network::GetRequest(algo_api_host + "v1/account/" + FRIEND_ADDRESS + "/transactions?firstRound=" + firstRound + "&lastRound=" + lastRound, header);
			json myList = transactions["transactions"];
			int woodSum = 0;
			int oreSum = 0;
			int woolSum = 0;
			for (const auto& transaction : myList) {

				string note = transaction["noteb64"];
				TypedData td = Base642Typed(note);
				tdSum.wood += td.wood;
				tdSum.ore += td.ore;
				tdSum.wool += td.wool;
			}
		}
		catch (...) {
			
		}
		try {
			json transactions = Network::GetRequest(algo_api_host + "v1/transactions/pending", algo_api_header);

			json myList = transactions["truncatedTxns"]["transactions"];
			for (const auto& transaction : myList) {
				string note = transaction["noteb64"];
				TypedData td = Base642Typed(note);
				tdSum.wood += td.wood;
				tdSum.ore += td.ore;
				tdSum.wool += td.wool;
			}

		}
		catch (...) {
		
		}



		return tdSum;
	}

	json GetVersion() {
		std::vector<std::string> header = { "X-Algo-API-Token: " + algo_api_token };
		return Network::GetRequest(algo_api_host + "versions", header);
	}

	json GetTransactionInfo() {
		std::vector<std::string> header = { "X-Algo-API-Token: " + algo_api_token };
		return Network::GetRequest(algo_api_host + "versions", header);
	}
}