// Provides the MainMenu.

#include <cstdlib>

#ifndef _INCLUDE_MAIN_MENU_H_
#define _INCLUDE_MAIN_MENU_H_

#include "config.h"

namespace google {

class MainMenu : public GameMode {
 public:
  void WaitForInput() override {
    std::cout << "Choose a game mode or quit:"               << std::endl
              << "\t1. Player vs. computer"                  << std::endl
              << "\t2. Player vs. player"                    << std::endl
              << "\t3. Player vs. computer (salvo)"          << std::endl
              << "\t4. Player vs. player (salvo)"            << std::endl
              << "\t5. Player vs. computer (hidden mines)"   << std::endl
              << "\t6. Player vs. player (hidden mines)"     << std::endl
              << "\t7. Computer vs. computer (hidden mines)" << std::endl
              << "\t8. Quit"                                 << std::endl;
    int buffer;
    std::cin >> buffer;

    if (buffer < 0 || buffer > 8) {
      std::cout << "Unknown command." << std::endl;
      return;
    }

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

    switch (buffer) {
      case 1:
        _config.player1 = PlayerType::HUMAN;
        _config.player2 = PlayerType::NPC;
        _config.gameMode = GameModeType::DEFAULT;
        _active = false;
        break;
      case 2:
        _config.player1 = PlayerType::HUMAN;
        _config.player2 = PlayerType::HUMAN;
        _config.gameMode = GameModeType::DEFAULT;
        _active = false;
        break;
      case 3:
        _config.player1 = PlayerType::HUMAN;
        _config.player2 = PlayerType::NPC;
        _config.gameMode = GameModeType::SALVO;
        _active = false;
        break;
      case 4:
        _config.player1 = PlayerType::HUMAN;
        _config.player2 = PlayerType::HUMAN;
        _config.gameMode = GameModeType::SALVO;
        _active = false;
        break;
      case 5:
        _config.player1 = PlayerType::HUMAN;
        _config.player2 = PlayerType::NPC;
        _config.gameMode = GameModeType::HIDDEN_MINES;
        _active = false;
        break;
      case 6:
        _config.player1 = PlayerType::HUMAN;
        _config.player2 = PlayerType::HUMAN;
        _config.gameMode = GameModeType::HIDDEN_MINES;
        _active = false;
        break;
      case 7:
        _config.player1 = PlayerType::NPC;
        _config.player2 = PlayerType::NPC;
        _config.gameMode = GameModeType::HIDDEN_MINES;
        _active = false;
        break;
      // TODO(cameron): Implement other game modes here.
      case 8:
        QuitGame();
    }
  }

  void Render() override {}
  void Tick() override {}

  GameModeConfig GetConfig() { return _config; }

 private:
  void QuitGame() {
    std::cout << "Bye bye!" << std::endl;
    exit(0);
  }
  
  GameModeConfig _config;
};

} // namespace google

#endif // _INCLUDE_MAIN_MENU_H_