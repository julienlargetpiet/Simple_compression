# Simple_compression

A text compression algorithm based on most frequent patterns detection and key compression association. The level of compression and the length of the repeated patterns have to be chosen.

## 1 file example (compression and then decompression)

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

## Directory example (compression and then decompression)

```
#include "simple_compression.h"

int main() {

  std::string inpt_path = "teste_dir";
  std::string out_file = "compressed_teste_file.txt";
  std::string k_file = "k";
  unsigned int n_pattern = 3;
  unsigned int level = 3;

  compression_dir(inpt_path, n_pattern, k_file, level, out_file);
  decompression_dir(out_file, k_file, "out_decompression");

  return 0;
};
```

>[Note]
>If a directory is empty it won't be taken in count.

```
$ tree teste_dir
├── oui2.txt
├── oui.txt
├── teste_dira
│   ├── a.txt
│   └── sub_dir
├── teste_dirb
│   ├── a.txt
│   ├── b.txt
│   └── sub_dir
│       ├── a.txt
│       └── sub_dir
└── teste_dirc
    └── a.txt
$ cat compressed_teste_file.txt
>jour j'aime\la se^<et\<^\smp sop\*>jour j'aime\la se^<et\<^\smp sop\**>jour j'aime\la se^<et\<^\smp sop\*>jour j'aime\la se^<et\<^\smp sop\*>jour j'aime\la se^<et\<^\smp sop\*>jour j'aime\la se^<et\<^\smp sop\*
$ cat k 
^mou
<le
>Bon*
^mou
<le
>Bon*
*^mou
<le
>Bon*
^mou
<le
>Bon*
^mou
<le
>Bon*
^mou
<le
>Bon*
teste_dir
oui2.txt
oui.txt
teste_dirb/b.txt
teste_dirb/a.txt
teste_dira/a.txt
teste_dirc/a.txt
teste_dirb/sub_dir/a.txt
$ tree out_decompression
out_decompression/
└── teste_dir
    ├── oui2.txt
    ├── oui.txt
    ├── teste_dira
    │   └── a.txt
    ├── teste_dirb
    │   ├── a.txt
    │   ├── b.txt
    │   └── sub_dir
    │       └── a.txt
    └── teste_dirc
        └── a.txt
```

# Forbidden characters

Compression keys used for compression are `^<>$;[]~\\*` and should not be used inside a document.
