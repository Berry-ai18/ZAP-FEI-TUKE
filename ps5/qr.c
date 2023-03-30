#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string) + 1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8]);

int main()
{

    return 0;
}

void encode_char(const char character, bool bits[8])
{
    int charNum = character;
    for (int position = 7; position >= 0; position--)
    {
        bits[position] = charNum % 2;
        charNum /= 2;
    }
}

char decode_byte(const bool bits[8])
{
    int charNum = 0;
    int biteConverter[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    for (int position = 0; position < 8; position++)
    {
        if (bits[position] == 1)
        {
            charNum += biteConverter[7 - position];
        }
    }
    return (char)charNum;
}

void encode_string(const char string[], bool bytes[strlen(string) + 1][8])
{
    for (int position = 0; position < strlen(string) + 1; position++)
    {
        encode_char(string[position], bytes[position]);
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows])
{
    for (int position = 0; position < rows; position++)
    {
        string[position] = decode_byte(bytes[position]);
    }
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
    for (int i = 0; i < offset * 8; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int bitOffset = cols * (i / 8);
            int currentBit = j + bitOffset;
            int currentWord = i % 8;

            if (currentBit < rows)
            {
                blocks[i][j] = bytes[currentBit][currentWord];
            }
            if (currentBit >= rows)
            {
                blocks[i][j] = 0;
            }
        }
    }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
    for (int i = 0; i < offset * 8; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int currentWord = i % 8;
            int bitOffset = cols * (i / 8);
            bytes[j + bitOffset][currentWord] = blocks[i][j];
        }
    }
}
