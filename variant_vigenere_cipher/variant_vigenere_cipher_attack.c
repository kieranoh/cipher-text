#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 9999
#define MAX_KEY_LEN 15
#define MIN_KEY_LEN 2
#define ASCII_RANGE 255
#define ASCII_MIN 0
#define ASCII_MAX 255

#define ciphertext_file "cipher.txt"
#define result_file "decrypt_result.txt"
#define key_file "key.txt"

double ascii_frequencies[ASCII_RANGE+1] = {
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000939, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.169563, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.011743, 0.000000, 0.010333, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000470, 0.001409, 0.000470, 0.000470, 0.000470, 0.000470, 0.001409, 0.000939, 0.003288, 0.000000, 0.000470, 0.000000, 0.000939, 0.000000, 0.000000, 
0.000470, 0.000000, 0.001409, 0.000000, 0.003288, 0.000000, 0.000000, 0.000470, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.056364, 0.007046, 0.024894, 
0.025364, 0.121653, 0.023485, 0.018318, 0.046031, 0.046031, 0.000000, 0.003288, 0.042743, 0.018788, 0.051198, 0.072804, 0.027243, 0.001409, 0.040395, 0.047440, 0.068107, 0.013621, 0.008924, 0.014091, 
0.000000, 0.011743, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 
0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000
};


void read_txt(char file_name[], unsigned char text[], int *len);
void write_plain_txt(char file_name[], unsigned char cipher_text[], int len);
void write_key_txt(char file_name[],char keys[],int len);
void decryption(char input[],int len,char output[]);

int get_key_length(unsigned char  ciphertext[],int text_len);
double calculate_ic(const unsigned char *text, int len);
unsigned char find_key_for_position(const char* ciphertext, int len, int step, int offset);
void get_xor_key(const char* ciphertext, int text_len, int key_length, char* key);
void xor_with_key(char input[],char output[],char key[],int text_len, int key_len);
int remove_key_redundancy(char *key, int key_length);


int main(){

    unsigned char cipher_text[MAX_LEN];
    unsigned char plain_text[MAX_LEN];
    int cipher_len = 0;
    read_txt(ciphertext_file,cipher_text,&cipher_len);
    decryption(cipher_text,cipher_len,plain_text);

    return 0;
}

void read_txt(char file_name[], unsigned char text[], int *len) {
    FILE* fp = NULL;
    int value;

    printf("Opening the file %s\n", file_name);
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Failed to read file\n");
        return;
    }

    *len = 0; 
    while (*len < MAX_LEN && fscanf(fp, " 0x%2x", &value) == 1) {
        text[*len] = (unsigned char)value;
        (*len)++;
    }

    if (*len == MAX_LEN) {
        printf("Warning: Maximum buffer size reached. Some data may not be read.\n");
    }

    fclose(fp);
}

void decryption(char input[],int len,char output[]){
    
    int plain,key,cipher,key_idx=0,key_len;
    char keys[MAX_KEY_LEN];
    
    key_len = get_key_length(input,len);
    
    get_xor_key(input,len,key_len,keys);
    key_len = remove_key_redundancy(keys, key_len);

    printf("key length is %d!\n",key_len);
    printf("key is ");
    for (int i=0; i<key_len;i++){
         printf("0x%x  ",keys[i]);
     }
     printf("\n");

    xor_with_key(input,output,keys,len,key_len);


    write_plain_txt(result_file,output,len);
    write_key_txt(key_file,  keys, key_len);

}

double calculate_ic(const unsigned char *text, int len) {

    int frequency[256] = {0};
    for (int i = 0; i < len; i++) {
        frequency[text[i]]++;
    }

    double ic = 0.0;
    for (int i = 0; i < 256; i++) {
        ic += frequency[i] * (frequency[i] - 1);
    }
    return ic / (len * (len - 1));
}

int get_key_length(unsigned char ciphertext[], int text_len) {
    double max_ic = 0.0;
    int best_key_len = 1;

    for (int key_len = 1; key_len < MAX_KEY_LEN; key_len++) {
        double total_ic = 0.0;
        int group_count = 0;

        for (int i = 0; i < key_len; i++) {
            unsigned char group[MAX_LEN] = {0};
            int group_len = 0;

            for (int j = i; j < text_len; j += key_len) {
                group[group_len++] = ciphertext[j];
            }

            total_ic += calculate_ic(group, group_len);
            if(total_ic > max_ic){
                max_ic = total_ic;
                best_key_len = key_len;
            }
        }
    }

    return best_key_len;
}

unsigned char find_key_for_position(const char* ciphertext, int len, int step, int offset) {
    unsigned char best_key = 0;
    double best_ic = 0; 
    char* decrypted = (char*)malloc(len + 1);
    int input[256] = {0}; 
    int flag = 0;

    for (int key = 0; key <= 0xFF; key++) {
        int chunk_size = 0;

        for (int i = offset; i < len; i += step) {
            decrypted[chunk_size++] = ciphertext[i] ^ key;
        }
        
        int char_counts[256] = {0};

        for (int i = 0; i < chunk_size; i++) {
            unsigned char c = decrypted[i];
            char_counts[c]++;
        }
        
        double ic = 0.0;
        for (int i = 0; i < 256; i++) {
            double temp = (double)char_counts[i]/(double)chunk_size;
            temp = temp*ascii_frequencies[i];
            ic+=temp;
        }

        if (ic > best_ic) {
            best_ic = ic;
            best_key = key;
        }
    }

    free(decrypted);

    return best_key;
}

void get_xor_key(const char* ciphertext, int text_len, int key_length, char* key) {
    for (int i = 0; i < key_length; i++) {
        key[i] = find_key_for_position(ciphertext, text_len, key_length, i);
    }
    key[key_length] = '\0';
}

void xor_with_key(char input[],char output[],char key[],int text_len, int key_len){

    for(int i=0;i<text_len;i++){
        output[i] = input[i] ^ key[i%key_len];
        
    }
}

int remove_key_redundancy(char *key, int key_length) {
    for (int i = 1; i <= key_length / 2; i++) {
        if (key_length % i == 0) {
            int is_redundant = 1;

            for (int j = 0; j < key_length; j++) {
                if (key[j] != key[j % i]) {
                    is_redundant = 0;
                    break;
                }
            }

            if (is_redundant) {
                key[i] = '\0';  
                return i;       
            }
        }
    }
    return key_length; 
}

void write_plain_txt(char file_name[], unsigned char cipher_text[], int len){
    FILE* fp = NULL;

    printf("open the file %s\n", file_name);
    fp = fopen(file_name, "w");
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

void write_key_txt(char file_name[], char keys[], int len){
    FILE* fp = NULL;

    printf("open the file %s\n", file_name);
    fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Failed to read file\n");
    } else {
        for (int i = 0; i < len; i++) {
            fprintf(fp, "0x%x  ", keys[i]);
        }
        printf("Successfully wrote to the file: %s\n", file_name);
        fclose(fp);
    }
}