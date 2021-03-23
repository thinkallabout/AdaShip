// Provides the MainMenu.

#include <cstdlib>

namespace google {

class MainMenu : public GameMode {
 public:
  void WaitForInput() override {
    std::cout << "Choose a game mode or quit:"               << std::endl
              << "\t1. Player vs. computer"                  << std::endl
              << "\t2. Player vs. player"                    << std::endl
              << "\t3. Player vs. computer (salvo)"          << std::endl
              << "\t4. Player vs. player (salvo)"            << std::endl
              << "\t5. Player vs. computer (hidden mines)"   << std::endl
              << "\t6. Player vs. player (hidden mines)"     << std::endl
              << "\t7. Computer vs. computer (hidden mines)" << std::endl
              << "\t8. Quit"                                 << std::endl;
    int buffer;
    std::cin >> buffer;

    if (buffer < 0 || buffer > 8) {
      std::cout << "Unknown command." << std::endl;
      return;
    }

    switch (buffer) {
      case 1:
        _active = false;
        break;
      // TODO(cameron): Implement other game modes here.
      case 8:
        QuitGame();
    }
  }

  void Render() override {}
  void Tick() override {}

 private:
  void QuitGame() {
    std::cout << "Bye bye!" << std::endl;
    exit(0);
  }
};

} // namespace google