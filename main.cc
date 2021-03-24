#include <iostream>
#include "game_mode.h"
#include "main_menu.h"
#include "gameplay.h"
#include "setup.h"
#include "player.h"
#include "board.h"
#include "config.h"

using namespace google;

int main() {
  MainMenu main_menu;
  GameModeConfig config = main_menu.GetConfig();
  main_menu.Execute();

  Player* player1;
  Player* player2;

  HumanPlayer* humanPlayer1 = new HumanPlayer();
  BadNpcPlayer* npcPlayer1 = new BadNpcPlayer();
  HumanPlayer* humanPlayer2 = new HumanPlayer();
  BadNpcPlayer* npcPlayer2 = new BadNpcPlayer();

  if (config.player1 == PlayerType::HUMAN) {
    player1 = humanPlayer1;
  } else {
    player1 = npcPlayer1;
  }

  if (config.player2 == PlayerType::HUMAN) {
    player2 = humanPlayer2;
  } else {
    player2 = npcPlayer2;
  }

  int boardWidth = config.boardWidth;
  int boardHeight = config.boardHeight;
  Board* board1 = new Board(boardWidth, boardHeight);
  Board* board2 = new Board(boardWidth, boardHeight);

  SetupMode setup(player1, player2, board1, board2);
  setup.Execute();

  // Both boards will be ready at this point.
  GameplayMode game(player1, player2, board1, board2, config);
  game.Execute();

  return 0;
}