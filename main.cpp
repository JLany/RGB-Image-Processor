#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include "bmplib.cpp"
#include <cmath>

using namespace std;

unsigned char img[SIZE][SIZE][RGB];

void readImage();
void writeImage();
void bwFilter();            // 1
void invertFilter();        // 2

void flipFilter();          // 4
void rotateFilter();        // 5
void edgeFilter();          // 7
void enlargeFilter();       // 8
void mirrorFilter();        // a
void shuffleFilter();       // b




void rotate90();
void extractQuarter(unsigned char * * &, char);


int main() {
    char userInput;
    printf("Welcome Habibi!\n");
    readImage();
    while (true) {
        printf("Please Select a filter:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n4 - Flip Image\n5 - Rotate Image\n");
        printf("6 - Darken and Lighten Image\n7 - Detect Image Edges\n8 - Enlarge Image\n9 - Shrink Image\na - Mirror Image\nb - Shuffle Image\nc - Blur Image\ns - Save changes\n0 - To end\n");

        cin >> userInput;
        switch (userInput) {
            case '1':
                bwFilter();
                printf("Black and white complete\n");
                break;
            case '2':
                invertFilter();
                printf("Image inverted.\n");
                break;
            case '4':
                flipFilter();
                printf("Image flipped.\n");
                break;
            case '5':
                rotateFilter();
                printf("Image rotated.\n");
                break;
            case '7':
                edgeFilter();
                printf("Edges detected.\n");
                break;
            case '8':
                enlargeFilter();
                printf("Image enlarged.\n");
                break;
            case 'a':
                mirrorFilter();
                printf("Image mirrored.\n");
                break;
            case 'b':
                shuffleFilter();
                printf("Image shuffled.\n");
                break;
            case 's':
                writeImage();
                printf("Save completed.\n");
                sleep(1);
                return main();
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


void bwFilter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {         //loop over every color in each pixel
                if (img[i][j][RGB] > 127)           // if the value of RGB is > 127
                    img[i][j][k] = 255;             // change to white (255)
                else
                    img[i][j][k] = 0;               // else change to black (0)
            }
        }
    }
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


void flipFilter() {
    string flip;
    printf("h to flip horizontally, v to flip vertically: ");
    cin >> flip;                // get user input for flip direction.
    if (flip == "h") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                swap(img[i][j], img[i][SIZE - 1 - j]);         //flip each pixel with it's corresponding horizontal pixel
            }
        }
    } else if (flip == "v") {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(img[i][j], img[SIZE - 1 - i][j]);         //flip each pixel with it's corresponding vertical pixel 
            }
        }
    } else {
        printf("Invalid input, Please try again\n");
        return flipFilter();                                   // recursion in case of invalid input
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

void edgeFilter() {
    bwFilter();
    for (int i = 0;i < SIZE;i++) {
        for (int j = 0;j < SIZE;j++) {
            for (int k = 0; k < RGB; k++) {         //loop over each color of each pixel
                if (img[i][j][k] != img[i][j + 1][k] || img[i][j][k] != img[i + 1][j][k])   // if pixel is not the same value as the next horizontal or vetrical pixel
                    img[i][j][k] = 0;                           // make it black
                else
                    img[i][j][k] = 255;                         // make it white
            }
        }
    }
}

void enlargeFilter() {
    char quarter;
    int quarterSize = SIZE * SIZE / 4;
    unsigned char * * pQuarter;
    pQuarter = new unsigned char * [quarterSize];
    for (int i = 0; i < quarterSize; i++) {
        pQuarter[i] = new unsigned char[RGB];
    }
    printf("Which quarter to enlarge 1, 2, 3 or 4?\n");
    cin >> quarter;
    extractQuarter(pQuarter, quarter);
    int pxl = 0;
    for (int i = 0; i < SIZE; i += 2) {
        for (int j = 0; j < SIZE; j += 2) {
            for (int rgb = 0; rgb < RGB; rgb++) {
                img[i][j][rgb] = pQuarter[pxl][rgb];
                img[i + 1][j][rgb] = pQuarter[pxl][rgb];
                img[i][j + 1][rgb] = pQuarter[pxl][rgb];
                img[i + 1][j + 1][rgb] = pQuarter[pxl][rgb];
            }
            pxl++;
        }
    }
    delete[] pQuarter;
}


void extractQuarter(unsigned char * * &ptr, char quarter) {
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
    int pxl = 0;
    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            for (int rgb = 0; rgb < RGB; rgb++) {
                ptr[pxl][rgb] = img[i][j][rgb];
            }
            pxl++;
        }
    }
}

