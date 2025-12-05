#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>
#ifndef VK_R
#define VK_R 0x52
#endif

const int FPS = 5;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 15;
std::vector<std::vector<int>> FieldLayout;
int FieldWidth;
int FieldHeight;
std::vector<int> FoodPos;
std::deque<std::vector<int>> SnakePos;
int SnakeLength;
std::vector<int> SnakeMovement;
bool GameRun = true;
bool GameOver = false;
bool GameWon = false;
char SnakeDrctn = 'o';
int Score = 0;

int CheckCollision(std::deque<std::vector<int>> SnakePos, std::vector<int> FoodPos, int OldScore);

int StartGame();

char ReadKeys(char CurrKey);

int RunGame();

std::deque<std::vector<int>> SetSnakePos(int W, int H);

std::deque<std::vector<int>> ReadSnakePos();

std::vector<int> SetSnakeMovement(std::vector<int> NewMovement);

int IncreaseSnakeSize(int H, int W);

std::vector<int> SetSnakeMove(char LastInput);

std::deque<std::vector<int>> UpdateSnakePos(int W, int H);

std::vector<int> SetFoodPos(std::deque<std::vector<int>> Snake, int W, int H);

bool CheckFoodCollision(std::deque<std::vector<int>> Snake);

std::vector<int> ReadFoodPos();

std::vector<std::vector<int>> SetField(int W, int H);

int PrintField(int Score);

std::vector<std::vector<int>> UpdateLayout(std::vector<int> Food, std::deque<std::vector<int>> Snake);

int main()
{
    RunGame();
}

//Game

char ReadKeys(char CurrKey)
{
    if (GetAsyncKeyState(VK_UP) != 0 && CurrKey != 'd')
    {
        return 'u';
    };
    if (GetAsyncKeyState(VK_RIGHT) != 0 && CurrKey != 'l')
    {
        return 'r';
    };
    if (GetAsyncKeyState(VK_DOWN) != 0 && CurrKey != 'u')
    {
        return 'd';
    };
    if (GetAsyncKeyState(VK_LEFT) != 0 && CurrKey != 'r')
    {
        return 'l';
        };
        if ((GetAsyncKeyState(VK_R) & 0x8000) != 0)
    {
        GameOver = true;
    };
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
    {
        GameRun = false;
    };
    return CurrKey;
}

int StartGame()
{
    system("cls");
    SetField(FIELD_WIDTH, FIELD_HEIGHT);
    SetFoodPos(ReadSnakePos(), FIELD_WIDTH, FIELD_HEIGHT);
    SetSnakePos(FIELD_WIDTH, FIELD_HEIGHT);
    return 0;
}

int CheckCollision(std::deque<std::vector<int>> SnakePos, std::vector<int> Food, int OldScore)
{
    int NewScore = OldScore;
    if (SnakePos[0][0] > FIELD_WIDTH - 1 || SnakePos[0][0] < 0)
    {
        GameOver = true;
    }
    if (SnakePos[0][1] > FIELD_HEIGHT - 1 || SnakePos[0][1] < 0)
    {
        GameOver = true;
    }
    if (SnakePos[0][0] == Food[0] && SnakePos[0][1] == Food[1])
    {
        IncreaseSnakeSize(FIELD_WIDTH, FIELD_HEIGHT);
        if (ReadSnakePos().size() >= FIELD_WIDTH * FIELD_WIDTH)
        {
        GameWon = true;
        GameRun = false;
        }
        SetFoodPos(ReadSnakePos(), FIELD_WIDTH, FIELD_HEIGHT);
        NewScore++;
    }
    std::deque<std::vector<int>> SnakeBody = ReadSnakePos();
    for (int i = 1; i < SnakeBody.size(); i++)
    {
        if (SnakeBody[0][0] == SnakeBody[i][0] && SnakeBody[0][1] == SnakeBody[i][1])
        {
            GameOver = true;
        }
    }
    return NewScore;
}

int RunGame()
{
    StartGame();
    while (GameRun)
    {
        SnakeDrctn = ReadKeys(SnakeDrctn);
        SetSnakeMove(SnakeDrctn);
        UpdateSnakePos(FIELD_WIDTH, FIELD_HEIGHT);
        Score = CheckCollision(ReadSnakePos(), ReadFoodPos(), Score);
        if (GameOver)
        {
            SnakeDrctn = 'o';
            SetSnakePos(FIELD_WIDTH, FIELD_HEIGHT);
            Score = 0;
            SetFoodPos(ReadSnakePos(), FIELD_WIDTH, FIELD_HEIGHT);
            GameOver = false;
        }
        UpdateLayout(ReadFoodPos(), ReadSnakePos());
        PrintField(Score);
        Sleep(1000 / FPS);
    }
    if (GameWon)
    {
        system("cls");
        std::cout << "You Won!";
        while ((GetAsyncKeyState(VK_SPACE) & 0x8000) == 0)
        {
            Sleep(1000 / FPS);
        }
    }
    return 0;
}

