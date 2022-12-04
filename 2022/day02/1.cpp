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
    char p1_in, p2_in;
    while (in >> p1_in >> p2_in)
    {

        int p1, p2;

        p1 = p1_in - 'A' + 1;
        p2 = p2_in - 'X' + 1;

        switch ((3 + (p1 - p2)) % 3)
        {
        case 0:
            // draw
            points += 3;
            break;
        case 1:
            // p1 won
            points += 0;
            break;
        case 2:
            // p1 lost
            points += 6;
            break;
        }
        points += p2;
    }

    std::cout << points << std::endl;
    return 0;
}
