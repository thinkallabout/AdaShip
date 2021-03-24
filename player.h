// Provides the Player class, which can be implemented by a human or
// an NPC version.

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
  virtual Placement GetNextPlacement() = 0;
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
  Placement GetNextPlacement() {
    // Return random placements forever based on remaining pieces.
    _piecesDown = true;
    return Placement{
      .move = RandomMove(),
      .length = 4
    };
  }

  Move GetNextMove() {
    // Return random placements forever.
    return RandomMove();
  }
  virtual bool ShouldAutoPlace() { return true; }

 private:
  Move RandomMove() {
    return Move{
      .x = 0,
      .y = 0,
    };
  }
};

class HumanPlayer : public Player {
  Placement GetNextPlacement() { return Placement{}; }

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
    return Move{
      .x = 9,
      .y = 9,
    };
  }
};

} // namespace google

#endif // _INCLUDE_PLAYER_H_