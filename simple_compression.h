#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <math.h>
#include <filesystem>

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
  std::string alphabet_v = "^<>$;[]~";
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
  out_f.close();
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

std::string sub_compression2(std::string &x, unsigned int &n_pattern, std::string &k_file, unsigned int cnt, unsigned int &goal_cnt) {
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
  std::fstream out_f(k_file, std::ios::app);
  if (n_pattern >= n) {
    out_f << "*";
    out_f.close();
    return x;
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
  if (cnt < goal_cnt) {
    out_f << cur_key + compressed_ptrn + "\n";
  } else {
    out_f << cur_key + compressed_ptrn + "*\n";
  };
  out_f.close();
  for (i2 = 0; i2 < cur_maxv.size(); ++i2) {
    cur_idx = cur_maxv[i2];
    x.erase(x.begin() + cur_idx - sub_cnt, x.begin() + cur_idx + n_pattern - sub_cnt);
    for (i = 0; i < cur_key.length(); ++i) {
      x.insert(x.begin() + cur_idx - sub_cnt + i, cur_key[i]);
    };
    sub_cnt += n_pattern;
    sub_cnt -= cur_key.length();
  };
  return x;
};


void compression(std::string &inpt_file, unsigned int &n_pattern, std::string &k_file, unsigned int &level, std::string &out_file) {
  std::fstream out_f(k_file, std::ios::out);
  out_f << "";
  out_f.close();
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
  out_f2.close();
};

void compression2(std::string inpt_file, unsigned int n_pattern, std::string k_file, unsigned int level, std::string out_file) {
  std::string x = "";
  std::string x_ref;
  std::fstream r_file(inpt_file);
  std::string currow;
  while (getline(r_file, currow)) {
    x += currow;
    x.push_back('\\');
  };
  for (unsigned int cnt = 1; cnt <= level; ++cnt) {
    x_ref = x;
    x = sub_compression2(x, n_pattern, k_file, cnt, level);
    if (x_ref == x) {
      break;
    };
  };
  std::fstream out_f2(out_file, std::ios::app);
  out_f2 << x;
  out_f2 << "*";
  out_f2.close();
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
  out_file.close();
};

std::string decompression2(std::string &inpt_file, std::string &k_file) {
  std::string currow;
  std::string x = inpt_file;
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
  unsigned int n;
  unsigned int cnt = 1;
  unsigned int cnt2 = 1;
  const unsigned int n_k = k_file.length();
  i = 0;
  while (i < n_k) {
    cur_keyval = {};
    i2 = 0;
    while (i2 < cnt2) {
      cur_keyval.push_back(k_file[i + i2]);
      i2 += 1;
    };
    i += i2;
    keys_keyv.push_back(cur_keyval);
    cur_keyval = {};
    while (k_file[i] != '\\') {
      cur_keyval.push_back(k_file[i]);
      i += 1;
    };
    i += 1;
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
  for (i = 0; i < x.length(); ++i) {
    if (x[i] == '\\') {
      x[i] = '\n';
    };
  };
  return x;
};

std::vector<std::string> get_all(std::string &path) {
  std::string cur_path;
  std::string cur_path_dir_found;
  std::deque<std::string> vec_dirname = {path};
  std::vector<std::string> rtn_vec = {};
  int n = 0;
  while (n > -1) {
    cur_path = vec_dirname[n];
    for (const auto &entry : std::filesystem::directory_iterator(cur_path)) {
      cur_path_dir_found = entry.path();
      if (entry.is_directory()) {
        vec_dirname.push_front(cur_path_dir_found);
        n += 1;
      } else {
        rtn_vec.push_back(cur_path_dir_found);
      };
    };
  vec_dirname.pop_back();
  n -= 1;
  };
  return rtn_vec;
};

void compression_dir(std::string &path, unsigned int &n_pattern, std::string &k_file, unsigned int &level, std::string &out_f) {
  std::vector<std::string> all_files = get_all(path);
  std::string cur_file;
  std::fstream out_file(out_f, std::ios::out);
  out_file << "";
  std::fstream out_file2(k_file, std::ios::out);
  out_file2 << "";
  out_file2.close();
  unsigned int i = 0;
  unsigned int i2;
  unsigned int ref_len = path.length() + 1;
  const unsigned int n = all_files.size();
  std::string ref_path = path;
  for (i = 0; i < n; ++i) {
    cur_file = all_files[i];
    compression2(cur_file, n_pattern, k_file, level, out_f);
  };
  std::fstream out_file3(k_file, std::ios::app);
  out_file3 << ref_path << "\n";
  for (i = 0; i < n; ++i) {
    cur_file = all_files[i];
    cur_file.erase(cur_file.begin(), cur_file.begin() + ref_len);
    out_file3 << cur_file << "\n";
  };
  out_file3.close();
};

void create_filedata(std::string &path, std::string &data) {
  std::fstream out_f(path, std::ios::out);
  out_f << data;
  out_f.close();
};

void create_filenodata(std::string &path) {
  std::fstream out_f(path, std::ios::out);
  out_f << "";
  out_f.close();
};

void decompression_dir(std::string &inpt_file, std::string &k_file, std::string out_path = ".") {
  std::string x = "";
  std::string k_x = "";
  std::string currow;
  std::string cur_file;
  std::string cur_dir;
  std::string cur_x;
  std::string cur_k;
  std::string pre_path = "";
  std::vector<std::string> all_files = {};
  std::vector<std::string> all_dirs = {};
  std::fstream r_k_file(k_file);
  unsigned int strt_file;
  unsigned int i = 0;
  int i2;
  int i3;
  unsigned int n;
  unsigned int n2;
  unsigned int ref_strt_file;
  bool not_found;
  bool alrd_found;
  while (getline(r_k_file, currow)) {
    n = currow.length() + 1;
    k_x += currow;
    k_x.push_back('\\');
    i += n;
    if (currow[n - 2] == '*') {
      strt_file = i;
    };
  };
  n = i;
  i = strt_file;
  ref_strt_file = strt_file;
  while (k_x[i] != '\\') {
    pre_path.push_back(k_x[i]);
    i += 1;
  };
  pre_path = out_path + "/" + pre_path;
  std::filesystem::create_directories(pre_path);
  pre_path.push_back('/');
  strt_file = i + 1;
  for (i = strt_file; i < n; ++i) {
    if (k_x[i] != '\\') {
      cur_file.push_back(k_x[i]);
    } else {
      i2 = cur_file.length() - 1;
      while (i2 > -1) {
        if (cur_file[i2] == '/') {
          break;
        };
        i2 -= 1;
      };
      i3 = 0;
      cur_dir = "";
      while (i3 < i2) {
        cur_dir.push_back(cur_file[i3]);
        i3 += 1;
      };
      if (cur_dir != "") {
        alrd_found = 0;
        for (i3 = 0; i3 < all_dirs.size(); ++i3) {
          if (cur_dir == all_dirs[i3]) {
            alrd_found = 1;
            break;
          };
        };
      } else {
        alrd_found = 1;
      };
      if (!alrd_found) {
        all_dirs.push_back(cur_dir);
        cur_dir = pre_path + cur_dir;
        std::filesystem::create_directories(cur_dir);
      };
      all_files.push_back(cur_file);
      cur_file = "";
    };
  };
  n2 = all_files.size();
  std::fstream r_x_file(inpt_file);
  while (getline(r_x_file, currow)) {
    x += currow;
  };
  i2 = 0;
  i3 = 0;
  for (i = 0; i < n2; ++i) {
    cur_file = pre_path + all_files[i];
    cur_k = "";
    cur_x = "";
    while (x[i2] != '*') {
      cur_x.push_back(x[i2]);
      i2 += 1;
    };
    while (k_x[i3] != '*') {
      cur_k.push_back(k_x[i3]);
      i3 += 1;
    };
    cur_k.push_back('\\');
    if (cur_x != "") {
      cur_x = decompression2(cur_x, cur_k);
      create_filedata(cur_file, cur_x);
      i3 += 2;
    } else {
      create_filenodata(cur_file);
      i3 += 1;
    };
    i2 += 1;
  };
};


