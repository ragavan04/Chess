#include "controller.h"
using namespace std;

int main() {
    Controller boss;

    while (true) {
        boss.run();

        if (cin.eof()) { // Check for EOF (Ctrl+D)
            boss.displayScore(); // Display the score
            break; // Break out of the loop to end the program
        }

        // Clear the error flags and ignore the rest of the line in case of other input errors
        cin.clear();
    }

    return 0;
}
