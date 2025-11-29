#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>

class Field
{
    private:
        std::vector<std::vector<int>> Layout;
        int Width;
        int Height;
    public:
        std::vector<std::vector<int>> SetField(int W, int H)
        {
        Width = W;
        Height = H;
        Layout.resize(W, std::vector<int> (H, 0));

        return Layout;
        }

    int PrintField(int Score)
    {
        system("cls");
        for (int i = 0; i < Height; i++)
        {
            for (int u = 0; u < Width; u++)
            {
                std::cout << Layout[u][i];
            }
            std::cout << std::endl;
        }
        std::cout << Score;
        return 1;
    }

    std::vector<std::vector<int>> UpdateLayout(std::vector<int> FoodPos, std::deque<std::vector<int>> Snake)
    {
        std::vector<std::vector<int>> NewLayout(Width, std::vector<int> (Height, 0));
        NewLayout[FoodPos[0]][FoodPos[1]] = 1;
        for (std::vector<int> Value : Snake)
        {
             NewLayout[Value[0]][Value[1]] = 2;
        }
        NewLayout[Snake[0][0]][Snake[0][1]] = 2;
        NewLayout[Snake[1][0]][Snake[1][1]] = 2;
        Layout = NewLayout;
        return NewLayout;
    }
};