void mirrorFilter() {
    string mirrorInput;
    printf("1- to Mirror Left half, 2- to Mirror Right half\n3- to Mirror Upper half, 4- to Mirror Lower half\n");
    cin >> mirrorInput;
    if (mirrorInput == "1") {                           //left half mirror
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {     //loop over right half
                for (int k = 0; k < RGB; k++) {
                    img[i][j][k] = img[i][SIZE - 1 - j][k];            //change every pixel of right half to the opposite half
                }
            }
        }
    }
    else if (mirrorInput == "2") {                  //right half mirror
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {    //loop over left half
                for (int k = 0; k < RGB; k++) {
                    img[i][j][k] = img[i][SIZE - 1 - j][k];          //change every pixel to its opposite half
                }
            }
        }
    }
    else if (mirrorInput == "3") {                  //upper half mirror
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {        //loop over lower half
                for (int k = 0; k < RGB; k++) {
                    img[i][j][k] = img[SIZE - 1 - i][j][k];        //change every pixel to its opposite half
                }
            }
        }
    }
    else if (mirrorInput == "4") {                  //lower half mirror
        for (int i = 0;i < (SIZE / 2);i++) {
            for (int j = 0;j < SIZE;j++) {          //loop over upper half
                for (int k = 0; k < RGB; k++) {
                    img[i][j][k] = img[SIZE - 1 - i][j][k];    //change every pixel to its opposite half
                }
            }
        }
    }
    else {
        printf("Invalid input. Please try again\n");
        return mirrorFilter();
    }
}

void shuffleFilter() {
    int quarterSize = SIZE * SIZE / 4;
    int qrtr;
    string newOrder;
    unsigned char * * * pTemp;
    pTemp = new unsigned char * * [4];
    for (int i = 0; i < 4; i++) {
        pTemp[i] = new unsigned char * [quarterSize];
        for (int j = 0; j < quarterSize; j++) {
            pTemp[i][j] = new unsigned char [RGB];
        }
    }

    unsigned char * * pQuarter;
    pQuarter = new unsigned char * [quarterSize];
    for (int i = 0; i < quarterSize; i++) {
        pQuarter[i] = new unsigned char[RGB];
    }

    printf("New order of quarters ?\n");
    cin.ignore();
    getline(cin, newOrder);

    qrtr = 0;
    for (int i = 0; i < newOrder.length(); i++) {
        if (newOrder[i] == ' ') {
            continue;
        }
        extractQuarter(pQuarter, newOrder[i]);
        for (int pxl = 0; pxl < quarterSize; pxl++) {
            for (int rgb = 0; rgb < RGB; rgb++) {
                pTemp[qrtr][pxl][rgb] = pQuarter[pxl][rgb];
            }
        }
        qrtr++;
    }

    int pxl, row = 0;
    qrtr = 0;
    for (int i = 0; i < SIZE; i++) {    // Bug: (i) is too large to multiply with pxl!
        // we might use a variable for the current row
        if (i == SIZE / 2) {
            row = 0;
            qrtr += 2;
        }
        pxl = row * sqrt(quarterSize);
        for (int j = 0; j < SIZE; j++) {
            if (j == SIZE / 2){
                qrtr++;
                pxl = row * sqrt(quarterSize);
            }
            for (int rgb = 0; rgb < RGB; rgb++) {
                img[i][j][rgb] = pTemp[qrtr][pxl][rgb];
            }
            pxl++;
        }
        qrtr--;
        row++;
    }
}