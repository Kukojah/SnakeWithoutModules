#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>
#ifndef VK_R
#define VK_R 0x52
#endif
#include "field.cpp"
#include "food.cpp"
#include "snake.cpp"

const int FPS = 5;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 15;
Field GameField;
Food Meat;
Snake Player;
bool GameRun = true;
bool GameOver = false;
bool GameWon = false;
char SnakeDrctn = 'o';
int Score = 0;

int CheckCollision(std::deque<std::vector<int>> SnakePos, std::vector<int> FoodPos, int OldScore);

int StartGame();

char ReadKeys(char CurrKey);

int RunGame();

int main()
{
    RunGame();
}

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
    GameField.SetField(FIELD_WIDTH, FIELD_HEIGHT);
    Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
    Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
    return 0;
}

int CheckCollision(std::deque<std::vector<int>> SnakePos, std::vector<int> FoodPos, int OldScore)
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
    if (SnakePos[0][0] == FoodPos[0] && SnakePos[0][1] == FoodPos[1])
    {
        Player.IncreaseSize(FIELD_WIDTH, FIELD_HEIGHT);
        if (Player.ReadPos().size() >= FIELD_WIDTH * FIELD_WIDTH)
        {
        GameWon = true;
        GameRun = false;
        }
        Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
        NewScore++;
    }
    std::deque<std::vector<int>> SnakeBody = Player.ReadPos();
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
        Player.SetMove(SnakeDrctn);
        Player.UpdatePos(FIELD_WIDTH, FIELD_HEIGHT);
        Score = CheckCollision(Player.ReadPos(), Meat.ReadPos(), Score);
        if (GameOver)
        {
            SnakeDrctn = 'o';
            Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
            Score = 0;
            Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
            GameOver = false;
        }
        GameField.UpdateLayout(Meat.ReadPos(), Player.ReadPos());
        GameField.PrintField(Score);
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
