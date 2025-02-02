#include <stdio.h>
#include <string>
#include "./Stockfish/uci.h"

#ifndef STOCKFISH_H
#define STOCKFISH_H

namespace stockfish {
  class EngineBridge
  {
    public:
      EngineBridge();
      void init();
      void stockfish_write(std::string data);
      const char* stockfish_read();
      static void engine_response_received(std::string data);
    
    private:
      static std::string response;
      Stockfish::UCIEngine * engine;
  };
}

#endif /* STOCKFISH_H */
