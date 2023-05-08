#include "dna.h"

namespace DNA {

/*
 When you manage to shove the unpushable, you piss off the god of collisions
 */
DNA::Positions RabinKarpAlgorithm(const Str &txt, const Str &sub, size_t mod) {
  Positions positions;

  const size_t sub_size = sub.size();
  const size_t txt_size = txt.size();

  if (sub_size > txt_size or !sub_size or !txt_size) return positions;

  size_t txt_hash = GetCharCode(txt[0]) % mod;
  size_t sub_hash = GetCharCode(sub[0]) % mod;
  size_t hash = 1u;

  for (size_t i = 1u; i < sub_size; ++i) {
    txt_hash = (txt_hash * kBase + GetCharCode(txt[i])) % mod;
    sub_hash = (sub_hash * kBase + GetCharCode(sub[i])) % mod;
    hash = (hash * kBase) % mod;
  }

  for (size_t i = 0u; i <= txt_size - sub_size; ++i) {
    if (txt_hash == sub_hash and txt.compare(i, sub_size, sub) == 0) {
      positions.push_back(i);
    }

    txt_hash =
        (((txt_hash - (GetCharCode(txt[i]) * hash) % mod) + mod) * kBase +
         GetCharCode(txt[i + sub_size])) %
        mod;
  }

  return positions;
}

size_t GetCharCode(char ch) {
  if (ch == 'A') return 1u;
  if (ch == 'C') return 2u;
  if (ch == 'G') return 3u;
  if (ch == 'T') return 4u;
  return 0u;
}

/*
 Needleman-Wunsch algorithm for determining the optimal alignment between two
 strings assuming a given score for hits, gaps and mismatches.
*/
Alignments NeedlemanWunschAlgorithm(int match, int mismatch, int gap,
                                    const Str &str_1, const Str &str_2) {
  const int size_1 = str_1.size();
  const int size_2 = str_2.size();

  if (!size_2)
    return std::make_tuple(0, str_1, Str(size_1, ' '), Str(size_1, '-'));

  Matrix nw = Matrix(size_1 + 1, Vector(size_2 + 1));

  for (int i = 0; i <= size_1; ++i) nw[i][0] = nw[0][i] = i * gap;

  for (int i = 1; i <= size_1; ++i) {
    for (int j = 1; j <= size_2; ++j) {
      int value = (str_1[i - 1] == str_2[j - 1]) ? match : mismatch;
      nw[i][j] = std::max(nw[i - 1][j - 1] + value,
                          std::max(nw[i - 1][j] + gap, nw[i][j - 1] + gap));
    }
  }
  int score = nw[size_1][size_2];

  Str seq_1, seq_2, seq_3;
  int idx_1 = size_1, idx_2 = size_2;

  while (idx_1 != 0 or idx_2 != 0) {
    if (idx_1 == 0) {
      seq_1 += '-';
      seq_3 += str_2[idx_2 - 1];
      --idx_2;
    } else if (idx_2 == 0) {
      seq_1 += str_1[idx_1 - 1];
      seq_3 += '-';
      --idx_1;
    } else {
      int value = (str_1[idx_1 - 1] == str_2[idx_2 - 1]) ? match : mismatch;
      if (nw[idx_1][idx_2] == nw[idx_1 - 1][idx_2 - 1] + value) {
        seq_1 += str_1[idx_1 - 1];
        seq_3 += str_2[idx_2 - 1];
        --idx_1;
        --idx_2;
      } else if (nw[idx_1 - 1][idx_2] > nw[idx_1][idx_2 - 1]) {
        seq_1 += str_1[idx_1 - 1];
        seq_3 += '-';
        --idx_1;
      } else {
        seq_1 += '-';
        seq_3 += str_2[idx_2 - 1];
        --idx_2;
      }
    }
    seq_2 += seq_1.back() == seq_3.back() ? '|' : ' ';
  }

  std::reverse(seq_1.begin(), seq_1.end());
  std::reverse(seq_2.begin(), seq_2.end());
  std::reverse(seq_3.begin(), seq_3.end());

  return std::make_tuple(score, seq_1, seq_2, seq_3);
}

bool RegexAlgorithm(const Str &txt, const Str &re) {
  return MatchSymbol(txt, 0, re, 0);
}

bool MatchSymbol(const Str &txt, size_t t_idx, const Str &re, size_t r_idx) {
  if (re.size() == r_idx) {
    return txt.size() == t_idx;
  }
  if (r_idx + 1 < re.size() and re[r_idx + 1] == '+') {
    return MatchPlus(re[r_idx], txt, t_idx, re, r_idx + 2);
  }
  if (re[r_idx] == '?') {
    return (MatchSymbol(txt, t_idx + 1, re, r_idx + 1) or
            MatchSymbol(txt, t_idx, re, r_idx + 1));
  }
  if (re[r_idx] == '*') {
    return MatchStar(txt, t_idx, re, r_idx + 1);
  }
  if (re[r_idx] == '.' or re[r_idx] == txt[t_idx]) {
    return MatchSymbol(txt, t_idx + 1, re, r_idx + 1);
  }

  return false;
}

bool MatchStar(const Str &txt, size_t t_idx, const Str &re, size_t r_idx) {
  do {
    if (MatchSymbol(txt, t_idx, re, r_idx)) return true;
  } while (t_idx++ < txt.size());
  return false;
}

bool MatchPlus(char ch, const Str &txt, size_t t_idx, const Str &re,
               size_t r_idx) {
  do {
    if (MatchSymbol(txt, t_idx, re, r_idx)) return true;
  } while (t_idx < txt.size() and (txt[t_idx++] == ch or ch == '.'));
  return false;
}

int KSimilarAlgorithm(const Str &str_1, const Str &str_2) {
  if (str_1 == str_2) return 0;
  if (str_1.size() != str_2.size()) {
    throw std::logic_error("Strings has different sizes");
  }
  if (std::count_if(str_1.begin(), str_1.end(), [&](char ch) {
        return std::count(str_1.begin(), str_1.end(), ch) !=
               std::count(str_2.begin(), str_2.end(), ch);
      }) > 0) {
    throw std::logic_error("Strings are not anagrams");
  }
  std::unordered_set<Str> visited;
  std::queue<std::pair<Str, int>> queue;
  queue.push({str_1, 0});
  visited.insert(str_1);
  while (!queue.empty()) {
    auto [cur, swap_cnt] = queue.front();
    queue.pop();
    if (cur == str_2) return swap_cnt;
    size_t i = 0;
    while (cur[i] == str_2[i]) ++i;
    for (size_t j = i + 1; j < cur.size(); ++j) {
      if (cur[j] == str_2[i] and cur[j] != str_2[j]) {
        std::swap(cur[i], cur[j]);
        if (visited.count(cur) == 0) {
          queue.push({cur, swap_cnt + 1});
          visited.insert(cur);
        }
        std::swap(cur[i], cur[j]);
      }
    }
  }
  return -1;
}

Str MinWindowAlgorithm(const Str &str_1, const Str &str_2) {
  const int size_1 = str_1.length();
  const int size_2 = str_2.length();

  if (size_1 < size_2 or !size_1 or !size_2) return "";

  std::unordered_map<char, int> mp;
  int parity = 0;
  for (const auto &ch : str_2) {
    ++mp[ch];
    ++parity;
  }

  int left = 0, right = -1, start = -1, min_len = size_1;
  while (right < size_1) {
    if (parity == 0) {
      int len = right - left + 1;
      if (len < min_len) {
        min_len = len;
        start = left;
      }

      if (CharInMap(mp, str_1[left]) and (++mp[str_1[left]] >= 1)) ++parity;

      ++left;
    } else {
      if (++right >= size_1) break;

      if (CharInMap(mp, str_1[right]) and (--mp[str_1[right]] >= 0)) --parity;

      if (start > -1) {
        if (CharInMap(mp, str_1[left]) and (++mp[str_1[left]] >= 1)) ++parity;

        ++left;
      }
    }
  }

  return (start > -1) ? str_1.substr(start, min_len) : "";
}

bool CharInMap(const std::unordered_map<char, int> &mp, char ch) {
  return mp.find(ch) != mp.end();
}

bool CorrectSequence(const Str &str) {
  return std::all_of(str.begin(), str.end(), [](char ch) {
    return ch == 'A' or ch == 'C' or ch == 'G' or ch == 'T';
  });
}

}  // namespace DNA
