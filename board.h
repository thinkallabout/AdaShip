// Provides the Board class, which can Render() in ASCII form,
// and is the basic data structure for the game.

#include <cstdlib>
#include <vector>

#ifndef _INCLUDE_BOARD_H_
#define _INCLUDE_BOARD_H_

namespace google {

enum Tile {
  EMPTY = 0,
  SHIP = 1,
  HIT = 2,
  MISS = 3,
};

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
          // The double size char is used due to the narrow character space
          // on the terminal.
          case Tile::SHIP:
            if (hitsOnly)
              std::cout << "~~";
            else
              std::cout << "DD";
            break;

          case Tile::HIT:  // Hit.
            std::cout << "XX";
            break;
          case Tile::MISS:  // Miss.
            std::cout << "xx";
            break;
            
          case Tile::EMPTY:
          default:
            std::cout << "~~";
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
      std::cout << "--";
    }
    std::cout << "\n";
  }
};

} // namespace google

#endif // _INCLUDE_BOARD_H_