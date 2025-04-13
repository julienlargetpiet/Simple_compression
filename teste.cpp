#include "simple_compression.h"

int main() {

  // Single file compression

  //std::string inpt_file = "pre_teste_file.txt";
  //std::string out_file = "compressed_teste_file.txt";
  //std::string out_file2 = "teste_file.txt";
  //std::string k_file = "k";
  //unsigned int n_pattern = 3;
  //unsigned int level = 3;

  //compression(inpt_file, n_pattern, k_file, level, out_file);
  //decompression(out_file, k_file, out_file2);

  //Directory compression

  std::string inpt_path = "teste_dir";
  std::string out_file = "compressed_teste_file.txt";
  std::string k_file = "k";
  unsigned int n_pattern = 3;
  unsigned int level = 3;

  compression_dir(inpt_path, n_pattern, k_file, level, out_file);
  decompression_dir(out_file, k_file, "out_decompression");

  return 0;
};


