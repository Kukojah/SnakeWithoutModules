#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>

class Food
{
private:
    std::vector<int> Pos;
public:
    std::vector<int> SetPos(std::deque<std::vector<int>> Snake, int W, int H)
    {
        Pos.resize(2, 0);
        do
        {
            Pos[0] = rand() % W;
            Pos[1] = rand() % H;
        } while (CheckCollision(Snake));
        return Pos;
    }

    bool CheckCollision(std::deque<std::vector<int>> Snake)
    {
        for (std::vector<int> Value : Snake)
        {
            if (Value[0] == Pos[0] && Value[1] == Pos[1])
            {
                return true;
            }
        }
    }

    std::vector<int> ReadPos()
    {
        return { Pos[0], Pos[1] };
    }

};
