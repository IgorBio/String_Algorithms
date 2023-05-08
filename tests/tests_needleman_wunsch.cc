#include <gtest/gtest.h>

#include "../dna/dna.h"

TEST(NeedlemanWunsch, CorrectInput1) {
  int match = 1;
  int mismatch = -1;
  int gap = -2;
  DNA::Str str_1 = "GGGCGACACTCCACCATAGA";
  DNA::Str str_2 = "GGCGACACCCACCATACAT";
  DNA::Alignments alignments =
      DNA::NeedlemanWunschAlgorithm(match, mismatch, gap, str_1, str_2);
  EXPECT_EQ(std::get<0>(alignments), 10);
  EXPECT_EQ(std::get<1>(alignments), "GGGCGACACTCCACCATAGA-");
  EXPECT_EQ(std::get<2>(alignments), " |||||||| |||||||| | ");
  EXPECT_EQ(std::get<3>(alignments), "-GGCGACAC-CCACCATACAT");
}

TEST(NeedlemanWunsch, CorrectInput2) {
  int match = 2;
  int mismatch = -2;
  int gap = -3;
  DNA::Str str_1 = "GTATGAAGCCGTTAGGGCCA";
  DNA::Str str_2 = "ATGAAGCCATTCGGGACA";
  DNA::Alignments alignments =
      DNA::NeedlemanWunschAlgorithm(match, mismatch, gap, str_1, str_2);
  EXPECT_EQ(std::get<0>(alignments), 18);
  EXPECT_EQ(std::get<1>(alignments), "GTATGAAGCCGTTAGGGCCA");
  EXPECT_EQ(std::get<2>(alignments), "  |||||||| || ||| ||");
  EXPECT_EQ(std::get<3>(alignments), "--ATGAAGCCATTCGGGACA");
}

TEST(NeedlemanWunsch, EmptyStr1) {
  int match = 1;
  int mismatch = -1;
  int gap = -2;
  DNA::Str str_1 = "";
  DNA::Str str_2 = "ATGAAGCCATTCGGGACA";
  DNA::Alignments alignments =
      DNA::NeedlemanWunschAlgorithm(match, mismatch, gap, str_1, str_2);
  EXPECT_EQ(std::get<0>(alignments), 0);
  EXPECT_EQ(std::get<1>(alignments), "------------------");
  EXPECT_EQ(std::get<2>(alignments), "                  ");
  EXPECT_EQ(std::get<3>(alignments), "ATGAAGCCATTCGGGACA");
}

TEST(NeedlemanWunsch, EmptyStr2) {
  int match = 1;
  int mismatch = -1;
  int gap = -2;
  DNA::Str str_1 = "ATGAAGCCATTCGGGACA";
  DNA::Str str_2 = "";
  DNA::Alignments alignments =
      DNA::NeedlemanWunschAlgorithm(match, mismatch, gap, str_1, str_2);
  EXPECT_EQ(std::get<0>(alignments), 0);
  EXPECT_EQ(std::get<1>(alignments), "ATGAAGCCATTCGGGACA");
  EXPECT_EQ(std::get<2>(alignments), "                  ");
  EXPECT_EQ(std::get<3>(alignments), "------------------");
}

TEST(NeedlemanWunsch, EmptyStr3) {
  int match = 1;
  int mismatch = -1;
  int gap = -2;
  DNA::Str str_1 = "";
  DNA::Str str_2 = "";
  DNA::Alignments alignments =
      DNA::NeedlemanWunschAlgorithm(match, mismatch, gap, str_1, str_2);
  EXPECT_EQ(std::get<0>(alignments), 0);
  EXPECT_EQ(std::get<1>(alignments), "");
  EXPECT_EQ(std::get<2>(alignments), "");
  EXPECT_EQ(std::get<3>(alignments), "");
}
