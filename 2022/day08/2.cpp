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
    if (in.fail())
    {
        std::cout << "Error opening input file" << std::endl;
        exit(0);
    }

    const int gridSize = 99; // 99 per input, 5 per test_input.txt
    int grid[gridSize][gridSize];

    char buffer;
    for (int j = 0; j < gridSize; j++)
    {
        for (int i = 0; i < gridSize; i++)
        {
            in.get(buffer);
            grid[i][j] = buffer - '0';
        }
        in.get(buffer); // il carattere di a capo
    }

    int res = 0;

    // i can avoid the edges of the map because they will always have a side as 0 (and 0 * n = 0)
    for (int x = 1; x < gridSize - 1; ++x)
    {
        for (int y = 1; y < gridSize - 1; ++y)
        {
            int tot = 1;
            int tmp = 0;
            bool loop = true;
            // going right
            tmp = 0;
            loop = true;
            for (int i = x + 1; i < gridSize && loop; i++)
            {
                tmp++;
                loop = (grid[i][y] < grid[x][y]);
            }
            tot *= tmp;

            // going down
            tmp = 0;
            loop = true;
            for (int j = y + 1; j < gridSize && loop; j++)
            {
                tmp++;
                loop = (grid[x][j] < grid[x][y]);
            }
            tot *= tmp;

            // going left
            tmp = 0;
            loop = true;
            for (int i = x - 1; i >= 0 && loop; i--)
            {
                tmp++;
                loop = (grid[i][y] < grid[x][y]);
            }
            tot *= tmp;

            // going up
            tmp = 0;
            loop = true;
            for (int j = y - 1; j >= 0 && loop; j--)
            {
                tmp++;
                loop = (grid[x][j] < grid[x][y]);
            }
            tot *= tmp;

            res = std::max(tot, res);
        }
    }

    std::cout << res << std::endl;
    in.close();
    return 0;
}
