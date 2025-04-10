#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <math.h>

unsigned int max(const std::vector<unsigned int> &x) {
  unsigned int rtn = x[0];
  for (std::vector<unsigned int>::const_iterator it = x.begin() + 1; it != x.end(); ++it) {
    if (rtn < *it) {
      rtn = *it;
    };
  };
  return rtn;
};

template <typename T, typename T2> unsigned int match(const std::vector<T> &source, const T2 &ptrn) {
  int cnt = 0;
  for (typename std::vector<T>::const_iterator i = source.begin(); i != source.end(); ++i) {
    if (*i == ptrn) {
      return cnt;
    };
    cnt += 1;
  };
  return -1;
};

std::string nb_to_letter(unsigned int x) {
  std::string alphabet_v = "^<>$;[]~`";
  std::string rtn_str = "";
  unsigned int cnt = 1;
  unsigned int rest_val2;
  unsigned int rest_val;
  unsigned int cur_val = 0;
  while (cur_val < x) {
    cur_val = std::pow(8, cnt);
    rest_val = x % cur_val;
    if (rest_val > 0) {
      rest_val2 = rest_val / std::pow(8, cnt - 1); 
      rtn_str.insert(0, 1, alphabet_v[rest_val2 - 1]);
    } else {
      rest_val = std::pow(8, cnt);
      rtn_str.insert(0, 1, 'z');
    };
    x -= rest_val;
    cnt += 1;
  };
  return rtn_str;
};

void sub_compression(std::string &x, unsigned int &n_pattern, std::string &k_file, unsigned int cnt) {
  unsigned int i;
  unsigned int i2;
  unsigned int max_val;
  unsigned int cur_idx;
  unsigned int sub_cnt = 0;
  unsigned int max_idx;
  std::string cur_key;
  std::string compressed_ptrn;
  std::vector<unsigned int> cur_maxv = {};
  std::vector<std::deque<char>> ref_ptrns;
  const unsigned int n = x.length();
  const unsigned int nb_iter = n - n_pattern + 1;
  if (n_pattern >= n) {
    return;
  };
  std::deque<char> cur_pattern = {};
  std::deque<char> cur_pattern2;
  for (i = 0; i < n_pattern; ++i) {
    cur_pattern.push_back(x[i]);
  };
  std::vector<unsigned int> freq_pattern = {0};
  freq_pattern.resize(nb_iter, 0);
  i = 1;
  while (i < nb_iter) {
    cur_pattern2 = {};
    for (i2 = 0; i2 < n_pattern; ++i2) {
      cur_pattern2.push_back(x[i2]);
    };
    if (cur_pattern == cur_pattern2) {
      freq_pattern[i - 1] += 1;
    };
    for (i2 = 1; i2 < nb_iter; ++i2) {
      cur_pattern2.pop_front();
      cur_pattern2.push_back(x[n_pattern + i2 - 1]);
      if (cur_pattern == cur_pattern2) {
        freq_pattern[i - 1] += 1;
      };
    };
    ref_ptrns.push_back(cur_pattern);
    cur_pattern.pop_front();
    cur_pattern.push_back(x[n_pattern + i - 1]);
    i += 1;
  };
  freq_pattern.pop_back();
  std::fstream out_f(k_file, std::ios::app);
  max_val = max(freq_pattern);
  max_idx = match(freq_pattern, max_val);
  cur_pattern = ref_ptrns[max_idx];
  for (i2 = 0; i2 < ref_ptrns.size(); ++i2) {
    if (cur_pattern == ref_ptrns[i2]) {
      cur_maxv.push_back(i2);
    };
  };
  cur_key = nb_to_letter(cnt);
  compressed_ptrn = "";
  for (i2 = cur_maxv[0]; i2 < cur_maxv[0] + n_pattern; ++i2) {
    compressed_ptrn.push_back(x[i2]);
  };
  out_f << cur_key + compressed_ptrn + "\n";
  for (i2 = 0; i2 < cur_maxv.size(); ++i2) {
    cur_idx = cur_maxv[i2];
    x.erase(x.begin() + cur_idx - sub_cnt, x.begin() + cur_idx + n_pattern - sub_cnt);
    for (i = 0; i < cur_key.length(); ++i) {
      x.insert(x.begin() + cur_idx - sub_cnt + i, cur_key[i]);
    };
    sub_cnt += n_pattern;
    sub_cnt -= cur_key.length();
  };
};

