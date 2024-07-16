#include <stdio.h>
#include <string.h>
#include <errno.h>
#define key_len 3
#define MAX_LEN 999
#define plaintext_file "plain.txt"
#define ciphertext_file "cipher_ascii.txt"

void read_txt(char file_name[],char plain_text[]);

void encryption(char input[],char keys[],char output[]);

void write_txt(char file_name[],char cipher_text[],int len);

int main()
{
    char plain_text[MAX_LEN];
    char cipher_text[MAX_LEN];
    char key[key_len] = { 0x6B , 0x65 , 0x79 };;

    read_txt(plaintext_file,plain_text);

    encryption(plain_text,key,cipher_text);

    write_txt(ciphertext_file, cipher_text,strlen(plain_text));

    return 0;
}

void write_txt(char file_name[], char cipher_text[],int len)
{
    FILE* fp = NULL;

    printf("open the file %s\n",file_name);
    fp = fopen(file_name,"w");
    printf("len is %d\n",len);
    if (fp == NULL) {
        printf("Failed to read file\n");
    }
    else
    {
        for(int i=0; i<len;i++)
        {
            fprintf(fp,"0x%x ",cipher_text[i]);
        }
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
        printf("Failed to read file\n"); // print error
    }
    else
    {
        size_t len = 0;
        while (fgets(text + len, MAX_LEN - len, fp) != NULL) {
            len += strlen(text + len);
        }
        //printf("%s\n",text);

        fclose(fp);
    }

    
}

void encryption(char input[] ,char keys[],char output[])
{
    int plain,key,cipher,key_idx=0;
    printf("plain text : %s,len is %d\n",input,strlen(input));
    printf("key : %c %c %c\n",keys[0],keys[1],keys[2]);

    for(int i=0;i<strlen(input);i++)
    {
        output[i] = input[i] ^ keys[ i % key_len ];

    }
}