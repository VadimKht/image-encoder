#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

size_t GetSize(FILE *fptr){
    fseek(fptr, 0, SEEK_END);
    size_t file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    return file_size;
}

char* ReadFile(const char* fileName){
    FILE *fptr = fopen(fileName, "r");
    assert(fptr != NULL);
    size_t size = GetSize(fptr);
    char* data = malloc(size);

    int n = fread(data, 1, size - 1, fptr);
    fclose(fptr);
    data[n] = '\0';

    return data;
}


int file_utils_test()
{
    char* text = ReadFile("test.txt");
    free(text);
    return 0;
}
