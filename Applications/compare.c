//  take as arguments the paths to two image files in the TGA format,
// and return the value 1 if the image stored in the first file is identical to the one stored in the second one, 
// and returns 0 otherwise.

#include "./include/applications.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Invalid number of arguments\n");
        exit(2);
    }
    RasterImage image1 = readTGA(argv[1]);
    RasterImage image2 = readTGA(argv[2]);

    return compare(&image1, &image2);
}