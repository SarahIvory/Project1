#ifndef VARIABLE
#define VARIABLE

//ROTATION CIPHER ENCRYPTION FUNCTION

void rotation_encrypt(char * filename, int key) { //recieves text and key
    char string[1000], character; //string is the input text, character is for specific letters
    //1000 should be enoungh elements to cover most text lengths
    int index; //index for counting in for loop later
    
    //Below code is for opening a string of text (including whitespace)
    
    FILE * file_pointer;
    
    file_pointer = fopen(filename, "rw"); //fopen takes input text and "rw" means read/write mode
    if (!file_pointer) { //to check if file is opened successfully
        printf("Error opening file!\n");
        return;
    }
    
    printf("\nPlease enter your text into (input.txt):\n");
    printf("\nFile Opened Successfully\n");
    
    //Above opens the file, below makes sure it includes whitespace as each character is used
    
    int j = 0; //used as an index
    while (feof(file_pointer) == 0 && j < 100) {
        fscanf(file_pointer, "%c", &string[j]); //saves text as string which can be easily used later
        j++;
    }
    string[j] = '\0';
    printf("\nYour Original Message Is: \n\n %s\n", string);
    
    //cipher function starts here - Encryption
    
    for(index = 0; string[index] != '\0'; ++index){ //for loop as index starts at 0 and adds one each iteration 
    //when string is not NULL
        character = string[index]; //char character becomes each element in string
        
        if(character >= 'A' && character <= 'Z'){ //if the elements are between A and Z
            character = character + key; //adds rotation cipher key (works with ASCII values)
            
            if(character > 'Z'){ //incase the character is outside the alphabet
                character = character - 'Z' + 'A' -1; //puts character back in alphabet
                //character above Z subtracts Z (ASCII 97) and adds A (ASCII 65) to loop back into the normal alphabet
                //for "overflow" letters i.e. if key was 5 and this applied to y
                //instead of going outside of alphabet, y goes to d (loop starts again)
                //-1 avoids any offset by 1 errors
            }
            
            string[index] = character; //applies new character string to text
        }
    } 
    
    printf("\nYour Encrypted Message Is: \n\n %s", string); //prints encrypted text
    
    //cipher function ends here
    
    fclose(file_pointer); //closes file
    return;
}

//ROTATION DECRYPTION CIPHER WITH KEY

void rotation_decrypt(char * filename, int key) { //recieves text and key
    char string[1000], character; //string is the input text, character is for specific letters
    //1000 should be enoungh elements to cover most text lengths
    int index; //index for counting in for loop later
    
    //Below code is for opening a string of text (including whitespace)
    //This is exactly the same code used in all my functions
    //Please don't make me repeat all the same comments...
    
    FILE * file_pointer;
    
    file_pointer = fopen(filename, "rw");
    if (!file_pointer) {
        printf("Error opening file!\n");
        return;
    }
    printf("\n\nPlease enter your text into (input.txt):\n");   
    printf("File Opened Successfully\n");
    
    int j = 0;
    while (feof(file_pointer) == 0 && j < 100) {
        fscanf(file_pointer, "%c", &string[j]);
        j++;
    }
    string[j] = '\0';
    printf("\nYour Original Message Is: \n\n %s\n", string);
    
    //cipher function starts here - Decryption
    //This is almost the "same but opposite" to the Encryption Rotation
    
    for(index = 0; string[index] != '\0'; ++index){//for loop as index starts at 0 and adds one each iteration 
    //when string is not NULL
        character = string[index]; //char character becomes each element in string
        //same as above so far
        
        if(character >= 'A' && character <= 'Z'){ //if the elements are between A and Z
            character = character - key; //minus key instead of plus as the encryption is being reversed
            
            if(character < 'A'){ //if character is less than A this time instead of Z
                character = character + 'Z' - 'A' + 1; //Does the opposite to encryption
                //character below A adds Z (ASCII 97) and subtracts A (ASCII 65) to loop back into the normal alphabet
                //for "overflow" letters i.e. if subtracting the key made it a character less than the alphabet
                //instead of going outside of alphabet, the loop starts again
                //+1 avoids any offset by 1 errors
            }
            
            string[index] = character;//applies new character string to text
        }
    }
    
    printf("\nYour Decrypted Message Is: \n\n%s", string); //prints decrypted message
    
    //cipher function ends here
    
    fclose(file_pointer); //closes file
    return;
}

//COUNTING FUNCTION FOR FINDING LETTER FREQUENCY
//USED FOR FINDING ROTATION KEY

void letter_count(char * filename) { //recieves input text
    char string[1000]; //string is the input text
    //1000 should be enoungh elements to cover most text lengths
    int c = 0, x;     //c is short for character, x is just an extra variable needed for counting
    int count[26] = {0}; //Like an index, used for counting through for loop
    
    //OPENS FILE
    
    FILE * file_pointer;
    
    file_pointer = fopen(filename, "rw");
    if (!file_pointer) {
        printf("Error opening file!\n");
        return;
    }
    printf("\nPlease enter your text into (input.txt):\n");    
    printf("\n\nFile Opened Successfully\n");
    
    int j = 0;
    while (feof(file_pointer) == 0 && j < 100) {
        fscanf(file_pointer, "%c", &string[j]);
        j++;
    }
    string[j] = '\0';
    printf("\n\n %s\n", string);
    
    //counting function starts here
    
    while (string[c] != '\0'){       //while string is not NULL, c = characters
        if (string[c] >= 'A' && string[c] <= 'Z'){ //while string is between A and Z
            x = string[c] - 'A'; //string[c]-65 (ASCII A is 65) makes index of 0 to 25
            count[x]++; //an index of 0 to 25 becomes the index of this array
        }
        c++; //continues loop
    }
    
    for(c=0; c<26; c++){ //for each character
        printf("%c occurs %d times in the text \n", c + 'A', count[c]);
        //reads as e.g. A occurs 9 times in the text
        //c+A is the same as c+65 to return the character back to capital alphabet form
        //count[c] reccords how many times this character occured
    }
    
    //counting function ends here
    
    //to find key: key=e-mostfrequent, then e-secondfrequent
    
    fclose(file_pointer);
    return;
}

