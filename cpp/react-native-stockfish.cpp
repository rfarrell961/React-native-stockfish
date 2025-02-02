#include <iostream>
#include <unordered_map>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "react-native-stockfish.h"

#include "./Stockfish/bitboard.h"
#include "./Stockfish/evaluate.h"
#include "./Stockfish/misc.h"
#include "./Stockfish/position.h"
#include "./Stockfish/tune.h"
#include "./Stockfish/types.h"
#include "./Stockfish/uci.h"
#include "./Stockfish/bitboard.h"
#include "./Stockfish/misc.h"
#include "./Stockfish/position.h"
#include "./Stockfish/types.h"
#include "./Stockfish/uci.h"
#include "./Stockfish/tune.h"
#include "../ios/cpp_bridge.h"

namespace stockfish {
	int argc = 1;
	char *argv[] = {""};
	std::string EngineBridge::response;

	EngineBridge::EngineBridge() : engine(nullptr)
	{
		Stockfish::UCIEngine::sendResponse = &EngineBridge::engine_response_received;
	}

	void EngineBridge::engine_response_received(std::string data)
	{
		response = response + data;
		triggerReactEventFromCpp(data.c_str());
	}

	void EngineBridge::init()
	{
		engine_response_received(Stockfish::engine_info());

		Stockfish::Bitboards::init();
		Stockfish::Position::init();
		
		engine = new Stockfish::UCIEngine(argc, argv);

		Stockfish::Tune::init(engine->engine_options());
	}

	void EngineBridge::stockfish_write(std::string data)
	{	
		engine->write(data);
	}

	const char* EngineBridge::stockfish_read()
	{
    	char* cstr = new char[response.size() + 1];
    	std::strcpy(cstr, response.c_str());

		response.clear();

		return cstr;
	}
}


