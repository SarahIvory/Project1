#include <stdio.h>
#include <string.h>

int main() {
char string[100];
int c = 0, count[26] = {0}, x;

FILE * file_pointer;

file_pointer = fopen("input.txt", "r");
if (!file_pointer) {
    printf("Error opening file!\n");
    return -1;
}
    
printf("File Opened Successfully\n");

int j = 0;
while (feof(file_pointer) == 0 && j < 100) {
    fscanf(file_pointer, "%c", &string[j]);
    j++;
}
string[j] = '\0';
printf("\n\n %s\n", string);


while (string[c] != '\0'){
    if (string[c] >= 'A' && string[c] <= 'Z'){
        x = string[c] - 'A';
        count[x]++;
    }
    c++;
}

for(c=0; c<26; c++){
    printf("%c occurs %d times in the text \n", c + 'A', count[c]);
}

fclose(file_pointer);
  return 0;
}

//#include <stdio.h> 

//int main() {
//    printf("Hello World");
//    return 0;
//}
