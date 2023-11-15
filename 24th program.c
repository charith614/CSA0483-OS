#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd; // File descriptor

    // Create a new file (or open if it already exists)
    fd = open("sample_file.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    char writeBuffer[] = "Hello, this is a sample file!\n";
    if (write(fd, writeBuffer, sizeof(writeBuffer)) == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Move the file cursor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Read data from the file
    char readBuffer[100];
    int bytesRead = read(fd, readBuffer, sizeof(readBuffer));
    if (bytesRead == -1) {
        perror("Error reading from file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Display the read data
    printf("Read from file: %.*s", bytesRead, readBuffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    // Remove the file
    if (remove("sample_file.txt") == -1) {
        perror("Error removing file");
        exit(EXIT_FAILURE);
    }

    printf("File management demonstration completed.\n");

    return 0;
}

