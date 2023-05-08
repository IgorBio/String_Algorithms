#ifndef SRC_DNA_DNA_H
#define SRC_DNA_DNA_H

#include <algorithm>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace DNA {

using Str = std::string;
using Positions = std::vector<size_t>;
using Alignments = std::tuple<int, Str, Str, Str>;
using Vector = std::vector<int>;
using Matrix = std::vector<std::vector<int>>;

constexpr size_t kBase = 256u;
constexpr size_t kMode = 9973u;

Positions RabinKarpAlgorithm(const Str &txt, const Str &sub, size_t mod);

Alignments NeedlemanWunschAlgorithm(int match, int mismatch, int gap,
                                    const Str &str_1, const Str &str_2);

bool RegexAlgorithm(const Str &txt, const Str &re);

int KSimilarAlgorithm(const Str &str1, const Str &str2);

Str MinWindowAlgorithm(const Str &str_1, const Str &str_2);

size_t GetCharCode(char ch);
bool MatchSymbol(const Str &txt, size_t t_idx, const Str &re, size_t r_idx);
bool MatchStar(const Str &txt, size_t t_idx, const Str &re, size_t r_idx);
bool MatchPlus(char ch, const Str &txt, size_t t_idx, const Str &re,
               size_t r_idx);
bool CharInMap(const std::unordered_map<char, int> &mp, char ch);
bool CorrectSequence(const Str &str);

}  // namespace DNA

#endif  // SRC_DNA_DNA_H
