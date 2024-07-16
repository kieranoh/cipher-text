# Vigenère Cipher Project

This repository contains a C program that demonstrates the implementation of the Vigenère cipher and Variant Vigenère cipher. The program includes functionalities for encryption, decryption, and finding the key without prior knowledge of it.

## Features

- **Encrypt**: Encrypts plaintext using the Vigenère cipher with a given key.
- **Decrypt**: Decrypts ciphertext using the Vigenère cipher with a given key.
- **Attack**: Attempts to discover the encryption key and decrypt the ciphertext without prior knowledge of the key.

## Project Structure
- encrypt.c: encryption code for the the Vigenère cipher. Read the plain.txt and key.txt and it will return cipher.txt.
  
- decrypt.c: decryption code for the the Vigenère cipher with a given key. Read the cipher.txt and key.txt and it will return after_decypt.txt

- vigener_cipher_attack.c : the decryption code for the the the Vigenère cipher without key. The key and plain text will be give by cipher_result.txt
  
- encrypt_ascii.c : the encryption code for Variant Vigenère cipher. it will return the cipher_ascii.txt with hexadecimal


- README.md: This file, providing an overview and instructions for the project.

## Vigenère Cipher Overview

The Vigenère cipher is a method of encrypting alphabetic text by using a simple form of polyalphabetic substitution. A keyword is used, and each letter of the plaintext is shifted along some number of places determined by the corresponding letter of the keyword.

### Encryption
The encryption formula is:

```c
E[i] = (P[i] + K[i % key_length]) % 26

//where P is the plaintext, K is the key, and E is the encrypted text.
```


### Decryption
The decryption formula is:

```c

P[i] = (E[i] - K[i % key_length] + 26) % 26

//where P is the decrypted plaintext, K is the key, and E is the encrypted text.
```

## Variant Vigenère cipher

Unlike the Vigenère cipher the key is a string of bytes. The plaintext is a string of ASCII characters.

To encrypt, XOR each character in the plaintext with the next character of the key.

### Encryption
The encryption formula is:

```c
E[i] = (P[i] ^ K[i % key_length])

//where P is the plaintext, K is the key, and E is the encrypted text.
```


### Decryption
The decryption formula is:

```c

P[i] = (E[i] ^K[i % key_length] )

//where P is the decrypted plaintext, K is the key, and E is the encrypted text.
```

### example

this is the example for Variant Vigenère cipher

```c
plaintext = "Hello!" // 0x48 65 6C 6C 6F 21
key = {0xA1, 0x2F}
0x48 ^ 0xA1 =  0100 1000 ^ 1010 0001 = 1110 1001 = 0xE9

ciphertext =  {0xE9 ,0x4A ,0xCD ,0x43 ,0xCE ,0x0E}

```
