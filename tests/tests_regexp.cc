#include <gtest/gtest.h>

#include "../dna/dna.h"

TEST(RegexAlgorithm, CorrectInput1) {
  DNA::Str txt = "GGCGACACCCACCATACAT";
  DNA::Str re = "G?G*AC+A*A.";
  EXPECT_TRUE(DNA::RegexAlgorithm(txt, re));
}

TEST(RegexAlgorithm, CorrectInput2) {
  DNA::Str txt = "GTAGTATGATGA";
  DNA::Str re = "*";
  EXPECT_TRUE(DNA::RegexAlgorithm(txt, re));
}

TEST(RegexAlgorithm, CorrectInput3) {
  DNA::Str txt = "GTAGTATGATGA";
  DNA::Str re = "+";
  EXPECT_FALSE(DNA::RegexAlgorithm(txt, re));
}

TEST(RegexAlgorithm, CorrectInput4) {
  DNA::Str txt = "GTAGTATGATGA";
  DNA::Str re = "?";
  EXPECT_FALSE(DNA::RegexAlgorithm(txt, re));
}

TEST(RegexAlgorithm, CorrectInput5) {
  DNA::Str txt = "G";
  DNA::Str re = ".";
  EXPECT_TRUE(DNA::RegexAlgorithm(txt, re));
}

TEST(RegexAlgorithm, EmptyStr) {
  DNA::Str txt = "";
  DNA::Str re = "";
  EXPECT_TRUE(DNA::RegexAlgorithm(txt, re));
}

TEST(RegexAlgorithm, EmptyRe) {
  DNA::Str txt = "GTAGTATGATGA";
  DNA::Str re = "";
  EXPECT_FALSE(DNA::RegexAlgorithm(txt, re));
}

TEST(RegexAlgorithm, EmptyTxt) {
  DNA::Str txt = "";
  DNA::Str re = "?";
  EXPECT_TRUE(DNA::RegexAlgorithm(txt, re));
}
