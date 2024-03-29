// FCAI - Programming 1 - 2022 - Assignment 3
// Program Name: Gray-Scale-Image-Processor.cpp
// Last Modification Date: Apr 21, 2022
// Author1 and ID and Group: Mahmoud Adel  | 20210563 | S25
// Author2 and ID and Group: Maya Ayman    | 20210508 | S25
// Author3 and ID and Group: Yousef Kilany | 20210544 | S25
// Teaching Assistant: Eng. Mahmoud Fateaha 
// Purpose: This program processes images taken from the user, in many different ways.

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
void bwFilter();                     // 1
void invertFilter();                 // 2
void mergeFilter();                  // 3
void flipFilter();                   // 4
void rotateFilter();                 // 5
void darkenAndLightenFilter();       // 6
void edgeFilter();                   // 7
void enlargeFilter();                // 8
void shrinkFilter();                 // 9
void mirrorFilter();                 // a
void shuffleFilter();                // b
void blurFilter();                   // c




void rotate90();
void extractQuarter(unsigned char * * &, char);


int main() {
    // NOTE: The program loops on the same picture until saved, The user can apply multiple filters on the same picture.
    // The program asks for a new picture only after the user save the previous picture.
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
            case '3':
                mergeFilter();
                printf("Images merged.\n");
                break;
            case '4':
                flipFilter();
                printf("Image flipped.\n");
                break;
            case '5':
                rotateFilter();
                printf("Image rotated.\n");
                break;
            case '6':
                darkenAndLightenFilter();
                printf("Image has been lightened/darkened.\n");
                break;
            case '7':
                edgeFilter();
                printf("Edges detected.\n");
                break;
            case '8':
                enlargeFilter();
                printf("Image enlarged.\n");
                break;
            case '9':
                shrinkFilter();
                printf("Image shrunk. \n");
                break;
            case 'a':
                mirrorFilter();
                printf("Image mirrored.\n");
                break;
            case 'b':
                shuffleFilter();
                printf("Image shuffled.\n");
                break;
            case 'c':
                blurFilter();
                printf("Image blurred.\n");
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
            float avg = (img[i][j][0] + img[i][j][1] + img[i][j][2]) / 3;       //calculate avg pixel color
            if (avg > 127) {                                                    // if the value of avg is > 127
                for (int k = 0; k < RGB; k++)                                   //loop over every color in each pixel
                    img[i][j][k] = 255;                                         // change to white (255)
            }
            else {
                for (int k = 0; k < RGB; k++)
                    img[i][j][k] = 0;                                           // else change to black (0)
            }
            
        }
    }
}

void invertFilter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                img[i][j][k] = 255 - img[i][j][k];
            }   // Invert each color in each pixel
        }
    }
}

void mergeFilter(){
    // Takes the name of the image to be merged with the current one
    char imageName2[100];
    unsigned char img2[SIZE][SIZE][RGB];
    cout << "Please enter name of the image to merge: " << endl;
    cin >> imageName2;
    strcat(imageName2, ".bmp");
    readRGBBMP(imageName2, img2);

    // Merges the 2 images
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                img[i][j][k] = (img[i][j][k] + img2[i][j][k]) / 2;
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
    cin >> angle;
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
            }   // Store image into a temp
        }
    }
    // Store temp into original image (rotated)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                img[j][SIZE-1-i][k] = tempImg[i][j][k];
            }   // by putting each row into a column
        }       // (top-down -> right left)
    }
}

