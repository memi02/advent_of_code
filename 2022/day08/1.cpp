#include <fstream>
#include <iostream>

struct palaces
{
    int height;
    bool seen;
};

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

    const int gridSize = 99; // 99 per input, 5 per test_input.txt
    palaces grid[gridSize][gridSize];

    char buffer;
    for (int j = 0; j < gridSize; j++)
    {
        for (int i = 0; i < gridSize; i++)
        {
            in.get(buffer);
            grid[i][j].height = buffer - '0';
            grid[i][j].seen = false;
        }
        in.get(buffer); // il carattere di a capo
    }

    int count = 0;
    for (int i = 0; i < gridSize; i++)
    {
        int max = grid[i][0].height - 1;
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[i][j].height > max)
            {
                max = grid[i][j].height;
                if (!grid[i][j].seen)
                {
                    grid[i][j].seen = true;
                    ++count;
                }
            }
        }
    }

    for (int i = 0; i < gridSize; i++)
    {
        int max = grid[i][gridSize - 1].height - 1;
        for (int j = gridSize - 1; j >= 0; j--)
        {
            if (grid[i][j].height > max)
            {
                max = grid[i][j].height;
                if (!grid[i][j].seen)
                {
                    grid[i][j].seen = true;
                    ++count;
                }
            }
        }
    }

    for (int j = 0; j < gridSize; j++)
    {
        int max = grid[0][j].height - 1;
        for (int i = 0; i < gridSize; i++)
        {
            if (grid[i][j].height > max)
            {
                max = grid[i][j].height;
                if (!grid[i][j].seen)
                {
                    grid[i][j].seen = true;
                    ++count;
                }
            }
        }
    }

    for (int j = 0; j < gridSize; j++)
    {
        int max = grid[gridSize - 1][j].height - 1;
        for (int i = gridSize - 1; i >= 0; i--)
        {
            if (grid[i][j].height > max)
            {
                max = grid[i][j].height;
                if (!grid[i][j].seen)
                {
                    grid[i][j].seen = true;
                    ++count;
                }
            }
        }
    }

    std::cout << count << std::endl;
    in.close();
    return 0;
}
