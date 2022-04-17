#include <iostream>
#include "bmplib.h"

using namespace std;

int main() {
    char userInput;
    cout << "Welcome Habibi!\n";
    // read image
    while (true) {
        cin >> userInput;
        switch (userInput) {
            case '0': cout << "Good Bye!";
                return 0;
            default: cout << "Invalid Input! Try Again.";
        }
    }
}