//KEY FINDER FUNCTION

void find_key(int letter) { //recieves the most frequent letter (as determined by counting function above)
    //to find key: key=mostfrequent-e, then secondfrequent-e, etc.
    //This works well unless in the unlikely case the text has no E at all
    //the following minuses the 3 most frquent letters in English E A and T
    //This presents the user with 3 very likely keys to try
    //This can be reattempted with the next most frquent letter in your text
    //If that still doesn't work, your text is pretty unusual tbh
    //This only works by assuming your text has the same letter frequency as most of the English language
    
        //key = most frequent - E
        
        printf("\nSome very likely keys are:\n");
        
        int key = letter - 69; //most frequent letter minus E
            if(key>0){ //makes sure key is not negative
                printf("\nKey 1: %d", key);
                }
            else if (key<0){ //negative keys make the text do wierd shit
                key = key + 26; //adds 26 to make sure the key is the same just not negative
                printf("\nKey 1: %d", key);
                }
            else{ //else if there is no different then it is plain text
                printf("\nPlain Text");
                }
        //key = most frequent - T
        key = letter - 84; //ASCII for T is 84
            if(key>0){ //process for checking sign of key is the same
                printf("\nKey 2: %d", key); 
                } //T is the next most frequent
            else if (key<0){
                key = key + 26;
                printf("\nKey 2: %d", key);
                }
            else{
                printf("\nPlain Text");
                }
        //key = most frequent - A
        key = letter - 65; //Repeated again for A (ACSII 65)
            if(key>0){
                printf("\nKey 3: %d", key);
                }
            else if (key<0){
                key = key + 26;
                printf("\nKey 3: %d\n", key);
                }
            else{
                printf("\nPlain Text");
                }
    //These extremely likely keys can then be put into the normal decryption function
    return;
}

//MENU SYSTEM FUNCTION

void menu_system(char * filename){ //recieves input
//though a file called "scanInput.txt"
//Because Che is dumb and ignores scanf
//So now I have to create a whole file pointer to read a single number...
//Thank you Che <3
    
        FILE * file_pointer; //The file pointer I was ranting about
    
    file_pointer = fopen(filename, "rw");
    if (!file_pointer) {
        //printf("Error opening file!\n"); We don't really need to print this
        return;
    }
        
    //printf("File Opened Successfully\n");
    //Doesn't have all that extra jazz cause it doesn't need to account for whitespace
    
    int opt; //option for user

    printf("Hello!! Welcome to the Cipher Program!\n\n"); //A nice greeting :)
    printf("Would you like to (1) Encrypt OR (2) Decrypt? (Please enter option number)\n");
    fscanf(file_pointer, "%d", &opt);
        if(opt==1){ //reads option 1 and gives encryption info
            printf("\nUse function: \n\n rotation_encrypt(char * filename, int key) for Rotation Ciphers\n");
            printf("\n OR \n\n sub_encrypt(char * filename) for Substitution Ciphers\n\n");
        }
        else if(opt==2){ //reads option 2 and gives decryption info
                    printf("\nIf You Have a Key, Use function: \n\n rotation_decryptKey(input, key) for Rotation Ciphers\n");
                    //printf("\n OR \n\n sub_decrypt(char * filename) for Substitution Ciphers\n\n");   
                    printf("\nOtherwise, follow these steps:\n\n 1. Use function letter_count(char *filename) to find the most requent letter in your text\n");
                    printf("\n\n 2. Then use function find_key(int letter) (input your most frequent) to find your key\n");
                    printf("\n\n 3. Use rotation_decrypt(char *filename, int key) as normal with the suggested keys\n\n");
                    printf("\n 4. Note: In the unlikely case none of these keys work, try your next most frequent letter in the find_key(int letter) function\n\n");
        }
        else{ //don't try to break it you idiot
            printf("\nPlease Enter Valid Option\n\n");
        }
        
    fclose(file_pointer);
    return;
}

//SUBSTITUTION ENCRYPTION

void sub_encrypt(char * filename){ //recieves input text
//couldn't figure out a way to recieve the key so this will have to be hard coded...
    char string[1000]; //text string
    int c=0; //index
    char x; //another string to hold new string and to be printed
    char plainAlphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    char cipherAlphabet[] = {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M','\0'};
    
    //Below code is for opening a string of text (including whitespace)
    
    FILE * file_pointer;
    
    file_pointer = fopen(filename, "rw");
    if (!file_pointer) {
        printf("Error opening file!\n");
        return;
    }
    printf("\nPlease enter your text into (input.txt):\n");    
    printf("File Opened Successfully\n\n");
    
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
            
printf("\n\nYour Encrypted Message Is:\n\n");
            
for(c = 0; string[c] != 0; ++c){ //same set up as other for loops
    if(string[c]>='A' && string[c]<='Z'){ //between A and Z
        x=cipherAlphabet[string[c]-65]; //string to be printed is cipherAlphabet with text index minus 65
        printf("%c", x); //The minus 65 makes all the letters in text string an index between 0 and 25
        //the cipher reference is then applied to this new index
    }
    else if(string[c]<'A'){ //if a character is less than A i.e. outside the alphabet
        x=string[c]; //this part accounts for whitespace
        printf("%c", x);
    }
}
    fclose(file_pointer);
    return;
    }


#endif