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
              Board* board1, Board* board2) : _player1(player1), _player2(player2), 
              _board1(board1), _board2(board2) {}

  void WaitForInput() override {
    _active = false;
  }

  void Render() override {
    _board1->Render();
  }

  void Tick() override {}

 private:
  // TODO(cameron): Construct sizes from adaship_config.ini
  Player* _player1;
  Player* _player2;
  Board* _board1;
  Board* _board2;
};

} // namespace google

#endif // _INCLUDE_GAMEPLAY_H_