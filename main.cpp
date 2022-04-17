#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include "bmplib.h"

using namespace std;

unsigned char img[SIZE][SIZE][RGB];

void readImage();
void writeImage();


void invertFilter();        // 2


int main() {
    char userInput;
   printf("Welcome Habibi!\n");
    // read image
    while (true) {
        printf("Please Select a filter:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n4 - Flip Image\n5 - Rotate Image\n");
        printf("6 - Darken and Lighten Image\n7 - Detect Image Edges\n8 - Enlarge Image\n9 - Shrink Image\na - Mirror Image\nb - Shuffle Image\nc - Blur Image\ns - Save changes\n0 - To end\n");

        cin >> userInput;
        switch (userInput) {
            case '2': invertFilter();
                break;
            case '0': printf("Good Bye!");
                return 0;
            default: printf("Invalid Input! Try Again.");
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

}