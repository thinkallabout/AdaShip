#include <iostream>
#include "game_mode.h"
#include "main_menu.h"
#include "setup.h"
#include "player.h"
#include "board.h"

using namespace google;

int main() {
  // TODO(cameron): Add Board and Player objects. Get those from MainMenu which
  //                constructs them.

  MainMenu main_menu;
  main_menu.Execute();

  HumanPlayer* player1 = new HumanPlayer();
  BadNpcPlayer* player2 = new BadNpcPlayer();
  Board* board1 = new Board();
  Board* board2 = new Board();

  SetupMode setup(player1, player2, board1, board2);
  setup.Execute();

  return 0;
}