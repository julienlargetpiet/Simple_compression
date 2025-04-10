# Simple_compression

A text compression algorithm based on most frequent patterns detection and key compression association. The level of compression and the length of the repeated patterns have to be chosen.

## Example (compression and then decompression)

```
#include "simple_compression.h"

int main() {

  std::string inpt_file = "pre_teste_file.txt";
  std::string out_file = "compressed_teste_file.txt";
  std::string out_file2 = "teste_file.txt";
  std::string k_file = "k";
  unsigned int n_pattern = 3;
  unsigned int level = 3;

  compression(inpt_file, n_pattern, k_file, level, out_file);
  decompression(out_file, k_file, out_file2);

  return 0;
};

```

```
$ wc -c pre_teste_file.txt
126 pre_teste_file.txt
$ g++ teste.cpp
$ ./a.out
$ wc -c compressed_teste_file.txt
96 compressed_teste_file.txt
$ wc -c k
15 k // We've saved 126 - (96 + 15) = 15 bits!
```


