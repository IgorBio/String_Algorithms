#include <gtest/gtest.h>

#include "../dna/dna.h"

TEST(KSimilarAlgorithm, CorrectInput1) {
  DNA::Str str_1 = "GGCGACACC";
  DNA::Str str_2 = "AGCCGCGAC";
  EXPECT_EQ(DNA::KSimilarAlgorithm(str_1, str_2), 3);
}

TEST(KSimilarAlgorithm, CorrectInput2) {
  DNA::Str str_1 = "GTAGTAATG";
  DNA::Str str_2 = "GTAGTAGTA";
  EXPECT_EQ(DNA::KSimilarAlgorithm(str_1, str_2), 1);
}

TEST(KSimilarAlgorithm, CorrectInput3) {
  DNA::Str str_1 = "ATAGTAAGG";
  DNA::Str str_2 = "GGAGTAATA";
  EXPECT_EQ(DNA::KSimilarAlgorithm(str_1, str_2), 2);
}

TEST(KSimilarAlgorithm, CorrectInput4) {
  DNA::Str str_1 = "AATGGAAAA";
  DNA::Str str_2 = "AGAAATAGA";
  EXPECT_EQ(DNA::KSimilarAlgorithm(str_1, str_2), 3);
}

TEST(KSimilarAlgorithm, Exception) {
  EXPECT_THROW(DNA::KSimilarAlgorithm("G", ""), std::logic_error);

  EXPECT_THROW(DNA::KSimilarAlgorithm("GTA", "GTC"), std::logic_error);

  EXPECT_THROW(DNA::KSimilarAlgorithm("", "GTC"), std::logic_error);
}
