#include <stdio.h>
#include <stdlib.h>

struct WS_Wario2Save
{
    uint8_t unk[8];         // 0x407
    uint8_t total_coins[3]; // 0x40F
};

const int offset = 0x407;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *file_path = argv[1];

    while (1)
    {
        FILE *file = fopen(file_path, "rb");
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }

        if (fseek(file, offset, SEEK_SET) != 0)
        {
            perror("Error seeking to the file c byte");
            fclose(file);
            return 1;
        }
        uint8_t size = 56;
        uint8_t byte_array[size];
        size_t bytes_read = fread(byte_array, 1, size, file);

        // Check if the read operation was successful
        if (bytes_read != size)
        {
            perror("Error reading from file");
            fclose(file);
            return 1;
        }

        static uint8_t prev_byte_array[56];
        static uint8_t is_waiting = 1;
        static uint8_t has_printed_waiting = 0;
        static uint8_t has_initial_read = 0;
        for (int i = 0; i < size; i++)
        {
            if ((byte_array[i] != prev_byte_array[i]))
            {
                printf("0x%x:, %02x -> %02x \n",i+offset, prev_byte_array[i], byte_array[i]);
                has_printed_waiting = 0;
            }
        }

        if (!has_printed_waiting)
        {
            printf("Waiting for changes...\n");
            has_printed_waiting = 1;
        }

        // Close the file
        fclose(file);

        for (int i = 0; i < size; i++)
        {
            prev_byte_array[i] = byte_array[i];
            has_initial_read = 1;
        }
    }
}