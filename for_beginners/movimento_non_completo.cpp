#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<windows.h>

using namespace std;
void gotoxy (int x, int y) 
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
main () 
{
int x=50, y=60;
char tasto;
do 
{
tasto=getch();	
if (tasto == 'w') y--;
    if (x!=20 || y!=21); 
if (tasto == 'a') x--;
    if (x!=20 || y!=21);
if (tasto == 'd') x++;
    if (x!=20 || y!=21);
if (tasto == 's') y++;  
    if (x!=20 || y!=21);
gotoxy(x,y); 
cout <<"+";
} while (x!=160);
}
