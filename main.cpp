#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include "bmplib.cpp"

using namespace std;

unsigned char img[SIZE][SIZE][RGB];

void readImage();
void writeImage();


void invertFilter();        // 2


int main() {
    char userInput;
    printf("Welcome Habibi!\n");
    readImage();
    while (true) {
        printf("Please Select a filter:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n4 - Flip Image\n5 - Rotate Image\n");
        printf("6 - Darken and Lighten Image\n7 - Detect Image Edges\n8 - Enlarge Image\n9 - Shrink Image\na - Mirror Image\nb - Shuffle Image\nc - Blur Image\ns - Save changes\n0 - To end\n");

        cin >> userInput;
        switch (userInput) {
            case '2':
                invertFilter();
                printf("Image inverted.\n");
                break;
            case 's':
                writeImage();
                printf("Save completed.\n");
                break;
            case '0':
                printf("Good Bye!");
                return 0;
            default: printf("Invalid Input! Try Again.\n");
        }
    }
}



void readImage() {
    char imageName[100];
    printf("Please enter the name of the image to process: ");
    cin >> imageName;
    strcat(imageName, ".bmp");
    readRGBBMP(imageName, img);
}

void writeImage() {
    char imageName[100];
    printf("Please enter the name of the new image: ");
    cin >> imageName;
    strcat(imageName, ".bmp");
    writeRGBBMP(imageName, img);
}



void invertFilter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                img[i][j][k] = 255 - img[i][j][k];
            }
        }
    }
}