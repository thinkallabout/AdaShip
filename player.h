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
};

class Player {
  // TODO(cameron): Get next move or placement setup.
 public:
  Player() {}
  Player(Player&&) = default;
  virtual Placement GetNextPlacement() = 0;
  virtual Move GetNextMove() = 0;
  virtual bool ShouldRenderBoard() { return false; }
};

// An implemention of Player which is completely random.
//
// A smarter version would store hits that occur on the game board in order
// to make better moves.
class BadNpcPlayer : public Player {
  Placement GetNextPlacement() {
    // Return random placements forever based on remaining pieces.
    return Placement{
      .move = RandomMove(),
      .length = 4
    };
  }

  Move GetNextMove() {
    // Return random placements forever.
    return RandomMove();
  }

  virtual bool ShouldRenderBoard() { return true; }

 private:
  Move RandomMove() {
    return Move{};
  }
};

class HumanPlayer : public Player {
  Placement GetNextPlacement() {
    std::cout << "Next piece: ";
    std::string buffer;
    std::cin >> buffer;
    Placement placement = Placement{
      .move = MoveFromInputBuffer(buffer),
      .length = 4,
      // TODO(cameron): Get the length of the piece.
    };
    return placement;
  }

  Move GetNextMove() {
    std::cout << "Next move: ";
    std::string buffer;
    std::cin >> buffer;
    return MoveFromInputBuffer(buffer);
  }

  Move MoveFromInputBuffer(std::string buffer) {
    // A2 -> 0, 0
    return Move{
      .x = 10,
      .y = 10,
    };
  }
};

} // namespace google

#endif // _INCLUDE_PLAYER_H_