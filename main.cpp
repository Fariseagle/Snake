#include "lpclib.h"
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


const int CELL_SIZE = 15;

struct Food
{
    int x_coord;
    int y_coord;
};
struct coord
{
    int x;
    int y;
};
struct follow
{
    int x;
    int y;
};

void DrawArm(int x, int y, int angle);
void DrawHead(int x, int y, int angle);
void Erase(vector<follow> & p);
void Move(int & x, int & y, int angle);
void Rotate(int & angle, char cmd);
void foodp(Food & apple);
void RunGame();
void Key(char choice, int & angle0);
void checkapple(Food & apple2,int & x0, int &y0, vector<follow> & p, int & score);
void checkborder(int &x0,int &y0, int & x);
void addPosition(vector<follow> & position, int x0,int y0);
void eatSelf(vector<follow> p,int & x, int x0,int y0);
void DelEvery();
void NewGame(int & game, int score);
void Score(int score);
void Score2(int score, int & score2);

int main()
{
    GraphicsWindow(600, 600, "black");
    RunGame();

}
void DrawHead(int x, int y, int angle)
{
    DrawCircle(x, y, CELL_SIZE / 2, "yellow", true);
    UpdateDisplay();
}
void Erase(vector<follow> & p )
{
    DrawCircle(p[0].x, p[0].y, CELL_SIZE / 2, "black", true);
    p.erase(p.begin());
}
void Move(int & x, int & y, int angle)
{
    int n=0;
        if(angle == 270)
        {
            y-=CELL_SIZE;
        }
        else if(angle == 90)
        {
            y+=CELL_SIZE;
        }
        else if(angle == 180)
        {
            x-=CELL_SIZE;
        }
        else if(angle == 0)
        {
            x+=CELL_SIZE;
        }
}
void foodp(Food & apple)
{
        apple.x_coord=RandomInt(1,600/CELL_SIZE - 1)*CELL_SIZE;
        apple.y_coord=RandomInt(1,600/CELL_SIZE - 1)*CELL_SIZE;
        DrawCircle(apple.x_coord, apple.y_coord, CELL_SIZE / 2, "red", true);
}
void Rotate(int & angle, char cmd)
{
    if(cmd=='S')
    {
        if(angle == 270)
        {

        }
        else
        {
            angle=90;
        }

    }
    else if(cmd == 'W')
    {
        if(angle == 90)
        {

        }
        else
        {
            angle=270;
        }
    }
    else if(cmd == 'D')
    {
        if(angle == 180)
        {

        }
        else
        {
            angle=0;
        }
    }
    else if(cmd == 'A')
    {
        if(angle == 0)
        {

        }
        else
        {
            angle=180;
        }
    }
}
void Key(char choice, int & angle0)
{
    if(KeyWasPressed("up"))
        {
            choice = 'W';
            Rotate(angle0, choice);
        }
        else if(KeyWasPressed("down"))
        {
            choice = 'S';
            Rotate(angle0, choice);
        }
        else if(KeyWasPressed("left"))
        {
            choice = 'A';
            Rotate(angle0, choice);
        }
        else if(KeyWasPressed("right"))
        {
            choice = 'D';
            Rotate(angle0, choice);
        }
}
void checkapple(Food & apple2,int & x0, int &y0, vector<follow> & p, int & score)
{
    if(x0 == apple2.x_coord && y0 == apple2.y_coord)
        {
            foodp(apple2);
            p.push_back({x0,y0});
            score++;
        }
}
void checkborder(int &x0,int &y0, int & x)
{
    if(x0 == 600 || y0==600)
    {
        x++;
    }
    else if(x0== 0 || y0==0)
    {
        x++;
    }
}
void addPosition(vector<follow> & position, int x0, int y0)
{
    follow po;
    po = {x0,y0};
    position.push_back(po);
}
void eatSelf(vector<follow> p,int & x, int x0,int y0)
{
    for(int i = 0; i<p.size()-1;i++)
    {
        if(x0==p[i].x && y0 == p[i].y)
        {
            x++;
        }
    }
}
void NewGame(int & game, int score)
{
    ostringstream convert;

    convert << game;
    string Result = convert.str()+" Lives left";
    DrawString(Result,440,0, "white", 30);
}
void DelEvery()
{
    DrawRectangle(0,0,5000,5000,"black",true);
}
void Score(int score)
{
    ostringstream convert;
    convert << score;

    string Result1 = " Score:" + convert.str();
    DrawString(Result1,90,150, "white", 30);
}
void Score2(int score, int & score2)
{
    ostringstream convert;

    convert << score;

    string Result1 = " Score:" + convert.str();

    if(score2 != score)
    {
        DrawRectangle(75,5,20,20,"black",true);
        DrawString(Result1,0,0, "white", 30);
        score2 = score;
    }
    else
    {
        DrawString(Result1,0,0, "white", 30);
    }
}

void RunGame()       /*************************************************************************************************/
{
    int x0=CELL_SIZE,y0=CELL_SIZE,angle0=0, x=0, n=0;
    char choice;
    Food apple2;
    vector<follow> position(1);
    position[0] ={x0,y0};
    cout << "Choose up,down, left, or right arrow:";
    int score =0;
    int score2 =0;
    for( int i=3;i>0;i--)
    {
        x0=CELL_SIZE,y0=CELL_SIZE,angle0=0, x=0, n=0;
        position[0] ={x0,y0};
        foodp(apple2);
        while(x==0)
        {
            NewGame(i,score);
            Score2(score, score2);
            checkapple(apple2,x0,y0,position,score);
            DrawHead( x0, y0, angle0);
            Key(choice,angle0);
            Move(x0, y0, angle0);
            checkborder(x0,y0,x);
            addPosition(position,x0,y0);
            eatSelf(position,x, x0,y0);
            Pause(.12);
            Erase(position);
            n++;
        }
        DelEvery();
    }
    Score(score);
    DrawString("Game Over!",90,300,"red",100);
    DrawString("By Faris Alsaad",60,450,"yellow",80);
    Pause(10);
}                    /***********************************************************************************************/
