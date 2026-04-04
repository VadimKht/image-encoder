#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include<stdio.h>
#include<math.h>
#include "file-utils.h"

char map[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};

char* decode(char* filename)
{
    int x,y,n;
    unsigned char* data = stbi_load(filename, &x,&y,&n,3);
    unsigned int size = x*y*3;
    char* output = malloc(size);
    for(int i = 0; i < y; i++)
    {
        for(int k = 0; k < x; k++){  
            const int index = k*3 + i*y*3;
            const int colordistance = floor(255.0/27.0);
            for(int j = 0; j < 3; j++){
                int reschnum = data[index+j] / colordistance;
                if(reschnum > 27) { output[index+j] = ' '; continue;};
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
    int size = charcount/3;

    // trying to make a cubic pic
    int dimensions = ceil(sqrt(size));
    int pixelsize = (dimensions*dimensions*3);
    char pixels[pixelsize];
    memset(pixels, 255, pixelsize);
    
    for(int i = 0; i < charcount; i++){
        if(data[i] == ' ') { pixels[i] = 255; continue;}
        pixels[i] = ((data[i]-'a') *9)+4;
    }
    stbi_write_png(filename, dimensions,dimensions,3,pixels,dimensions*3);
}

int main(int argc, char *argv[]){
    char* choice = argv[1];
    if(choice == nullptr || !strcmp("--help", choice)){
        printf("Either encode into text by using 'imagetool e textfile.txt' or decode by 'imagetool d myimage.png'\nThe text input MUST NOT have numbers or capital letters, only a-z and spacebars.");
        return 0;
    }

    if(strcmp("e", choice) && strcmp("d", choice)){
        printf("Incorrect choice. Second argument must be [d]ecode or [e]ncode\n");
        return 1;
    }

    char* secondchoice = argv[2];
    if(secondchoice == nullptr) 
    {   
        printf("Inlucde a file name please\n");
        return 1;
    }
    //If encoding
    if(!strcmp("e",choice)){
        encode(ReadFile(secondchoice), "output.png");
    } 
    // If decoding
    else if(!strcmp("d", choice)){
        printf("%s\n", decode(secondchoice));
    }
    return 0;
}
