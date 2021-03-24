// Provides the Setup.

#include <cstdlib>
#include <memory>

using namespace std;

#ifndef _INCLUDE_GAMEPLAY_H_
#define _INCLUDE_GAMEPLAY_H_

#include "board.h"
#include "player.h"

namespace google {

class GameplayMode : public GameMode {
 public:
  GameplayMode(Player* player1, Player* player2,
              Board* board1, Board* board2, GameModeConfig config)
              : _player1(player1), _player2(player2), 
              _board1(board1), _board2(board2), _config(config) {}

  void WaitForInput() override {
    if (_board2->Empty()) {
      std::cout << "Player 1 has won!" << std::endl;
      _active = false;
    }
    else if (_board1->Empty()) {
      std::cout << "Player 2 has won!" << std::endl;
      _active = false;
    }

    int turns = 1;
    if (_config.gameMode == GameModeType::SALVO) {
      turns = 3;
    }

    bool valid = true;
    for (int i = 0; i < turns; i++) {
      do {
        Move move = _player1->GetNextMove();
        valid = _board1->ApplyMove(move);
        if (!valid && _player1->ShouldRenderBoard()) {
          std::cout << "Invalid move" << std::endl;
        }
      } while (!valid);
    }
    
    for (int i = 0; i < turns; i++) {
      do {
        Move move = _player2->GetNextMove();
        valid = _board2->ApplyMove(move);
        if (!valid && _player2->ShouldRenderBoard()) {
          std::cout << "Invalid move" << std::endl;
        }
      } while (!valid);
    }
  }

  void Render() override {
    std::cout << std::endl << std::endl
              << "================================================"
              << std::endl << std::endl << std::endl;

    // TODO(cameron): Render boards of human players.
    if (_player1->IsHuman())
    {
      _board1->Render();
      _board2->Render(/*hitsOnly=*/true);
    }

    if (_player2->IsHuman())
      _board1->Render(/*hitsOnly=*/true);
      _board2->Render();
  }

  void Tick() override {}

 private:
  // TODO(cameron): Construct sizes from adaship_config.ini
  Player* _player1;
  Player* _player2;
  Board* _board1;
  Board* _board2;
  GameModeConfig _config;
};

} // namespace google

#endif // _INCLUDE_GAMEPLAY_H_