#include <gtest/gtest.h>

#include "../dna/dna.h"

TEST(MinWindowAlgorithm, CorrectInput1) {
  DNA::Str str_1 = "GGCGACACCCACCATACAT";
  DNA::Str str_2 = "TGT";
  EXPECT_EQ(DNA::MinWindowAlgorithm(str_1, str_2), "GACACCCACCATACAT");
}

TEST(MinWindowAlgorithm, CorrectInput2) {
  DNA::Str str_1 = "GTAGTATGATGA";
  DNA::Str str_2 = "GTA";
  EXPECT_EQ(DNA::MinWindowAlgorithm(str_1, str_2), "GTA");
}

TEST(MinWindowAlgorithm, CorrectInput3) {
  DNA::Str str_1 = "TAGGTA";
  DNA::Str str_2 = "GTA";
  EXPECT_EQ(DNA::MinWindowAlgorithm(str_1, str_2), "TAG");
}

TEST(MinWindowAlgorithm, CorrectInput4) {
  DNA::Str str_1 = "ATTGTA";
  DNA::Str str_2 = "GTA";
  EXPECT_EQ(DNA::MinWindowAlgorithm(str_1, str_2), "GTA");
}

TEST(MinWindowAlgorithm, EmptyStr1) {
  DNA::Str str_1 = "";
  DNA::Str str_2 = "GTA";
  EXPECT_EQ(DNA::MinWindowAlgorithm(str_1, str_2), "");
}

TEST(MinWindowAlgorithm, EmptyStr2) {
  DNA::Str str_1 = "GTA";
  DNA::Str str_2 = "";
  EXPECT_EQ(DNA::MinWindowAlgorithm(str_1, str_2), "");
}

TEST(CorrectSequence, CorrectInput1) {
  EXPECT_TRUE(DNA::CorrectSequence("GTAAGTTAGCCAGCTGAC"));
}

TEST(CorrectSequence, CorrectInput2) { EXPECT_TRUE(DNA::CorrectSequence("")); }

TEST(CorrectSequence, IncorrectInput1) {
  EXPECT_FALSE(DNA::CorrectSequence("GTAAGTTAGCCAGCTGACX"));
}
