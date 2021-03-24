#include "config.h"
#include <fstream>
#include <regex>
#include <string>

namespace google {

GameModeConfig LoadConfigFromFile() {
  GameModeConfig _config;
  _config.boardWidth = 10;
  _config.boardHeight = 10;

  std::string buffer;
  std::ifstream configFile("adaship_config.ini");
  while (getline (configFile, buffer)) {
      if (buffer.rfind("Board: ", 0) == 0) {
      // Adapted from: https://stackoverflow.com/questions/33520934/regex-with-only-numbers-in-a-string-c
      std::regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
      std::smatch m;
      std::string str = buffer;

      int i = 0;
      while (regex_search(str, m, rx)) {
          if (i == 0) _config.boardWidth = std::atoi(std::string(m[1]).c_str());
          if (i == 1) _config.boardHeight = std::atoi(std::string(m[1]).c_str());
          str = m.suffix().str();
          i++;
      }
    }
  }

  configFile.close();

  _config.ships.push_back(ShipDefinition{
    .length = 5,
    .name = "Carrier",
  });
  _config.ships.push_back(ShipDefinition{
    .length = 4,
    .name = "Battleship",
  });
  _config.ships.push_back(ShipDefinition{
    .length = 3,
    .name = "Destroyer",
  });
  _config.ships.push_back(ShipDefinition{
    .length = 3,
    .name = "Submarine",
  });
  _config.ships.push_back(ShipDefinition{
    .length = 2,
    .name = "Patrol Boat",
  });
  return _config;
}

} // namespace google