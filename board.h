// Provides the Board class, which can Render() in ASCII form,
// and is the basic data structure for the game.

#include <cstdlib>
#include <vector>

#ifndef _INCLUDE_BOARD_H_
#define _INCLUDE_BOARD_H_

namespace google {

class Board {
 public:
  Board() {
    _x = 10;
    _y = 10;
    SetupBoard();
  }

  Board(int x, int y) : _x(x), _y(y) {
    SetupBoard();
  }

  void Render(bool hitsOnly = false) {
    RenderLine();

    for (int i = 0; i < _y; i++) {
      for (int j = 0; j < _x; j++) {
        switch (_board[i][j]) {
          // TODO(cameron): Use enum statement here instead.
          case 1:
            if (hitsOnly)
              std::cout << "~";
            else
              std::cout << "D";
            break;

          case 2:  // Hit.
            std::cout << "X";
            break;
          case 3:  // Miss.
            std::cout << "x";
            break;
            
          case 0:
          default:
            std::cout << "~";
        }
      }

      std::cout << std::endl;
    }

    RenderLine();
  }

 private:
  int _x;
  int _y;

  std::vector<std::vector<int>> _board;

  void SetupBoard() {
    _board.reserve(_x);

    for (int i = 0; i < _x; i++) {
      _board[i].reserve(_y);
    }
  }

  void RenderLine() {
    for (int i = 0; i < _x; i++) {
      std::cout << "-";
    }
    std::cout << "\n";
  }
};

} // namespace google

#endif // _INCLUDE_BOARD_H_