void compression(std::string &inpt_file, unsigned int &n_pattern, std::string &k_file, unsigned int &level, std::string &out_file) {
  std::fstream out_f(k_file, std::ios::out);
  out_f << "";
  std::string x = "";
  std::fstream r_file(inpt_file);
  std::string currow;
  while (getline(r_file, currow)) {
    x += currow;
    x.push_back('\\');
  };
  for (unsigned int cnt = 1; cnt <= level; ++cnt) {
    sub_compression(x, n_pattern, k_file, cnt);
  };
  std::fstream out_f2(out_file, std::ios::out);
  out_f2 << x;
};

void decompression(std::string &inpt_file, std::string &k_file, std::string &out_f) {
  std::fstream r_file(inpt_file);
  std::fstream r_k_file(k_file);
  std::fstream out_file(out_f, std::ios::out);
  std::string currow;
  std::string x = "";
  std::vector<std::deque<char>> keys_valv = {};
  std::vector<std::deque<char>> keys_keyv = {};
  int i;
  unsigned int i2;
  unsigned int i3;
  unsigned int cur_len;
  unsigned int cur_len2;
  std::deque<char> cur_keyval;
  std::deque<char> cur_pattern;
  std::deque<char> cur_key;
  while (getline(r_file, currow)) {
    x += currow;
    x.push_back('\n');
  };
  unsigned int n;
  unsigned int cnt = 1;
  unsigned int cnt2 = 1;
  while (getline(r_k_file, currow)) {
    i = 0;
    cur_keyval = {};
    while (i < cnt2) {
      cur_keyval.push_back(currow[i]);
      i += 1;
    };
    keys_keyv.push_back(cur_keyval);
    cur_keyval = {};
    while (i < currow.length()) {
      cur_keyval.push_back(currow[i]);
      i += 1;
    };
    keys_valv.push_back(cur_keyval);
    cnt += 1;
    if (cnt > std::pow(8, cnt2)) {
      cnt2 += 1;
    };
  };
  for (i = keys_keyv.size() - 1; i > -1; --i) {
    n = x.length();
    cur_key = keys_keyv[i];
    cur_keyval = keys_valv[i];
    cur_len = cur_key.size();
    cur_len2 = cur_keyval.size();
    cur_pattern = {};
    for (i2 = 0; i2 < cur_len; ++i2) {
      cur_pattern.push_back(x[i2]);
    };
    if (cur_pattern == cur_key) {
      x.erase(x.begin(), x.begin() + cur_len);
      for (i3 = 0; i3 < cur_len2; ++i3) {
        x.insert(x.begin() + i3, cur_keyval[i3]);
      };
    };
    n = x.length();
    i2 = 1;
    while (i2 < n - cur_len + 1) {
      cur_pattern.pop_front();
      cur_pattern.push_back(x[cur_len + i2 - 1]);
      if (cur_pattern == cur_key) {
        x.erase(x.begin() + i2, x.begin() + cur_len + i2);
        for (i3 = 0; i3 < cur_len2; ++i3) {
          x.insert(x.begin() + i2 + i3, cur_keyval[i3]);
        };
        n = x.length();
      };
      i2 += 1;
    };
  };
  for (i = 0; i < x.length() - 1; ++i) {
    if (x[i] == '\\') {
      x[i] = '\n';
    };
  };
  x.pop_back();
  out_file << x;
};



