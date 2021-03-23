// Provides the Setup.

#include <cstdlib>

#ifndef _INCLUDE_SETUP_H_
#define _INCLUDE_SETUP_H_

#include "board.h"
#include "player.h"

namespace google {

class SetupMode : public GameMode {
 public:
  void WaitForInput() override {
    _active = false;
  }

  void Render() override {
    _firstBoard.Render();
  }

  void Tick() override {}

  Board GetFirstBoard() { return _firstBoard; }
  Board GetSecondBoard() { return _secondBoard; }
 private:
  // TODO(cameron): Construct sizes from adaship_config.ini
  Board _firstBoard;
  Board _secondBoard;
};

} // namespace google

#endif // _INCLUDE_SETUP_H_