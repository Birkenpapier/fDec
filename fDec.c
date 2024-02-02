#include <stdio.h>
#include <stdlib.h>

/**
 * Opens a file in read-binary mode.
 * @param fileName Name of the file to open.
 * @return Pointer to the opened file, or NULL if the file couldn't be opened.
 */
FILE* Open_File(const char *fileName) {
    FILE *filePointer = fopen(fileName, "rb");

    if(!filePointer) {
        fprintf(stderr, "Error: File '%s' could not be opened!\n", fileName);
        
        return NULL;
    }

    return filePointer;
}

/**
 * Reads the size of the file.
 * @param filePointer Pointer to the file whose size is to be determined.
 * @return Size of the file.
 */
int Get_File_Size(FILE *filePointer) {
    fseek(filePointer, 0, SEEK_END);
    int size = ftell(filePointer);
    rewind(filePointer);

    return size;
}

/**
 * Reads the contents of the file into a buffer.
 * @param filePointer Pointer to the file to read from.
 * @param size Size of the file.
 * @return Pointer to the buffer containing file data.
 */
unsigned char* Read_File_Contents(FILE *filePointer, int size) {
    unsigned char *buffer = malloc(size);

    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }
    fread(buffer, size, 1, filePointer);

    return buffer;
}

/**
 * Prints the file contents in a formatted manner.
 * @param buffer Buffer containing the file data.
 * @param size Size of the buffer.
 * @param fileName Name of the file.
 */
void Print_File_Contents(const unsigned char *buffer, int size, const char *fileName) {
    printf("/* file: %s */\n", fileName);
    printf("const int fsize = %d;\n\n", size);
    printf("const unsigned char file[] = {\n");
    
    for (int i = 0; i < size; ++i) {
        printf("%d%s", buffer[i], i == size-1 ? "" : ", ");
        if ((i + 1) % 10 == 0) printf("\n");
    }

    printf("\n};\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n\tfDec <filename>.<filextension> > <filename>.c\n");
        
        return 1;
    }

    const char *fname = argv[1];
    FILE *fp = Open_File(fname);
    if (!fp) return 1;

    int fsize = Get_File_Size(fp);
    unsigned char *binContent = Read_File_Contents(fp, fsize);
    fclose(fp);

    if (!binContent) return 1;

    Print_File_Contents(binContent, fsize, fname);

    free(binContent);
    return 0;
}