//Snake

std::deque<std::vector<int>> SetSnakePos(int W, int H)
{
    SnakePos = { {W / 2, H / 2}, {(W / 2) - 1, H / 2} };
    SnakeLength = SnakePos.size();
    SnakeMovement = { -1, 0 };
    return SnakePos;
}

std::deque<std::vector<int>> ReadSnakePos()
{
    return SnakePos;
}

std::vector<int> SetSnakeMovement(std::vector<int> NewMovement)
{
    SnakeMovement = NewMovement;
    return SnakeMovement;
}

int IncreaseSnakeSize(int H, int W)
{
    SnakePos.push_back(std::vector<int>(2, 0));
    SnakePos[SnakeLength][0] = SnakePos[SnakeLength - 1][0] - SnakeMovement[0];
    SnakePos[SnakeLength][1] = SnakePos[SnakeLength - 1][1] - SnakeMovement[1];
    if ((SnakePos[SnakeLength][0] < 0 || SnakePos[SnakeLength][0] > W))
    {
        SnakePos[SnakeLength][0] = SnakePos[SnakeLength - 1][0];
        SnakePos[SnakeLength][1] = SnakePos[SnakeLength - 1][1] - 1;
        if ((SnakePos[SnakeLength][1] < 0 || SnakePos[SnakeLength][1] > H))
        {
            SnakePos[SnakeLength][1] = SnakePos[SnakeLength - 1][1] + 1;
        }
    }
    if ((SnakePos[SnakeLength][1] < 0 || SnakePos[SnakeLength][1] > H))
    {
        SnakePos[SnakeLength][0] = SnakePos[SnakeLength - 1][0] - 1;
        SnakePos[SnakeLength][1] = SnakePos[SnakeLength - 1][1];
        if ((SnakePos[SnakeLength][0] < 0 || SnakePos[SnakeLength][0] > W))
        {
            SnakePos[SnakeLength][0] = SnakePos[SnakeLength - 1][0] + 1;
        }
    }
    SnakeLength++;
    return 0;
}

std::vector<int> SetSnakeMove(char LastInput)
{
    if (LastInput == 'u')
    {
        SnakeMovement = {0, -1};
    };
    if (LastInput == 'r')
    {
        SnakeMovement = {1, 0};
    };
    if (LastInput == 'd')
    {
        SnakeMovement = {0, 1};
    };
    if (LastInput == 'l')
    {
        SnakeMovement = {-1, 0};
    };
    return SnakeMovement;
}

std::deque<std::vector<int>> UpdateSnakePos(int W, int H)
{
    for (int i = SnakeLength - 1; i >= 1; i--)
    {
        SnakePos[i][0] = SnakePos[i - 1][0];
        SnakePos[i][1] = SnakePos[i - 1][1];
    }
    SnakePos[0][0] += SnakeMovement[0];
    SnakePos[0][1] += SnakeMovement[1];

    return {};
}

//Food

std::vector<int> SetFoodPos(std::deque<std::vector<int>> Snake, int W, int H)
{
    FoodPos.resize(2, 0);
    do
    {
        FoodPos[0] = rand() % W;
        FoodPos[1] = rand() % H;
    } while (CheckFoodCollision(Snake));
    return {FoodPos[0], FoodPos[1]};
}

bool CheckFoodCollision(std::deque<std::vector<int>> Snake)
{
    for (std::vector<int> Value : Snake)
    {
        if (Value[0] == FoodPos[0] && Value[1] == FoodPos[1])
        {
            return true;
        }
    }
}

std::vector<int> ReadFoodPos()
{
    return { FoodPos[0], FoodPos[1] };
}

//Field

std::vector<std::vector<int>> SetField(int W, int H)
{
        FieldWidth = W;
        FieldHeight = H;
        FieldLayout.resize(W, std::vector<int> (H, 0));

        return FieldLayout;
}

    int PrintField(int Score)
    {
        system("cls");
        for (int i = 0; i < FieldHeight; i++)
        {
            for (int u = 0; u < FieldWidth; u++)
            {
                std::cout << FieldLayout[u][i];
            }
            std::cout << std::endl;
        }
        std::cout << Score;
        return 1;
    }

    std::vector<std::vector<int>> UpdateLayout(std::vector<int> Food, std::deque<std::vector<int>> Snake)
    {
        std::vector<std::vector<int>> NewLayout(FieldWidth, std::vector<int> (FieldHeight, 0));
        NewLayout[Food[0]][Food[1]] = 1;
        for (std::vector<int> Value : Snake)
        {
             NewLayout[Value[0]][Value[1]] = 2;
        }
        NewLayout[Snake[0][0]][Snake[0][1]] = 2;
        NewLayout[Snake[1][0]][Snake[1][1]] = 2;
        FieldLayout = NewLayout;
        return NewLayout;
    }
