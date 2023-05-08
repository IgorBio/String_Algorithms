#include <fstream>

#include "./dna/dna.h"
#include "./view/console.h"

std::string ans_color = "\u001b[42;1m";
std::string end_clr = "\u001b[0m";

void SolveRabinKarp(std::string txt_path, std::string sub_path) {
  std::ifstream txt_input(txt_path);
  std::ifstream sub_input(sub_path);

  std::string txt, sub;
  txt_input >> txt;
  sub_input >> sub;

  if (!txt_input.is_open() or txt_input.fail())
    throw std::logic_error("FAIL TO READ TEXT");

  if (!sub_input.is_open() or sub_input.fail())
    throw std::logic_error("FAIL TO READ SUBSTRING");

  if (!DNA::CorrectSequence(sub))
    throw std::logic_error("TEXT CONTAINS INVALID SYMBOLS");

  if (!DNA::CorrectSequence(txt))
    throw std::logic_error("SUBSTRING CONTAINS INVALID SYMBOLS");

  DNA::Positions pos = DNA::RabinKarpAlgorithm(txt, sub, DNA::kMode);

  system("clear");

  std::cout << ans_color << "POSITIONS OF SUBSTRING IN TEXT:" << end_clr
            << std::endl
            << std::endl;
  for (auto p : pos) std::cout << ans_color << p << " ";
  std::cout << end_clr << " 🚀" << std::endl;
}

void FirstItem() {
  std::string txt_path = Console::InputFilename("ENTER PATH TO TEXT:");
  std::string sub_path = Console::InputFilename("ENTER PATH TO SUBSTRING:");
  SolveRabinKarp(txt_path, sub_path);
}

void SolveNeedlemanWunsch(std::string path) {
  std::ifstream input(path);

  int match, mismatch, gap;
  std::string str_1, str_2;

  input >> match >> mismatch >> gap >> str_1 >> str_2;

  if (!input.is_open() or input.fail())
    throw std::logic_error("FAIL TO READ FILE");

  if (!DNA::CorrectSequence(str_1) or !DNA::CorrectSequence(str_2))
    throw std::logic_error("STRING CONTAINS INVALID SYMBOLS");

  DNA::Alignments alignments =
      DNA::NeedlemanWunschAlgorithm(match, mismatch, gap, str_1, str_2);

  auto [score, first, second, third] = alignments;

  system("clear");

  std::cout << ans_color << "SCORE OF THE BEST ALIGNMENT: " << score << end_clr
            << std::endl
            << std::endl;
  std::cout << ans_color << first << end_clr << std::endl;
  std::cout << second << std::endl;
  std::cout << ans_color << third << end_clr << std::endl;
}

void SecondItem() {
  std::string path = Console::InputFilename("ENTER PATH TO FILE:");
  SolveNeedlemanWunsch(path);
}

void SolveRegexMatching(std::string path) {
  std::string txt, re;

  std::ifstream input(path);
  input >> txt >> re;

  if (!input.is_open() or input.fail())
    throw std::logic_error("FAIL TO READ FILE");

  if (!DNA::CorrectSequence(txt))
    throw std::logic_error("STRING CONTAINS INVALID SYMBOLS");

  system("clear");

  std::cout << ans_color
            << (DNA::RegexAlgorithm(txt, re) ? "True ✅" : "False ❌") << end_clr
            << std::endl;
}

void ThirdItem() {
  std::string path = Console::InputFilename("ENTER PATH TO FILE:");
  SolveRegexMatching(path);
}

void SolveSimilarFinding(std::string path) {
  std::string str_1, str_2;

  std::ifstream input(path);
  input >> str_1 >> str_2;

  if (!input.is_open() or input.fail())
    throw std::logic_error("FAIL TO READ FILE");

  if (!DNA::CorrectSequence(str_1) or !DNA::CorrectSequence(str_2))
    throw std::logic_error("STRING CONTAINS INVALID SYMBOLS");

  system("clear");

  std::cout << ans_color << "k = " << DNA::KSimilarAlgorithm(str_1, str_2)
            << end_clr << " 🚀" << std::endl;
}

void FourthItem() {
  std::string path = Console::InputFilename("ENTER PATH TO FILE:");
  SolveSimilarFinding(path);
}

void SolveMinWindowFinding(std::string path) {
  std::string str_1, str_2;

  std::ifstream input(path);
  input >> str_1 >> str_2;

  if (!input.is_open() or input.fail())
    throw std::logic_error("FAIL TO READ FILE");

  if (!DNA::CorrectSequence(str_1) or !DNA::CorrectSequence(str_2))
    throw std::logic_error("STRING CONTAINS INVALID SYMBOLS");

  system("clear");

  std::cout << ans_color << "MINIMUM WINDOW SUBSTRING: "
            << DNA::MinWindowAlgorithm(str_1, str_2) << end_clr << " 🚀"
            << std::endl;
}

void FifthItem() {
  std::string path = Console::InputFilename("ENTER PATH TO FILE:");
  SolveMinWindowFinding(path);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    Console console;
    console.AddItem({"DNA search with the Rabin-Karp algorithm", FirstItem});
    console.AddItem({"Sequence alignment with the NW algorithm", SecondItem});
    console.AddItem({"Matching regular expressions", ThirdItem});
    console.AddItem({"Finding k-similar of two strings", FourthItem});
    console.AddItem({"Finding minimum window substring", FifthItem});
    console.Run();
  } else if (argc == 4 and std::string(argv[1]) == "-1") {
    SolveRabinKarp(argv[2], argv[3]);
  } else if (argc == 3 and std::string(argv[1]) == "-2") {
    SolveNeedlemanWunsch(argv[2]);
  } else if (argc == 3 and std::string(argv[1]) == "-3") {
    SolveRegexMatching(argv[2]);
  } else if (argc == 3 and std::string(argv[1]) == "-4") {
    SolveSimilarFinding(argv[2]);
  } else if (argc == 3 and std::string(argv[1]) == "-5") {
    SolveMinWindowFinding(argv[2]);
  } else {
    system("clear");
    std::cout << "\u001b[41;1mRUN PARAMETERS ARE NOT APROPRIATE. TRY "
                 "AGAIN\u001b[0m 🚨\n";
  }
  return 0;
}