void darkenAndLightenFilter() {
    string rspns;
    cout << "Do you want to lighten or darken the image? " << endl;
    cin >> rspns;
    transform(rspns.begin(), rspns.end(), rspns.begin(), ::tolower);
    // Lightens an image
    if (rspns == "lighten")
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    (img[i][j][k] * 1.5 > 255) ? img[i][j][k] = 255 : img[i][j][k] += 0.5 * img[i][j][k];
                }
            }
        }
    // Darkens an image
    else if (rspns == "darken")
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    img[i][j][k] /= 2;
                }
            }
        }
    else
    {
        cout << "Invalid choice. Please choose a valid option: ";
        return darkenAndLightenFilter();
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
    // Initialize a 2D dynamic array to hold a quarter
    unsigned char * * pQuarter;
    pQuarter = new unsigned char * [quarterSize];
    for (int i = 0; i < quarterSize; i++) {
        pQuarter[i] = new unsigned char[RGB];
        // each pointer points to [array of colors (RGB)] in the pixel
    }
    printf("Which quarter to enlarge 1, 2, 3 or 4?\n");
    cin >> quarter;
    extractQuarter(pQuarter, quarter);
    int pxl = 0; // quarter-pointer iterator
    // Store the extracted quarter into the original image (enlarged)
    for (int i = 0; i < SIZE; i += 2) {
        for (int j = 0; j < SIZE; j += 2) {
            for (int rgb = 0; rgb < RGB; rgb++) { // rgb: color iterator
                img[i][j][rgb] = pQuarter[pxl][rgb];
                img[i + 1][j][rgb] = pQuarter[pxl][rgb];
                img[i][j + 1][rgb] = pQuarter[pxl][rgb];
                img[i + 1][j + 1][rgb] = pQuarter[pxl][rgb];
            }   // by putting each single pixel into 4 pixels
            pxl++;
        }
    }
    // Cleaning
    for (int i = 0; i < quarterSize; i++) {
        delete[] pQuarter[i];
    }
    delete[] pQuarter;
}

void shrinkFilter(){
    int shrinkFactor, x = 0, y = 0, z = 0;
    cout << "By which factor do you want to shrink the image: 2, 3, or 4?" << endl;
    cin >> shrinkFactor;
    unsigned char newImg[SIZE][SIZE][RGB];   //creating a new array to store the shrunk image

    if (shrinkFactor == 2 || shrinkFactor == 3 || shrinkFactor == 4) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    newImg[i][j][k] = 255;
                }
            }
        }

        // Shrinking the image by removing some pixels according to the shrink factor
        for (int i = 0; i < SIZE; i += shrinkFactor) {
            for (int j = 0; j < SIZE; j += shrinkFactor) {
                for (int k = 0; k < RGB; k++) {
                    newImg[x][y][z++] = img[i][j][k];
                }
            }
            x++;
            y++;
            y = 0;
            z = 0;
        }
        // Putting the new shrunk image in the old array
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    img[i][j][k] = newImg[i][j][k];
                }
            }
        }
    }
    else
    {
        cout << "Please enter a valid shrink factor: ";
        return shrinkFilter();
    }
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
    int pxl = 0; // pointer iterator
    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            for (int rgb = 0; rgb < RGB; rgb++) {
                ptr[pxl][rgb] = img[i][j][rgb];
            }   // Storing a quarter of the image into the quarter-pointer
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

void blurFilter(){
    int avg, sum = 0;
    // Calculates average of each 8 subsequent pixels and assigns this value to each pixel of the 8 in a column
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
            if (j <= 247) {                         // makes sure the index doesn't go beyond 255
                for (int k = 0; k < RGB; ++k) {
                    for (int r = 0; r < 8; ++r) {
                        sum += img[i][j + r][k];
                    }
                    avg = sum/8;
                    img[i][j][k] = avg;
                    sum = 0;
                }
            } else {
                for (int k = 0; k < RGB; ++k) {
                    for (int l = 0; l < SIZE - j; ++l) {
                        sum += img[i][j + l][k];
                    }
                    avg = sum/8;
                    img[i][j][k] = avg;
                    sum = 0;
                    for (int l = 0; l < SIZE - j; ++l) {
                        img[i][j + l][k] = avg;
                    }
               }
                break;
            }
        }
    }
    // Calculates average of each 8 subsequent pixels and assigns this value to each pixel of the 8 in a row
    for (int i = 0; i < SIZE; ++i) {
        if (i <= 247) {                         // makes sure the index doesn't go beyond 255
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    for (int r = 0; r < 8; ++r) {
                        sum += img[i + r][j][k];
                    }
                    avg = sum / 8;
                    img[i][j][k] = avg;
                    sum = 0;
                }
            }
        }
        else {
            for (int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; ++k) {
                    for (int l = 0; l < SIZE - i; ++l) {
                        sum += img[i+l][j][k];
                    }
                    avg = sum/8;
                    img[i][j][k] = avg;
                    sum = 0;
                    for (int l = 0; l < SIZE - i; ++l) {
                        img[i + l][j][k] = avg;
                    }
                }
            }
            break;
        }
    }
}

