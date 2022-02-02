	#include<stdio.h>
	#include<conio.h>
	#include<windows.h>
		
		
	void gotoxy(int x , int y)
	{
		COORD c;
		c.X=x;
		c.Y=y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	}



	void box (int len , int bre , int x , int y)
	{
		int i;
		for(i=0 ; i<len ; i++)
		{
			gotoxy(x+i,y);
			printf("%c",205);
			gotoxy(x+i,y+bre);
			printf("%c",205);
		}
		for(i=0 ; i< bre ; i++)
		{
			gotoxy(x,y+i);
			printf("%c",186);
			gotoxy(x+len,y+i);
			printf("%c",186);	
		}
		gotoxy(x+len,y);
		printf("%c",187);
		gotoxy(x+len,y+bre);
		printf("%c",188);
		gotoxy(x,y);
		printf("%c",201);
		gotoxy(x,y+bre);
		printf("%c",200);
	}
		
		
		
	void SetColor(int ForgC)
	{
		WORD wColor;
		
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		
		if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
		{	                 
			 wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
			 SetConsoleTextAttribute(hStdOut, wColor);
		}
		return;
	}
