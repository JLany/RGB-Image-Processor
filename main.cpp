#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include "bmplib.cpp"

using namespace std;

unsigned char img[SIZE][SIZE][RGB];

void readImage();
void writeImage();


void invertFilter();        // 2
void rotateFilter();        // 5
void enlargeFilter();       // 8




void rotate90();
void extractQuarter(unsigned char ** &, char);


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
            case '5':
                rotateFilter();
                break;
            case '8':
                enlargeFilter();
                printf("Image enlarged.\n");
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


void rotateFilter() {
    int angle;
    printf("Rotate (90), (180), (270) or (360) degrees?\n");
    if (angle == 360 || angle == 270 || angle == 180 || angle == 90) {
        for (int i = 0; i < angle / 90; i++) {
            rotate90();
        }
    }
    else {
        cout << "Unrecognized angle! Please try again\n";
        return rotateFilter();
    }
}


void rotate90() {
    unsigned char tempImg[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                tempImg[i][j][k] = img[i][j][k];
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                img[j][i][k] = tempImg[i][j][k];
            }
        }
    }
}


void enlargeFilter() {
    char quarter;
    unsigned char **pQuarter;
    int quarterSize = SIZE * SIZE / 4;
    pQuarter = new unsigned char * [quarterSize];
    for (int i = 0; i < quarterSize; i++) {
        pQuarter[i] = new unsigned char[RGB];
    }
    printf("Which quarter to enlarge 1, 2, 3 or 4?\n");
    cin >> quarter;
    extractQuarter(pQuarter, quarter);
    int s = 0;
    for (int i = 0; i < SIZE; i += 2) {
        for (int j = 0; j < SIZE; j += 2) {
            for (int k = 0; k < RGB; k++) {
                img[i][j][k] = pQuarter[s][k];
                img[i + 1][j][k] = pQuarter[s][k];
                img[i][j + 1][k] = pQuarter[s][k];
                img[i + 1][j + 1][k] = pQuarter[s][k];
            }
            s++;
        }
    }
}


void extractQuarter(unsigned char ** &ptr, char quarter) {
    int startRow = 0, endRow = SIZE / 2, startCol = 0, endCol = SIZE / 2;
    switch (quarter) {
        case '1':
            break;
        case '2':
            startCol = SIZE / 2;
            endCol = SIZE;
            break;
        case '3':
            startRow = SIZE / 2;
            endRow = SIZE;
            break;
        case '4':
            startRow = SIZE / 2;
            endRow = SIZE;
            startCol = SIZE / 2;
            endCol = SIZE;
            break;
        default: printf("Unrecognized Quarter!");
    }
    int s = 0;
    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            for (int k = 0; k < RGB; k++) {
                ptr[s][k] = img[i][j][k];
            }
            s++;
        }
    }
}