void shuffleFilter() {
    int quarterSize = SIZE * SIZE / 4;
    string newOrder;
    // Initialize a 3D dynamic temp-array
    // divided into 4 quarters, each is
    // a 2D dynamic array
    unsigned char * * * pTemp;
    pTemp = new unsigned char * * [4];
    for (int i = 0; i < 4; i++) {
        pTemp[i] = new unsigned char * [quarterSize];
        for (int j = 0; j < quarterSize; j++) {
            pTemp[i][j] = new unsigned char [RGB];
        }
    }
    // Initialize a 2D dynamic array to hold a quarter
    unsigned char * * pQuarter;
    pQuarter = new unsigned char * [quarterSize];
    for (int i = 0; i < quarterSize; i++) {
        pQuarter[i] = new unsigned char[RGB];
    }
    // take new order from user, and make sure it's valid
    printf("New order of quarters ?\n");
    while (true) {
        int i = 0;
        cin.ignore(); // for getline() to work properly
        getline(cin, newOrder);
        // remove any spaces
        newOrder.erase(remove(newOrder.begin(), newOrder.end(), ' '), newOrder.end());
        for (i = 0; i < newOrder.length(); i++) { // loop on the input
            if (newOrder[i] < '1' || newOrder[i] > '4') {
                break; // if other than {1,2,3,4} (1)
            }
        }
        if (i < newOrder.length()) {
            printf("Wrong Input!\n");
            continue; // (1) retake input
        }
        if (newOrder.length() == 4) {
            break; // if passed all check if it's 4 quarters
        }          // if so, break
        printf("Wrong Input!\n");
    }

    int qrtr = 0; // quarter indicator
    for (int i = 0; i < newOrder.length(); i++) { // Take a quarter each iteration
        extractQuarter(pQuarter, newOrder[i]);
        for (int pxl = 0; pxl < quarterSize; pxl++) { // pxl: loops on each
            for (int rgb = 0; rgb < RGB; rgb++) {     // pixel in the quarter
                pTemp[qrtr][pxl][rgb] = pQuarter[pxl][rgb];
            }   // Store extracted-quarter into a quarter of temp
        }
        qrtr++; // move to next quarter of temp
    }

    // This process stores the 3D dynamic temp-array into original image (2D)
    int pxl, row = 0;
    qrtr = 0;
    for (int i = 0; i < SIZE; i++) { // loop over original image
        if (i == SIZE / 2) {
            row = 0;   // When half is reached (vertically)
            qrtr += 2; // move quarter indicator to 3rd quarter
        }
        pxl = row * sqrt(quarterSize);
        for (int j = 0; j < SIZE; j++) {
            if (j == SIZE / 2){  // When half is reached (horizontally)
                qrtr++;          // move quarter indicator to next quarter
                pxl = row * sqrt(quarterSize);
                // this indicates the position of pxl
                // according to current reached row
                // so pxl doesn't get lost while
            }   // going back and forth through quarters

            for (int rgb = 0; rgb < RGB; rgb++) {
                img[i][j][rgb] = pTemp[qrtr][pxl][rgb];
                // Store current pixel into image
            }
            pxl++;
        }
        qrtr--; // go back to previous quarter
        row++;  // and move to next row
    }
    // Cleaning
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < quarterSize; j++) {
            delete[] pTemp[i][j];
        }
        delete[] pTemp[i];
    }
    delete[] pTemp;
    for (int i = 0; i < quarterSize; i++) {
        delete[] pQuarter[i];
    }
    delete[] pQuarter;
}
