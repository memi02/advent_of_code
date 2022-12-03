#include <fstream>
#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << "<input_file>" << std::endl;
        exit(0);
    }
    std::fstream in;
    in.open(argv[1], std::ios::in);
    // in.open("input.txt", std::ios::in);
    if (in.fail())
    {
        std::cout << "Error opening input file" << std::endl;
        exit(0);
    }

    int points = 0;
    char p1_in, howToEnd;
    while (in >> p1_in >> howToEnd)
    {
        int p1, myMove = 0;

        p1 = p1_in - 'A';

        switch (howToEnd)
        {
        case 'X':
            // you have to lose, so make his move +1
            myMove = (3 + (p1 - 1)) % 3;
            points += 0;
            // std::cout << (char)('A' + p1) << 'X' << (char)('A' + myMove) << " " << myMove + 1 << std::endl;
            break;
        case 'Y':
            // you have to draw, so make his move
            myMove = p1;
            points += 3;
            // std::cout << (char)('A' + p1) << 'Y' << (char)('A' + myMove) << " " << myMove + 4 << std::endl;
            break;
        case 'Z':
            // you have to win, so make his move -1
            myMove = (p1 + 1) % 3;
            points += 6;
            // std::cout << (char)('A' + p1) << 'Z' << (char)('A' + myMove) << " " << myMove + 7 << std::endl;
            break;
        }
        points += myMove + 1;
    }

    std::cout << points << std::endl;

    in.close();
    return 0;
}
