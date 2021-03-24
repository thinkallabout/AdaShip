// Provides the MainMenu.

#include <cstdlib>

#ifndef _INCLUDE_CONFIG_H_
#define _INCLUDE_CONFIG_H_

namespace google {

enum PlayerType {
  HUMAN,
  NPC,
};

enum GameModeType {
  DEFAULT,
  SALVO,
  HIDDEN_MINES,
};

struct ShipDefinition {
  std::string name;
  int length;
};

struct GameModeConfig {
  PlayerType player1;
  PlayerType player2;
  GameModeType gameMode;
  int boardHeight;
  int boardWidth;
  std::vector<ShipDefinition> ships;
};

} // namespace google

#endif // _INCLUDE_CONFIG_H_