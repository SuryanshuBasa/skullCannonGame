/*--FINAL WORKING GAME SOURCE CODE--
--USED FOR REFERENCE ONLY--
--SURYANSHU BASA--
--16 JAN 2022--*/

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

#include"box.h" // my own header file to print box

int hits = 0; // hits
int sklife = 10; // skull lives
int time = 1000; // timer
char ch; 
int xc = 6 , yc = 23,tempx,tempy; // cannon coords
int xsk = 6 , ysk = 4 ,tempxsk,tempysk; // skull coords
int bulcount=0; // bullet count
int xb,yb,tempxb,tempyb; // bullet coords
int bul = 0; // bullet alive or dead key
int random; // randomiser to choose skull path
int open = 1; // cannon ready to fire key




void main()
{
	int key = 1,i,j=0;
	random = rand() % 2;
	gotoxy(12,15);
	printf(" E N T E R  F U L L  S C R E E N ");
	Sleep(5000);
	system("cls");
	screen0();
	screen1();
	screen2();
	Sleep(2000);
	while(time > 0 && key!= 0 && sklife != 0) // game loop conditions
	{
		if(kbhit())
		{
			ch = getch();
			if(ch == 27)
				key = 0;
			move(ch);
		}
		
		moveskull();
		travel();
		removebul();
		hitscan();
	
		
		gotoxy(18,30);
		printf("%3d",hits*10);
		gotoxy(53,30);
		printf("%3d",sklife);
		gotoxy(98,22);
		printf("%5d",time/10);
		if(open)
		{
			gotoxy(30,25);
			printf("                     ");
		}
		else
		{
			gotoxy(30,25);
			printf(" R E L O D I N G ");
		}
		
		Sleep(100);
		time--;
	}
		SetColor(4);
		gotoxy(25,12);
		printf("G A M E  O V E R");
		gotoxy(10,13);
		printf("P R E S S  A N Y  K E Y  T O  C O N T I N U E .....");
		getch();
} // main
	
void move(char ch)  // moving cannon using arrow keys
{
	int key=0;
	switch(ch)
	{
		case 72:{
			key = 1;
			make();
			break;
		}
		case 77:{
			key = 1;
			tempx = xc++;
			if(xc > 70)
				xc = 70;
			break;
		}
		case 75:{
			key = 1;
			tempx = xc--;
			if(xc < 6)
				xc = 6;
			break;
		}
		/*case 27:{
			key=1;
			exit(0);
			break;
		}*/
		default:{
			key = 0;
			break;
		}
	} // switch
	if(key) // if any arrow key is pressed and location of cannon is updated
	{
		gotoxy(tempx,tempy);
		printf(" ");
		gotoxy(xc,yc);
		printf("%c",30);
		tempx = xc;
		tempy = yc;
	}	
}

void moveskull() // randomised path for the skull
{
	tempxsk = xsk;
	tempysk = ysk;
	gotoxy(tempxsk,tempysk);
	printf(" ");
	if(random == 0)
	{
		xsk++;
		if(xsk > 70)
		{
			xsk = 6;
			random = rand() % 2;
		}
		ysk = 3 + rand() % 3;
	}
	if(random == 1)
	{
		xsk += 2;
		if(xsk > 70)
		{
			xsk = 6;
			random = rand() % 2;
		}
		ysk = 3 + rand() % 3;
		
	}
	gotoxy(xsk,ysk);
	printf("%c",2);
}

void make() // when up arrow is hit a bullet is added
{
	if(open) // check cannon ready to fire?
	{
		xb = xc;
		yb = yc-1;
		bul = 1; 	// bullet alive
	}
	open = 0; // cannon reloading
	
}

void travel() // bullet travel
{
	if(bul) // if bullet is alive
	{
		if(yb) // bullet travel
		{
			tempyb = yb--;
			if(yb <= 2)
			{
				open = 1; 
				yb = 0; 
				bul = 0;
			}
			gotoxy(xb,yb);
			printf(".");
			gotoxy(xb,tempyb);
			printf(" ");
			tempyb = yb;
		}
	}
	
}

void removebul() // cleaning bullets that dont connect
{
	int i;
	for(i=0 ; i<80 ;i++)
	{
		gotoxy(i,0);
		printf(" ");
	}
}

void hitscan() // logic for hitscanning // made a field around the skull so as to make it easier to hit
{
	if(bul) // check bul is alive
	{
		if(xb >= (xsk - 3) && xb <= xsk) // bullet in the left field of the skull
		{
			if(yb <= (ysk + 1) && yb  >= ysk) // vertical height 
			{
				gotoxy(xb,yb);
				printf(" ");
				yb=0;
				bul=0;
				open=1;
				hits++;sklife--;
				return;
			}
		}
		 if(xb >= xsk && xb < (xsk + 3)) // bullet in the right side of the skull
		{
			if(yb <= (ysk + 1) && yb  >= ysk) // vertical height 
			{
				gotoxy(xb,yb);
				printf(" ");
				yb=0;
				bul=0;
				open=1;
				hits++;sklife--;
				return;
			}
		}
	}
	
}

void screen0() // opening page
{
	SetColor(5);
	box(130,25,0,3);
	gotoxy(40,2);
	printf(" S K U L L  C A N N O N  :  T H E  G A M E ");
	SetColor(9);
	gotoxy(45,5);
	printf(" H O W  T O  P L A Y ");
	gotoxy(6,7);
	printf("-> CONTROLS WILL BE DISPLAYED ON THE RIGHT SIDE OF THE CONSOLE ");
	gotoxy(6,9);
	printf("-> THE SKULL WILL BE MOVING IN A RANDOM PATH ON TOP OF THE SCREEN ");
	gotoxy(6,11);
	printf("-> THE CANNON ON THE BOTTOM IS CONTROLLED BY YOU AND UR AIM IS TO SHOOT AT THE SKULL TO GATHER POINTS IN LIMITED TIME ");
	gotoxy(10,15);
	printf("%c%c%c=>REMEMBER THE CANNON HAS A %cRELOAD TIME%c SO PLACE YOUR CANNON STRATEGICALLY AND FIRE AT THE SKULL<=%c%c%c",35,35,35,'"','"',35,35,35);
	gotoxy(25,19);
	printf("P R E S S  E N T E R  T O  P L A Y  %c",16);
	gotoxy(1,25);
	printf("improvements will be done and added in due time");
	gotoxy(100,25);
	printf("S U R Y A N S H U  B A S A");
	getch();
	system("cls");
}

void screen1() // game HUD to provide instructions
{
	SetColor(9);
	box(80,25,0,1);
	box(30,25,90,1);
	gotoxy(97,2);
	printf(" C O N T R O L S ");
	gotoxy(94,5);
	printf("RIGHT ARROW -> move right ");
	gotoxy(94,7);
	printf("LEFT ARROW -> move left ");
	gotoxy(94,9);
	printf("UP ARROW -> shoot bullets ");
	gotoxy(96,13);
	printf("PRESS ESC TO EXIT ");
	gotoxy(95,20);
	printf("T I M E  L E F T");
	SetColor(15);
}
void screen2() // game HUD to show points
{

	SetColor(13);
	box(120,6,0,27);
	gotoxy(8,30);
	printf("H I T S : ");
	gotoxy(30,30);
	printf("S K U L L  L I V E S :");
	gotoxy(67,30);
	printf(" M I N I  G A M E  B Y  S U R Y A N S H U  B A S A ");
	SetColor(15);
}
