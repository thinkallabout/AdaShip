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
  ConfigFile config_file;

  MainMenu main_menu;
  main_menu.Execute();

  Player* player1;
  Player* player2;

  HumanPlayer* humanPlayer1 = new HumanPlayer(config_file);
  BadNpcPlayer* npcPlayer1 = new BadNpcPlayer(config_file);
  HumanPlayer* humanPlayer2 = new HumanPlayer(config_file);
  BadNpcPlayer* npcPlayer2 = new BadNpcPlayer(config_file);

  GameModeConfig config = main_menu.GetConfig();
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