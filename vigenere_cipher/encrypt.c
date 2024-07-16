#include <stdio.h>
#include <string.h>
#include <errno.h>
#define MAX_LEN 999999
#define plaintext_file "plain.txt"
#define key_file "key.txt"
#define ciphertext_file "cipher.txt"

void read_txt(char file_name[],char plain_text[]);

void change_key_up(char key[],int key_len);

void encryption(char input[],char keys[],int key_len);

void write_txt(char file_name[],char cipher_text[]);

int main()
{
    char plaintext[MAX_LEN];
    char key[MAX_LEN];
    int key_len;

    read_txt(plaintext_file,plaintext);
    read_txt(key_file,key);

    key_len = strlen(key);

    encryption(plaintext,key,key_len);

    printf("cipher text %s\n",plaintext);

    write_txt(ciphertext_file, plaintext);

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

void encryption(char input[],char keys[],int key_len)
{
    int plain,key,cipher,key_idx=0;
    change_key_up(keys,key_len);

    printf("plain text : %s\n",input);
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
            plain = input[i]-'a';
            key = keys[key_idx%key_len]-'A';
            key_idx++;
            cipher = (plain + key)%26;
            input[i] = cipher + 'a';
        }
        else
        {
            plain = input[i]-'A';
            key = keys[key_idx%key_len]-'A';
            key_idx++;
            cipher = (plain + key)%26;
            input[i] = cipher + 'A';
        }
        //printf("plain %d, key %d cipher %d ",plain,key,cipher);
        //printf("plain %c, key %c cipher %c\n",plain+'A',key+'A',cipher+'A');
        
        

    }
}