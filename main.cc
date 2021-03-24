#include <iostream>
#include "game_mode.h"
#include "main_menu.h"
#include "gameplay.h"
#include "setup.h"
#include "player.h"
#include "board.h"

using namespace google;

int main() {

  MainMenu main_menu;
  main_menu.Execute();

  // TODO(cameron): Construct these based on data from the MainMenu.
  HumanPlayer* player1 = new HumanPlayer();
  BadNpcPlayer* player2 = new BadNpcPlayer();
  Board* board1 = new Board();
  Board* board2 = new Board();

  SetupMode setup(player1, player2, board1, board2);
  setup.Execute();

  // Both boards will be ready at this point.
  GameplayMode game(player1, player2, board1, board2);
  game.Execute();

  return 0;
}