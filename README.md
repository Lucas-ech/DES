DES
===
This program is my own DES algorithm implementation made in C++11.

Supported modes : 
- ECB
- CBC

Compilation
-----------
 
```bash
g++ --std=c++11 -Wall -o DES *.cpp
```

How it works
-------

First, you have to create a DES instance :
```c++
std::string data("Hello World!");
Key key("0123456789ABCDEF");

// ECB Mode
DES ecb(data, key);

// CBC Mode
DES cbc(data, key, 0xcbcbcbcbcbcbcbcb);
```
Note: data can be **plaintext** or **ciphertext**.

Next, you can encrypt or decrypt like this :
```c++
// Encryption
std::string ciphertext = enc.encrypt();

// Decryption
std::string plaintext = enc.decrypt();
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

    DES des(plain, key);

    std::string cipher = des.encrypt();

    des.setData(cipher);

    std::string recovered = des.decrypt();

    std::cout << recovered << std::endl; // Hello World!
    
    return 0;
}
```
