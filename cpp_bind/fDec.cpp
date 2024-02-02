#include <iostream>
#include "../fDec.h"

int main() {
    const char* filename = "example.bin";
    FILE* file = Open_File(filename);

    if (file == nullptr) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    // Your code to work with the file goes here

    fclose(file);
    return 0;
}
