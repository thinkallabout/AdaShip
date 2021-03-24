#include "config.h"

namespace google {

GameModeConfig LoadConfigFromFile() {
  GameModeConfig _config;
  _config.boardWidth = 10;
  _config.boardHeight = 10;
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

}