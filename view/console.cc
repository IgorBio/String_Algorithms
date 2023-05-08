#include "console.h"

std::string menu_color = "\u001b[44;1m";
std::string err_color = "\u001b[41;1m";
std::string end_color = "\u001b[0m";

std::string Console::InputFilename(const std::string& msg) {
  std::string input;
  std::cout << menu_color << msg << end_color << "\n\n";
  std::cin >> input;
  std::cout << std::endl;
  return input;
}

void Console::AddItem(Item item) { items_.push_back(item); }

void Console::Run() {
  system("clear");
  MainLoop();
}

int Console::InputNumber() {
  int input;
  while (true) {
    std::cin >> input;
    if (std::cin.fail() or input < 0 or input > 5) {
      system("clear");
      std::cout << err_color << Align("WRONG INPUT!") << end_color << "\n\n";
      ShowMenu();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      return input;
    }
  }
}

std::string Console::Align(const std::string& str) {
  std::string aligned;
  std::string addition((50 - str.size()) / 2, ' ');
  aligned.append(addition);
  aligned.append(str);
  aligned.append(addition);
  while (aligned.size() < 50) aligned.append(" ");
  return aligned;
}

void Console::ShowMenu() {
  std::cout << menu_color << Align("DNA ANALYZER") << end_color;
  std::cout << "\n\n";
  std::cout << menu_color << Align("CHOOSE ITEM") << end_color;
  std::cout << "\n\n";
  for (size_t i = 0; i < items_.size(); i++) {
    std::cout << "     ";
    std::cout << i + 1 << ". " << items_[i].name << std::endl;
  }
  std::cout << "     ";
  std::cout << "0. Exit\n\n";
  std::cout << menu_color << Align(" ") << end_color << "\n\n";
}

void Console::MainLoop() {
  while (true) {
    ShowMenu();
    int choice = InputNumber() - 1;
    if (choice == -1) break;
    try {
      items_[choice].run_item();
    } catch (const std::exception& e) {
      system("clear");
      std::cerr << err_color << e.what() << end_color << " 🚨" << std::endl;
    }
    std::cout << std::endl;
  }
  system("clear");
  std::cout << menu_color << Align("HOPE YOU ENJOY!👋") << end_color << "\n\n";
}
