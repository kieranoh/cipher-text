#include <stdio.h>
#include <string.h>
#include <errno.h>
#define key_len 3
#define MAX_LEN 9999
#define plaintext_file "C:\\Users\\PC\\Desktop\\TT_TT_TT\\CS\\vigenere cipher\\vigenere_cipher\\variant_vigenere_cipher\\txt_file\\plain.txt"
#define probatext_file "C:\\Users\\PC\\Desktop\\TT_TT_TT\\CS\\vigenere cipher\\vigenere_cipher\\variant_vigenere_cipher\\txt_file\\proba.txt"

void read_txt(char file_name[],char plain_text[],int *len);
void cal_probability(char input[],double proba[],int *len);
void write_txt(char file_name[],double proba[]);



int main()
{
    char plain_text[MAX_LEN];
    int len=0;


    read_txt(plaintext_file,plain_text,&len);
    double proba[256]={0.0};

    cal_probability(plain_text,proba,&len);
    write_txt(probatext_file,proba);



    return 0;
}


void read_txt(char file_name[],char text[],int *len)
{
    FILE* fp = NULL;

    printf("open the file %s\n",file_name);
    fp = fopen(file_name,"r");
    if (fp == NULL) {
        printf("Failed to read file\n"); // print error
    }
    else
    {
        
        while (fgets(text + *len, MAX_LEN - *len, fp) != NULL) {
            *len += strlen(text + *len);
        }
        //printf("%s\n",text);

        fclose(fp);
    }    
}

void cal_probability(char input[],double proba[],int *len){
    int ascii[256]={0};
    for(int i=0;i<*len;i++){
        ascii[input[i]]++;
    }
    for(int i=0; i<256;i++){
        proba[i] = (double)ascii[i]/(double)(*len);
    }
}

void write_txt(char file_name[], double proba[])
{
    FILE* fp = NULL;

    printf("open the file %s\n",file_name);
    fp = fopen(file_name,"w");
    
    if (fp == NULL) {
        printf("Failed to read file\n");
    }
    else
    {
        for(int i=0; i<256;i++)
        {
            if(i%20==0&&i!=0){
                 fprintf(fp,"\n");
            }
            fprintf(fp,"%f, ",proba[i]);
            
        }
        printf("Successfully wrote to the file: %s\n", file_name);
        fclose(fp);
    }
}