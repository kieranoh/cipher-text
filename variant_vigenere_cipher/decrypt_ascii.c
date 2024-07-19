#include <stdio.h>
#include <string.h>
#include <errno.h>

#define key_len 3
#define MAX_LEN 999
#define plaintext_file "plain_after_decrypt.txt"
#define ciphertext_file "cipher_ascii.txt"

void read_txt(char file_name[], unsigned char text[], int *len);
void decryption(unsigned char input[], char keys[], unsigned char output[], int len);
void write_txt(char file_name[], unsigned char cipher_text[], int len);

int main()
{
    unsigned char plain_text[MAX_LEN];
    unsigned char cipher_text[MAX_LEN];
    char key[key_len] = { 0x6B , 0x65 , 0x79 };
    int cipher_len = 0;

    read_txt(ciphertext_file, cipher_text, &cipher_len);
    printf("Cipher text length: %d\n", cipher_len);

    decryption(cipher_text, key, plain_text, cipher_len);
    write_txt(plaintext_file, plain_text, cipher_len);

    return 0;
}

void read_txt(char file_name[], unsigned char text[], int *len)
{
    FILE* fp = NULL;
    char line[256];
    int value;

    printf("open the file %s\n", file_name);
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Failed to read file\n");
    } else {
        *len = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            char *ptr = strtok(line, " \t\n");
            while (ptr != NULL) {
                if (sscanf(ptr, "0x%x", &value) == 1) {
                    if (*len < MAX_LEN) {
                        text[*len] = (unsigned char)value;
                        (*len)++;
                    }
                }
                ptr = strtok(NULL, " \t\n");
            }
        }
        fclose(fp);
    }
}

void decryption(unsigned char input[], char keys[], unsigned char output[], int len)
{
    int i;

    printf("key : %c %c %c\n", keys[0], keys[1], keys[2]);

    for (i = 0; i < len; i++) {
        output[i] = input[i] ^ keys[i % key_len];
    }
    output[len] = '\0'; 
}

void write_txt(char file_name[], unsigned char cipher_text[], int len)
{
    FILE* fp = NULL;

    printf("open the file %s\n", file_name);
    fp = fopen(file_name, "w");
    printf("len is %d\n", len);
    if (fp == NULL) {
        printf("Failed to read file\n");
    } else {
        for (int i = 0; i < len; i++) {
            fprintf(fp, "%c", cipher_text[i]);
        }
        printf("Successfully wrote to the file: %s\n", file_name);
        fclose(fp);
    }
}
