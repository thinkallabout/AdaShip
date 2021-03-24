// Provides the Player class, which can be implemented by a human or
// an NPC version.

#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <stack>
#include "board.h"
#include "config.h"

#ifndef _INCLUDE_PLAYER_H_
#define _INCLUDE_PLAYER_H_

namespace google {

struct Move {
  int x;
  int y;
};

struct Placement {
  Move move;
  int length;
  bool sideways;
};

class Player {
  // TODO(cameron): Get next move or placement setup.
 public:
  Player() {}
  Player(Player&&) = default;
  virtual Placement GetNextPlacement(Board* board) = 0;
  virtual Move GetNextMove() = 0;
  virtual bool ShouldRenderBoard() { return false; }
  bool AllPiecesDown() { return _piecesDown; }
  virtual bool ShouldAutoPlace() { return false; }
  bool IsHuman() { return false; }
 protected:
  bool _piecesDown;
};

// An implemention of Player which is completely random.
//
// A smarter version would store hits that occur on the game board in order
// to make better moves.
class BadNpcPlayer : public Player {
 public:
  BadNpcPlayer(GameModeConfig config) : _config(config) {
    for (int i = 0; i < config.ships.size(); i++) {
      _remainingShips.push(config.ships[i]);
    }
  }

  Placement GetNextPlacement(Board* board) {
    Placement placement;
    bool valid = false;
    while (!valid) {
      ShipDefinition next = _remainingShips.top();

      placement = Placement{
        .move = RandomMove(),
        .length = next.length,
        .sideways = true,
      };
      valid = board->IsValidPlacement(placement);

      if (valid) {
        std::cout << "[ NPC ] Auto-placed: " << _remainingShips.top().name;
        _remainingShips.pop();
      }
    }

    _piecesDown = _remainingShips.size() == 0;
    return placement;
  }

  Move GetNextMove() {
    // Return random placements forever.
    return RandomMove();
  }
  virtual bool ShouldAutoPlace() { return true; }

 private:
  std::stack<ShipDefinition> _remainingShips;
  GameModeConfig _config;
  Move RandomMove() {
    return Move{
      .x = rand() % _config.boardWidth,
      .y = rand() % _config.boardHeight,
    };
  }
};

class HumanPlayer : public Player {
 public:
  HumanPlayer(GameModeConfig config) : _config(config) {
    for (int i = 0; i < config.ships.size(); i++) {
      _remainingShips.push(config.ships[i]);
    }
  }

  Placement GetNextPlacement(Board* board) {
    // TODO(cameron): Pick random ship.
    Placement placement;
    bool valid = false;
    while (!valid) {
      ShipDefinition next = _remainingShips.top();
      std::string buffer;
      std::cout << "Next placement (e.g. A2) - " << next.name << ": ";
      std::cin >> buffer;
      
      placement = Placement{
        .move = MoveFromInputBuffer(buffer),
        .length = next.length,
        .sideways = true,
      };
      valid = board->IsValidPlacement(placement);

      if (valid) {
        _remainingShips.pop();
      }
    }

    _piecesDown = _remainingShips.size() == 0;
    return placement;
  }

  Move GetNextMove() {
    std::cout << "Next move: ";
    std::string buffer;
    std::cin >> buffer;
    return MoveFromInputBuffer(buffer);
  }

  bool IsHuman() { return true; }
  virtual bool ShouldRenderBoard() { return true; }

  Move MoveFromInputBuffer(std::string buffer) {
    // A2 -> 0, 0
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);
    return Move{
      .x = indexForColumnReference(buffer.substr(0,1)),
      .y = indexForColumnReference(buffer.substr(1,1)),
    };
  }

 private:
  std::stack<ShipDefinition> _remainingShips;
  GameModeConfig _config;

  // Sourced from Mike's Google Classroom post.
  //
  // Removed comments and tidied up to keep it clean.
  int indexForColumnReference(std::string buffer) {
    if(buffer.length() == 1) {
      return toupper(int(buffer[0])) - 65;
    } else if(buffer.length() == 2) {
      return ((toupper(int(buffer[1])) - 65) + (toupper(int(buffer[0])) - 64) * 26);
    }
    return -1;
  }
};

} // namespace google

#endif // _INCLUDE_PLAYER_H_