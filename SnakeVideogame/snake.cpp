#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>

class Snake
{
    private:
        std::deque<std::vector<int>> SnakePos;
        int Length;
        std::vector<int> Movement;
    public:
        std::deque<std::vector<int>> SetPos(int W, int H)
        {
            SnakePos = {{W / 2, H / 2}, {(W / 2) - 1, H / 2}};
            Length = SnakePos.size();
            Movement = {-1, 0};
            return SnakePos;
        }

        std::deque<std::vector<int>> ReadSnakePos()
        {
            return SnakePos;
        }

        std::vector<int> SetMovement(std::vector<int> NewMovement)
        {
            Movement = NewMovement;
            return Movement;
        }

        int IncreaseSize(int H, int W)
        {
            Pos.push_back(std::vector<int> (2, 0));
            Pos[Length][0] = Pos[Length - 1][0] - Movement[0];
            Pos[Length][1] = Pos[Length - 1][1] - Movement[1];
            if ((Pos[Length][0] < 0 || Pos[Length][0] > W))
            {
                Pos[Length][0] = Pos[Length - 1][0];
                Pos[Length][1] = Pos[Length - 1][1] - 1;
                if ((Pos[Length][1] < 0 || Pos[Length][1] > H))
                {
                    Pos[Length][1] = Pos[Length - 1][1] + 1;
                }
            }
            if ((Pos[Length][1] < 0 || Pos[Length][1] > H))
            {
                Pos[Length][0] = Pos[Length - 1][0] - 1;
                Pos[Length][1] = Pos[Length - 1][1];
                if ((Pos[Length][0] < 0 || Pos[Length][0] > W))
                {
                    Pos[Length][0] = Pos[Length - 1][0] + 1;
                }
            }
            /*if (CheckCollision(Pos, Length))
            {
                Pos[Length][0] = Pos[Length - 1][0] - 1;
                Pos[Length][1] = Pos[Length - 1][1];
                if (CheckCollision(Pos, Length))
                {
                    Pos[Length][0] = Pos[Length - 1][0] + 1;
                    Pos[Length][1] = Pos[Length - 1][1];
                    if (CheckCollision(Pos, Length))
                    {
                        Pos[Length][0] = Pos[Length - 1][0];
                        Pos[Length][1] = Pos[Length - 1][1] - 1;
                        if (CheckCollision(Pos, Length))
                        {
                            Pos[Length][0] = Pos[Length - 1][0];
                            Pos[Length][1] = Pos[Length - 1][1] + 1;
                        }
                    }
                }
            }*/
            Length++;
            /*auto LastSegment = Pos.back();
            Pos.push_back(LastSegment); // добавляем копию последнего элемента
            Length = Pos.size();*/
            return 0;
        }

        std::vector<int> SetMove(char LastInput)
        {
            if (LastInput == 'u')
            {
                Movement = {0, -1};
            };
            if (LastInput == 'r')
            {
                Movement = {1, 0};
            };
            if (LastInput == 'd')
            {
                Movement = {0, 1};
            };
            if (LastInput == 'l')
            {
                Movement = {-1, 0};
            };
            return Movement;
        }

        std::deque<std::vector<int>> UpdatePos(int W, int H)
        {
            for (int i = Length - 1; i >= 1; i--)
            {
                Pos[i][0] = Pos[i - 1][0];
                Pos[i][1] = Pos[i - 1][1];
            }
            Pos[0][0] += Movement[0];
            Pos[0][1] += Movement[1];

            return {};
        }
};
