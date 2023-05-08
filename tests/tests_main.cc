#include <gtest/gtest.h>

#include "./tests_ksimilar.cc"
#include "./tests_min_window.cc"
#include "./tests_needleman_wunsch.cc"
#include "./tests_rabin_karp.cc"
#include "./tests_regexp.cc"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
