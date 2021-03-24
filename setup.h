// Provides the Setup.

#include <cstdlib>
#include <memory>

using namespace std;

#ifndef _INCLUDE_SETUP_H_
#define _INCLUDE_SETUP_H_

#include "board.h"
#include "player.h"

namespace google {

class SetupMode : public GameMode {
 public:
  SetupMode(Player* player1, Player* player2,
            Board* board1, Board* board2) : _player1(player1), _player2(player2), 
            _board1(board1), _board2(board2) {}

  void WaitForInput() override {
    std::cout << "Autoplace? (y/n)\n";
    std::string buffer;
    std::cin >> buffer;

    bool valid = true;
    if (_player1->ShouldAutoPlace()
    || (_player1->IsHuman() && buffer == "y")) {
      _board1->AutoPlace(_player1);
    } else {
      do {
        Placement move = _player1->GetNextPlacement();
        valid = _board1->ApplyPlacement(move);
        if (!valid && _player1->ShouldRenderBoard()) {
          std::cout << "Invalid placement:" << std::endl;
        }
      } while (!valid);
    }

    if (_player2->ShouldAutoPlace()
    || (_player2->IsHuman() && buffer == "y"))  {
      _board2->AutoPlace(_player2);
    } else {
      do {
        Placement move = _player2->GetNextPlacement();
        valid = _board2->ApplyPlacement(move);
        if (!valid && _player2->ShouldRenderBoard()) {
          std::cout << "Invalid placement:" << std::endl;
        }
      } while (!valid);
    }

    std::cout << "Reset? (y/n)\n";
    std::cin >> buffer;
    if (buffer == "y") {
      _board1->Reset();
      _board2->Reset();
    } else {
      _active = _player1->AllPiecesDown() && _player2->AllPiecesDown();
    }
  }

  void Render() override {
    if (_player1->ShouldRenderBoard())
      _board1->Render();

    if (_player2->ShouldRenderBoard())
      _board2->Render();
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

#endif // _INCLUDE_SETUP_H_