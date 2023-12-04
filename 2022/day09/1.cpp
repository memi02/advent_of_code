#include <fstream>
#include <iostream>
#include <set>

struct coord
{
    int x;
    int y;

    void add(coord in)
    {
        x += in.x;
        y += in.y;
    }

    void setTo(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    std::string toString()
    {
        std::string res = "";
        res += std::to_string(x);
        res += ", ";
        res += std::to_string(y);
        return res;
    }

    friend bool operator<(const coord &l, const coord &r) { return (l.x < r.x ? true : (l.y < r.y ? true : false)); }

    coord(int x, int y) : x(x), y(y) {}
    coord() : coord(0, 0) {}
};

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << "<input_file>" << std::endl;
        exit(0);
    }
    std::fstream in;
    in.open(argv[1], std::ios::in);
    if(in.fail())
    {
        std::cout << "Error opening input file" << std::endl;
        exit(0);
    }

    coord head, tail;
    head.x = tail.x = 0;
    head.y = tail.y = 0;

    std::set<coord> passedPositions;

    std::string input;
    while(std::getline(in, input))
    {
        coord dir;
        switch(input.at(0))
        {
        case 'U':
            dir.x = 1;
            dir.y = 0;
            break;
        case 'R':
            dir.x = 0;
            dir.y = 1;
            break;
        case 'D':
            dir.x = -1;
            dir.y = 0;
            break;
        case 'L':
            dir.x = 0;
            dir.y = -1;
            break;
        }

        for(int i = 0; i < input.at(2) - '0'; i++)
        {
            head.add(dir);

            if(head.x - 1 > tail.x)
            {
                tail.setTo(tail.x + 1, head.y);
            }
            else if(head.x + 1 < tail.x)
            {
                tail.setTo(tail.x - 1, head.y);
            }

            if(head.y - 1 > tail.y)
            {
                tail.setTo(head.x, tail.y + 1);
            }
            else if(head.y + 1 < tail.y)
            {
                tail.setTo(head.x, tail.y - 1);
            }
            passedPositions.insert(tail);
        }
        std::cout << head.toString() << " " << tail.toString() << std::endl;
    }
    std::cout << passedPositions.size() << std::endl;

    in.close();
    return 0;
}