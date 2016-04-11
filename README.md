DES
===
This program is my own DES algorithm implementation made in C++11.

Compilation
-----------
 
```bash
g++ --std=c++11 -Wall -o DES *.cpp
```

Run
---

Main functions :
```c++
// Takes a string plain to encrypt and returns the cipher
std::string DES::encrypt(const std::string &plain, Key &key);
```

```c++
// Takes a string cipher to decrypt and returns the plain
std::string DES::decrypt(const std::string &cipher, Key &key);
```

Example
-------

```c++
#include <iostream>
#include <string>
#include "Key.h"
#include "DES.h"

int main(int argc, char const *argv[])
{
    std::string plain("Hello World!");
    Key key("0123456789ABCDEF");

    std::string cipher = DES::encrypt(plain, key);
    std::string recovered = DES::decrypt(cipher, key);

    std::cout << recovered << std::endl; //Hello World!
    
    return 0;
}
```
