#include <stdio.h>
#include <string.h>

void sub_decrypt(char * filename); 

int main() {
    
	sub_decrypt("input.txt");
	
  return 0;
}

void sub_decrypt(char * filename){
    char string[100];
   // int i; //index for decrypt
    int c=0;
    char w;
    const char plainAlphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    char cipherAlphabet[] = {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M','\0'};
    
    //Below code is for opening a string of text (including whitespace)
    
    FILE * file_pointer;
    
    file_pointer = fopen(filename, "rw");
    if (!file_pointer) {
        printf("Error opening file!\n");
        return;
    }
        
    printf("File Opened Successfully\n");
    
    int j = 0;
    while (feof(file_pointer) == 0 && j < 100) {
        fscanf(file_pointer, "%c", &string[j]);
        j++;
    }
    string[j] = '\0';
    printf("\nYour Original Message Is: \n\n %s\n", string);
    
    //cipher function starts here - Encryption

//strlen is a function for finding length of string (this tests length of cipher key)
//the following tests if cipher alphabet key is the same length as normal alphabet
//if not, the code does not run, asks for valid key
//stops people doing stupid shit

    if(strlen(plainAlphabet) != strlen(cipherAlphabet)){
        printf("\nPlease Enter a Valid Cipher Key!!\n");
    }
            
printf("\n\nYour Decrypted Message Is:\n\n");

//for(i = 0; cipherAlphabet[i] != 0; ++i){
    //plainAlphabet[i]==cipherAlphabet[i];
   // cipherAlphabet[i]=plainAlphabet[i];
//}
            
for(c = 0; string[c] != 0; ++c){
    if(string[c]>='A' && string[c]<='Z'){
        w=plainAlphabet[string[c]-65];
       // w=w[plainAlphabet];
        printf("%c", w);
    }
    else if(string[c]<'A'){
        w=string[c];
        printf("%c", w);
    }
}

    fclose(file_pointer);

    return;
    }
