#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <stdlib.h>


//read all this, its important
/*
the function:

VECTOR 1
	characters
VECTOR 2
	character coords(integers, x is how far right(starts at 0), y is how far down(starts at 0 as well))
CHAR 1
	border material (leave a space if none)
VECTOR 3
	colors (see below)
BOOL 1
  whether or not colors are enabled (doubles speed)
*/

//COLORS LIST
//1: Blue
//2: Green
//3: Cyan
//4: Red
//5: Purple
//6: Yellow (Dark)
//7: Default white
//8: Gray/Grey
//9: Bright blue
//10: Brigth green
//11: Bright cyan
//12: Bright red
//13: Pink/Magenta
//14: Yellow
//15: Bright white

//Numbers after 15 include background colors:

//16 - 31 - blue bg
//32 - 47 - green bg
//48 - 63 - cyan bg
//64 - 79 - red bg
//80 - 95 - purple bg
//96 - 111 - yellow bg
//112 - 127 - white bg
//128 - 143 - gray bg
//144 - 159 - bright blue bg
//160 - 175 - bright green bg
//176 - 191 - bright cyan bg
//192 - 207 - bright red bg
//208 - 223 - magenta bg
//224 - 239 - beige bg
//240 - 255 - bright white bg

//REQUIRED:
//put frame size here:
const int width = 110;
const int height = 55;


//THE ONLY FUNCTION THAT SHOULD BE DEFINED IN YOUR MAIN PROGRAM IS refresh


bool firsttime = 1;

//the useable functions include refresh and endservice. ALL OTHER FUNCTIONS ARE SELF-CONTAINED.

char lastframe[width][height] = {};

char ipbuffer[width][height] = {}; //ip as in Itchy Penis (ALL RIGHTS RESERVED)

int lastcolor[width][height] = {}; //check if last frame color is same as current frame color
int currentcolor[width][height]; //same

HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE); //handle for console output

int col = 0;     //color, used in computational comparison saving

void Color(const int& color)
{
	SetConsoleTextAttribute(hand, color);
}

void ShowConsoleCursor(const bool& showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(hand, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(hand, &cursorInfo);
}

COORD cord = {}; //used so i don't have to reinit the cursor coords every time


void refresh(std::vector<char> chars, std::vector<int> cords, char bord, std::vector<int> colors, bool colorful) { //color background

	if (firsttime == 1) { //simply to set LastFrame and CurrentFrame to empty, so the first frame is entirely refreshed
		SetConsoleTitleW(L"Console Graphic Test"); //SET NAME OF CONSOLE
		firsttime = 0;
		for (int i = 0; i < height; i++) {
			for (int e = 0; e < width; e++) {
				lastframe[e][i] = {};
				lastcolor[e][i] = 15;
				ipbuffer[e][i] = {};
				col = 15;
			}
		}
	}
	ShowConsoleCursor(false);
	for (int cordparse = 0; cordparse < cords.size(); cordparse += 2) { //parse through coordinates and lay them out in a frame
		if (cords[cordparse] >= 0 && cords[cordparse] < width && cords[cordparse + 1] >= 0 && cords[cordparse + 1] < height) { //cordparse+1 is y. all this checks array range
			ipbuffer[cords[cordparse]][cords[cordparse + 1]] = chars[cordparse / 2];
			currentcolor[cords[cordparse]][cords[cordparse + 1]] = colors[cordparse / 2];
		}
	}
	if (bord != ' ') { //FILL BORDER IF BORDER IS NOT GONE
		for (int one = 0; one < height; one++) { //X is 0, Y going up
			ipbuffer[0][one] = bord;
			currentcolor[0][one] = 15;
		}
		for (int two = 0; two < width; two++) { //X going right, Y is maximum
			ipbuffer[two][height - 1] = bord;
			currentcolor[two][height - 1] = 15;
		}
		for (int three = height - 1; three >= 0; three--) { //X maximum, Y back down
			ipbuffer[width - 1][three] = bord;
			currentcolor[width - 1][three] = 15;
		}
		for (int four = width - 1; four >= 0; four--) { //X going left, Y is 0
			ipbuffer[four][0] = bord;
			currentcolor[four][0] = 15;
		}
	}
	for (int a = 0; a < height; a++) { //a is Y, going down
		for (int b = 0; b < width; b++) { //b is X, going right
			if (ipbuffer[b][a] != (lastframe[b][a]) || currentcolor[b][a] != lastcolor[b][a]) {
				cord.X = b;
				cord.Y = a;
				SetConsoleCursorPosition(hand, cord);
				if (colorful == 1) {
					if (currentcolor[b][a] != lastcolor[b][a] && currentcolor[b][a] != col || currentcolor[b][a] != col) {
						Color(currentcolor[b][a]);
						col = currentcolor[b][a];
					}
				}
				putchar(ipbuffer[b][a]);
			}
			lastcolor[b][a] = currentcolor[b][a];
			currentcolor[b][a] = {};

			lastframe[b][a] = ipbuffer[b][a];
			ipbuffer[b][a] = ' ';
		}
	}
}


void endservice() { // ends program, anykeycontinue is out of view
	COORD cord; cord.X = 0; cord.Y = height + 1;
	SetConsoleCursorPosition(hand, cord);
	Color(15);
	system("pause");
}
