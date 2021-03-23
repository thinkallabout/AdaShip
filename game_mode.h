// Provides the base GameMode class.

namespace google {

// A GameMode awaits a text input, then runs the Tick() and Render()
// functions.
class GameMode {
 public:
  GameMode() : _active(true) {}

  void Execute() {
    while (_active) {
      Render();
      WaitForInput();
      Tick();
    }
  }

  virtual void WaitForInput() = 0;
  virtual void Tick() = 0;
  virtual void Render() = 0;

 protected:
  bool _active;
};

} // namespace google