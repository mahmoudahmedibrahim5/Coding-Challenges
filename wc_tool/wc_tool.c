#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Given the file name, this function find the count of bytes in this file */
int getBytesCount(char* fileName);

/* Given the file name, this function find the count of characters in this file */
int getCharactersCount(char* fileName);

/* Given the file name, this function find the count of words in this file */
int getWordsCount(char* fileName);

/* Given the file name, this function find the count of lines in this file */
int getLinesCount(char* fileName);

/* Get and print count of (Bytes - Characters - words - lines) */
int getAll(char* fileName);

int main(int argc, char** argv)
{
    // Check if there is an argument
    if(argc == 3)
    {
        /* -c print the byte counts */
        if(argv[1][1] == 'c')
        {
            // Get the bytes count
            int bytesCount = getBytesCount(argv[2]);
            
            if(bytesCount == -1)
                return -1;

            printf("%d %s\n", bytesCount, argv[2]);
        }

        /* -l print the lines count */
        else if(argv[1][1] == 'l')
        {
            // Get the lines count
            int linesCount = getLinesCount(argv[2]);
            
            if(linesCount == -1)
                return -1;

            printf("%d %s\n", linesCount, argv[2]);
        }

        /* -w print the words count */
        else if(argv[1][1] == 'w')
        {
            // Get the words count
            int wordsCount = getWordsCount(argv[2]);
            
            if(wordsCount == -1)
                return -1;

            printf("%d %s\n", wordsCount, argv[2]);
        }
        
        /* -m print the characters count */
        else if(argv[1][1] == 'm')
        {
            // Get the characters count
            int charactersCount = getCharactersCount(argv[2]);
            
            if(charactersCount == -1)
                return -1;

            printf("%d %s\n", charactersCount, argv[2]);
        }

        else
            return -1;
    }

    else if(argc == 2)
    {
        getAll(argv[1]);
    }

    else
        return -1;

    return 0;
}

int getBytesCount(char* fileName)
{
    FILE* fptr;

    // open the file in binary mode
    fptr = fopen(fileName, "rb");
    if(fptr == NULL){
        printf("error opening the file\n");
        return -1;
    }
    
    // Move the fptr to the end of the line
    if(fseek(fptr, 0, SEEK_END) != 0){
        printf("error seeking in the file\n");
        return -1;
    }

    // Getting the size of the file
    int bytesCount = ftell(fptr);
    if(bytesCount == -1){
        printf("error getting the file size\n");
        return -1;
    }

    // close the file
    fclose(fptr);

    return bytesCount;
}

int getCharactersCount(char* fileName)
{
    FILE* fptr;

    // open the file in read mode
    fptr = fopen(fileName, "r");
    if(fptr == NULL){
        printf("error opening the file\n");
        return -1;
    }

    char buffer[255];
    int charactersCount = 0;

    while(fgets(buffer, sizeof(buffer), fptr))
        charactersCount += strlen(buffer);

    // close the file
    fclose(fptr);
    
    return charactersCount;
}

int getWordsCount(char* fileName)
{
    FILE* fptr;
    
    // open the file in read mode
    fptr = fopen(fileName, "r");
    if(fptr == NULL){
        printf("error opening the file\n");
        return -1;
    }

    char buffer[255];
    int wordsCount = 0;

    while(fgets(buffer, sizeof(buffer), fptr)){
        int i = 0;
        while(buffer[i] != '\n'){
            if(buffer[i++] == ' ')
                wordsCount++;
        }
        if(buffer[0] != '\n' && buffer[0] != ' ')
            wordsCount++;
    }

    // close the file
    fclose(fptr);

    return wordsCount;
}

int getLinesCount(char* fileName)
{
    FILE* fptr;

    // open the file in read mode
    fptr = fopen(fileName, "r");
    if(fptr == NULL){
        printf("error opening the file\n");
        return -1;
    }

    char buffer[255];
    int linesCount = 0;

    while(fgets(buffer, sizeof(buffer), fptr))
        linesCount++;
        
    // close the file
    fclose(fptr);

    return linesCount;
}

int getAll(char* fileName)
{
    FILE* fptr;

    int bytesCount = getBytesCount(fileName);

    if(bytesCount == -1)
        return -1;

    // open the file in read mode
    fptr = fopen(fileName, "r");
    if(fptr == NULL){
        printf("error opening the file\n");
        return -1;
    }

    char buffer[255];
    int linesCount = 0;
    int charactersCount = 0;
    int wordsCount = 0;

    // For each line in the file
    while(fgets(buffer, sizeof(buffer), fptr)){
        linesCount++;   
        charactersCount += strlen(buffer);

        int i = 0;
        while(buffer[i] != '\n' && buffer[i] != 0){
            if(buffer[i] == ' ' && i > 1 && buffer[i - 1] != ' ')
                wordsCount++;
            i++;
        }
        if(i > 0 && buffer[i - 1] != ' ')
            wordsCount++;
    }
    
    printf("%d %d %d %s\n", linesCount, wordsCount, bytesCount, fileName);

    // close the file
    fclose(fptr);

    return linesCount;
}
