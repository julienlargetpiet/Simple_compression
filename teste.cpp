#include "simple_compression.h"

int main() {

  std::string inpt_file = "pre_teste_file.txt";
  std::string out_file = "compressed_teste_file.txt";
  std::string out_file2 = "teste_file.txt";
  std::string k_file = "k";
  unsigned int n_pattern = 3;
  //unsigned int cnt = 1;
  unsigned int level = 3;

  compression(inpt_file, n_pattern, k_file, level, out_file);
  decompression(out_file, k_file, out_file2);
  //std::string teste = "12345";
  //teste.erase(teste.begin() + 1, teste.begin() + 3);
  //std::cout << teste << "\n";

  return 0;
};


