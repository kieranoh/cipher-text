#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#define MAX_LEN 999999
#define plaintext_file "C:\\Users\\PC\\Desktop\\CS\\vigenere cipher\\vigenere_cipher\\plain_after_decrypt.txt"
#define key_file "C:\\Users\\PC\\Desktop\\CS\\vigenere cipher\\vigenere_cipher\\key_for_decrypt.txt"
#define ciphertext_file "C:\\Users\\PC\\Desktop\\CS\\vigenere cipher\\vigenere_cipher\\cipher.txt"

void read_txt(char file_name[],char plain_text[]);

void change_key_up(char key[],int key_len);

void decryption(char input[],char keys[],int key_len);

void write_txt(char file_name[],char cipher_text[]);

int main()
{
    char cipher[MAX_LEN];
    char key[MAX_LEN];
    int key_len;

    read_txt(ciphertext_file,cipher);
    read_txt(key_file,key);

    key_len = strlen(key);

    decryption(cipher,key,key_len);

    printf("plain text %s\n",cipher);

    write_txt(plaintext_file, cipher);

    return 0;
}

void write_txt(char file_name[], char cipher_text[])
{
    FILE* fp = NULL;

    printf("open the file %s\n",file_name);
    fp = fopen(file_name,"w");
    if (fp == NULL) {
        printf("Failed to read file: %s\n", strerror(errno)); // 오류 원인 출력
    }
    else
    {
        fputs(cipher_text,fp);
        printf("Successfully wrote to the file: %s\n", file_name);
        fclose(fp);
    }
}

void read_txt(char file_name[],char text[])
{
    FILE* fp = NULL;

    printf("open the file %s\n",file_name);
    fp = fopen(file_name,"r");
    if (fp == NULL) {
        printf("Failed to read file: %s\n", strerror(errno)); // print error
    }
    else
    {
        size_t len = 0;
        while (fgets(text + len, MAX_LEN - len, fp) != NULL) {
            len += strlen(text + len);
        }
        printf("%s\n",text);

        fclose(fp);
    }

    
}

void change_key_up(char key[],int key_len)
{
    for(int i=0;i<key_len;i++)
    {
        if(key[i]>='a')
        {
            key[i] = key[i] -'a' + 'A';
        }
    }
}

void decryption(char input[],char keys[],int key_len)
{
    int plain,key,cipher,key_idx=0;
    change_key_up(keys,key_len);

    printf("cipher text : %s\n",input);
    printf("key : %s\n",keys);

    for(int i=0;i<strlen(input);i++)
    {
        if(input[i]==' ')
        {
            continue;
        }
        if(input[i]=='\n')
        {
            continue;
        }
        if(input[i]>='0'&&input[i]<='9')
        {
            continue;
        }
        if(input[i]=='.'||input[i]==',')
        {
            continue;
        }
        if(input[i]>='a')
        {
            cipher = input[i]-'a';
            key = keys[key_idx%key_len]-'A';
            key_idx++;
            plain = (cipher - key+26)%26;
            input[i] = plain + 'a';
        }
        else
        {
            cipher = input[i]-'A';
            key = keys[key_idx%key_len]-'A';
            key_idx++;
            plain = (cipher - key+26)%26;
            input[i] = plain + 'A';
        }
        //printf("cipher %d, key %d plain %d ",cipher,key,plain);
        //printf("cipher %c, key %c plain %c\n",cipher+'A',key+'A',plain+'A');
        
        

    }
}