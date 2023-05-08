#ifndef SRC_VIEW_CONSOLE_H
#define SRC_VIEW_CONSOLE_H

#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

struct Item {
  std::string name = "Default";
  std::function<void()> run_item;
};

class Console {
 public:
  static std::string InputFilename(const std::string& msg);
  void AddItem(Item item);
  void Run();

 private:
  int InputNumber();
  void MainLoop();
  std::string Align(const std::string& str);
  void ShowMenu();

 private:
  std::vector<Item> items_;
};

#endif  // SRC_VIEW_CONSOLE_H
