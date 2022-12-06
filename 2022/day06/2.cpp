#include <fstream>
#include <iostream>

bool areAllDifferent(char c[], int size);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << "<input_file>" << std::endl;
        exit(0);
    }
    std::fstream in;
    in.open(argv[1], std::ios::in);
    if (in.fail())
    {
        std::cout << "Error opening input file" << std::endl;
        exit(0);
    }

    const int bufferSize = 14;
    char buffer[bufferSize];

    for (int i = 0; i < bufferSize; i++)
    {
        in.get(buffer[i]);
        // std::cout << buffer[i];
    }

    int pos = bufferSize;
    int c = 0;
    while (!areAllDifferent(buffer, bufferSize))
    {
        in.get(buffer[c]);
        // std::cout << buffer[c];
        c = (c + 1) % bufferSize;
        pos++;
    }
    std::cout << pos << std::endl;

    in.close();
    return 0;
}

bool areAllDifferent(char c[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (c[i] == c[j])
                return false;
        }
    }
    return true;
}