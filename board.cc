#include <iostream>
#include "board.h"

namespace google {

void Board::Render(bool hitsOnly = false) {
  std::cout << std::endl;

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

bool Board::IsValidPlacement(Placement placement) {
  int x = placement.move.x;
  int y = placement.move.y;

  if (x > _board.size() || y > _board[0].size()) {
    return false;
  }

  if (placement.sideways) {
    for (int i = 0; i < placement.length; i++) {
      if (_board[x+i][y] != Tile::EMPTY) {
        return false;
      }
    }
  } else {
    for (int i = 0; i < placement.length; i++) {
      if (_board[x][y+i] != Tile::EMPTY) {
        return false;
      }
    }
  }

  return true;
}

bool Board::ApplyPlacement(Placement placement) {
  int x = placement.move.x;
  int y = placement.move.y;

  if (!IsValidPlacement(placement)) {
    return false;
  }

  if (placement.sideways) {
    for (int i = 0; i < placement.length; i++) {
      _board[x+i][y] = Tile::SHIP;
    }
  } else {
    for (int i = 0; i < placement.length; i++) {
      _board[x][y+i] = Tile::SHIP;
    }
  }

  return true;
}

bool Board::ApplyMove(Move move) {
  int i = move.x;
  int j = move.y;

  if (_board[i][j] == Tile::SHIP) {
    _board[i][j] = Tile::HIT;
  } else {
    _board[i][j] = Tile::MISS;
  }

  return true;
}

void Board::AutoPlace(GameModeConfig config) {
  // player.GetRemainingPieces
  std::cout << "Autoplacing\n";
}

bool Board::Empty() {
  for (int i = 0; i < _y; i++) {
    for (int j = 0; j < _x; j++) {
      if (_board[i][j] == Tile::SHIP) {
        return false;
      }
    }
  }

  return true;
}

void Board::Reset() {
  for (int i = 0; i < _y; i++) {
    for (int j = 0; j < _x; j++) {
      _board[i][j] = Tile::EMPTY;
    }
  }
}

}