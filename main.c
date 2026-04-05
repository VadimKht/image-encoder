#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utils/stb_image_write.h"
#include "utils/file-utils.h"

#include<stdio.h>
#include<math.h>

const int NUMCHANNELS = 3;
char map[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
int COLORDISTANCE;

char* decode(char* filename)
{
    int x,y,n;
    unsigned char* data = stbi_load(filename, &x,&y,&n,NUMCHANNELS);
    unsigned int size = x*y*NUMCHANNELS;
    char* output = malloc(size);
    for(int i = 0; i < y; i++)
    {
        for(int k = 0; k < x; k++){  
            const int index = k*NUMCHANNELS + i*y*NUMCHANNELS;
            for(int j = 0; j < 3; j++){
                int reschnum = data[index+j] / COLORDISTANCE;
                if(reschnum >= sizeof map) { output[index+j] = ' '; continue;};
                output[index+j] = map[reschnum];
            }
        }
    }
    output[size] = '\0';
    return output;
}

int count_characters(char* chars){
    int count = 0;
    for(int i = 0; chars[i] != '\0'; i++)
    {
        count += 1;
    }
    return count;
}

void encode(char* data, const char* filename)
{
    int charcount = count_characters(data);
    int size = charcount/NUMCHANNELS;

    // trying to make a cubic pic
    int dimensions = ceil(sqrt(size));
    int pixelsize = (dimensions*dimensions*NUMCHANNELS);
    char pixels[pixelsize];
    memset(pixels, 255, pixelsize);
    
    for(int i = 0; i < charcount; i++){
        if(data[i] == ' ') { pixels[i] = (char)255; continue;}
        // colordistance/2 for middle color may not be good in case if the map is too big
        pixels[i] = ((data[i]-'a') * COLORDISTANCE) + COLORDISTANCE/2;
    }
    stbi_write_png(filename, dimensions,dimensions,NUMCHANNELS,pixels,dimensions*NUMCHANNELS);
}

int main(int argc, char *argv[]){
    COLORDISTANCE = floor(255.0/sizeof map);
    char* choice = argv[1];
    if(choice == NULL || !strcmp("--help", choice)){
        printf("Encode text file into image by using:\n%s e mytextfile.txt\nOr you can use:\n%s e \"Your string of text to be encoded\"\n You can decode the image using:\n%s d output.png\n",argv[0], argv[0], argv[0]);
        return 0;
    }

    if(strcmp("e", choice) && strcmp("d", choice)){
        printf("Incorrect choice. Second argument must be [d]ecode or [e]ncode\n");
        return 1;
    }

    char* secondchoice = argv[2];
    if(secondchoice == NULL) 
    {   
        printf("Inlucde a file name please\n");
        return 1;
    }
    //If encoding
    if(!strcmp("e",choice)){
        if(fopen(secondchoice, "r") == NULL)
        {
            encode(secondchoice, "output.png");
        }
        else{
            encode(ReadFile(secondchoice), "output.png");
        }
    } 
    // If decoding
    else if(!strcmp("d", choice)){
        printf("%s\n", decode(secondchoice));
    }
    return 0;
}
