#include <iostream>
#include "game_mode.h"
#include "main_menu.h"
#include "setup.h"

int main() {
  // TODO(cameron): Add Board and Player objects. Get those from MainMenu which
  //                constructs them.

  google::MainMenu main_menu;
  main_menu.Execute();

  google::SetupMode setup;
  setup.Execute();

  return 0;
}