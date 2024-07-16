#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 9999
#define MAX_KEY_LEN 15
#define ALPHABET_SIZE 26
#define ciphertext_file "cipher.txt"
#define result_file "cipher_result.txt"

void read_txt(const char* file_name, char* text);
void change_char_up(const char* text, char* new_text);
double get_index_c(const char* ciphertext);
int get_key_length(char ciphertext [],int text_len);
char freq_analysis(const char* sequence, int len);
void get_key(const char* ciphertext, int text_len, int key_length, char* key);
void decryption(char input[]);
void write_txt(char file_name[], char plain_text[],char keys[],char cipher_text[]);

double english_frequencies[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};

int main() {
    char ciphertext[MAX_LEN];

    read_txt(ciphertext_file, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decryption(ciphertext);

    return 0;
}

void read_txt(const char* file_name, char* text) 
{
    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Failed to read file: %s\n", strerror(errno));
        exit(1);
    }

    size_t len = 0;
    while (fgets(text + len, MAX_LEN - len, fp) != NULL) {
        len += strlen(text + len);
    }
    fclose(fp);
}

void change_char_up(const char* text, char* new_text) 
{
    int len = strlen(text);
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            new_text[k++] = toupper(text[i]);
        }
    }
    new_text[k] = '\0';
}

double get_index_c(const char* ciphertext) 
{
    int len = strlen(ciphertext);
    double N = (double)len;
    double frequency_sum = 0.0;

    for (char letter = 'A'; letter <= 'Z'; letter++) {
        int count = 0;
        for (int i = 0; i < len; i++) {
            if (ciphertext[i] == letter) {
                count++;
            }
        }
        frequency_sum += count * (count - 1);
    }

    double ic = frequency_sum / (N * (N - 1));
    return ic;
}

int get_key_length(char text[],int text_len) 
{
    double ic_table[MAX_KEY_LEN] = {0.0};
    char sequence[MAX_LEN] ={0};
    

    for (int guess_len = 1; guess_len <= MAX_KEY_LEN; guess_len++) {
        double ic_sum = 0.0;

        for (int i = 0; i < guess_len; i++) {
            int k = 0;
            for (int j = i; j < text_len; j += guess_len) {
                sequence[k++] = text[j];
                
            }

            sequence[k] = '\0';

            ic_sum += get_index_c(sequence);
        }

        ic_table[guess_len - 1] = ic_sum / guess_len;
    }

    int best_guess = 1;
    double maxIC = ic_table[0];
    for (int i = 1; i < MAX_KEY_LEN; i++) {
        if (ic_table[i] > maxIC) {
            maxIC = ic_table[i];
            best_guess = i + 1;
        }
    }
    return best_guess;
}

char freq_analysis(const char* sequence, int len) 
{
    double all_chi_squareds[ALPHABET_SIZE] = {0};

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double chi_squared_sum = 0.0;
        double v[ALPHABET_SIZE] = {0};

        for (int j = 0; j < len; j++) {
            char shifted_char = (sequence[j] - 'a' - i + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
            v[shifted_char - 'a']++;
        }

        for (int j = 0; j < ALPHABET_SIZE; j++) {
            v[j] /= (double)len;
        }

        for (int j = 0; j < ALPHABET_SIZE; j++) {
            chi_squared_sum += pow(v[j] - english_frequencies[j], 2) / english_frequencies[j];
        }

        all_chi_squareds[i] = chi_squared_sum;
    }

    int shift = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (all_chi_squareds[i] < all_chi_squareds[shift]) {
            shift = i;
        }
    }

    return 'A' + shift;
}

void get_key(const char* ciphertext, int text_len, int key_length, char* key) 
{
    for (int i = 0; i < key_length; i++) {
        char sequence[text_len / key_length + 1];
        int k = 0;

        for (int j = i; j < text_len; j += key_length) {
            sequence[k++] = tolower(ciphertext[j]);
        }
        sequence[k] = '\0';

        key[i] = freq_analysis(sequence, k);
    }
    key[key_length] = '\0';
}

void write_txt(char file_name[], char plain_text[],char keys[],char cipher_text[])
{
    FILE* fp = NULL;

    printf("open the file %s\n",file_name);
    fp = fopen(file_name,"w");
    if (fp == NULL) {
        printf("Failed to read file: %s\n", strerror(errno)); // 오류 원인 출력
    }
    else
    {
        fputs("cipher text is : \n",fp);
        fputs(cipher_text,fp);
        fputs("\n",fp);

        fputs("key is : \n",fp);
        fputs(keys,fp);
        fputs("\n",fp);

        fputs("plain text is : \n",fp);
        fputs(plain_text,fp);
        fputs("\n",fp);

        printf("Successfully wrote to the file: %s\n", file_name);
        fclose(fp);
    }
}

void decryption(char input[])
{

    int plain,key,cipher,key_idx=0,key_len;
    char keys[MAX_KEY_LEN];
    char temp_text[MAX_LEN];
    char test [MAX_LEN];

    for(int i=0;i<strlen(input);i++)
    {
        test[i] = input[i];
    }

    change_char_up(input, temp_text);
    printf("After change: %s\n", temp_text);


    key_len = get_key_length(temp_text,strlen(temp_text));
    printf("Key length is %d\n", key_len);

    get_key(temp_text,strlen(temp_text),key_len,keys);
    printf("Key is %s\n", keys);


    for(int i=0;i<strlen(test);i++)
    {
        if(test[i]==' ')
        {
            continue;
        }
        if(test[i]=='\n')
        {
            continue;
        }
        if(test[i]>='0'&&test[i]<='9')
        {
            continue;
        }
        if(test[i]=='.'||test[i]==',')
        {
            continue;
        }
        if(test[i]>='a')
        {
            cipher = test[i]-'a';
            key = keys[key_idx%key_len]-'A';
            key_idx++;
            plain = (cipher - key+26)%26;
            test[i] = plain + 'a';
        }
        else
        {
            cipher = test[i]-'A';
            key = keys[key_idx%key_len]-'A';
            key_idx++;
            plain = (cipher - key+26)%26;
            test[i] = plain + 'A';
        }
        
        
    }
    write_txt(result_file,test,keys,input);
    printf("Plaintext: %s\n",test);
    
}

