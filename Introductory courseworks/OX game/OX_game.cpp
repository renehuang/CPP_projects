#include "ccc_win.h"
#include <string>

using namespace std;


//create a list of char to record the activity of each box
char box[10] = { 'o','1','2','3','4','5','6','7','8','9' };

int ccc_win_main() {
	//graph the grid for this game
	Point top_left(-3, 3);
	Point top_right(3, 3);
	Point bottom_left(-3, -3);

	Line horizontal(top_left, top_right);
	Line vertical(top_left, bottom_left);

	cwin << horizontal << vertical;

	for (int i = 1; i <= 3; i++) {

		horizontal.move(0, -2);
		vertical.move(2, 0);

		cwin << horizontal << vertical;
	}

	//user input click
	for (int j = 1; j <= 9; j++) {
		Point click = cwin.get_mouse("Please click inside the box you want.");
		int click_x = click.get_x();
		int click_y = click.get_y();

		//initialize the center point
		Point center(0, 0);

		//to find out which box the user clicked, and move the center point to the box's center
		switch (click_y) {
		case 2:
		case 1:
			switch (click_x) {
			case -2:
			case -1:
				center.move(-2, 2);
				box[1] = 'y';
				break;
			case 0:
				center.move(0, 2);
				box[2] = 'y';
				break;
			case 1:
			case 2:
				center.move(2, 2);
				box[3] = 'y';
			}
			break;
		case 0:
			switch (click_x) {
			case -2:
			case -1:
				center.move(-2, 0);
				box[4] = 'y';
				break;
			case 0:
				center.move(0, 0);
				box[5] = 'y';
				break;
			case 1:
			case 2:
				center.move(2, 0);
				box[6] = 'y';
			}
			break;
		case -1:
		case -2:
			switch (click_x) {
			case -2:
			case -1:
				center.move(-2, -2);
				box[7] = 'y';
				break;
			case 0:
				center.move(0, -2);
				box[8] = 'y';
				break;
			case 1:
			case 2:
				center.move(2, -2);
				box[9] = 'y';
			}
			break;
		}

		//find out whether should graph 'X' or 'O', and graph at the box clicked.
		if (j % 2) {
			Point LT(center.get_x() - 1, center.get_y() + 1);
			Point RT(center.get_x() + 1, center.get_y() + 1);
			Point LB(center.get_x() - 1, center.get_y() - 1);
			Point RB(center.get_x() + 1, center.get_y() - 1);
			Line X1(LT, RB);
			Line X2(RT, LB);
			cwin << X1 << X2;
			for (int k = 1; k <= 9; k++) {
				if (box[k] == 'y') {
					box[k] = 'X';
					break;
				}
			}
		}
		else {
			Circle O(center, 1);
			cwin << O;
			for (int k = 1; k <= 9; k++) {
				if (box[k] == 'y') {
					box[k] = 'O';
					break;
				}

			}
		}
		
		//Test all the possibilities of winning
		if (box[1] == box[2] && box[2] == box[3]) {
			Point A(-3, 2);
			Point B(3, 2);
			Line Win_1(A, B);
			j = 10;
			if (box[1] == 'X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}
		else if (box[4] == box[5] && box[5] == box[6]) {
			Point A(-3, 0);
			Point B(3, 0);
			Line Win_1(A, B);
			j = 10;
			if (box[4] =='X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}
		else if (box[7] == box[8] && box[8] == box[9]) {
			Point A(-3, -2);
			Point B(3, -2);
			Line Win_1(A, B);
			j = 10;
			if (box[7] == 'X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}
		else if (box[1] == box[4] && box[4] == box[7]) {
			Point A(-2, 3);
			Point B(-2, -3);
			Line Win_1(A, B);
			j = 10;
			if (box[1] == 'X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}
		else if (box[2] == box[5] && box[5] == box[8]) {
			Point A(0, 3);
			Point B(0, -3);
			Line Win_1(A, B);
			j = 10;
			if (box[2] == 'X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}
		else if (box[3] == box[6] && box[6] == box[9]) {
			Point A(2, 3);
			Point B(2, -3);
			Line Win_1(A, B);
			j = 10;
			if (box[3] == 'X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}
		else if (box[1] == box[5] && box[5] == box[9]) {
			Point A(-3, 3);
			Point B(3, -3);
			Line Win_1(A, B);
			j = 10;
			if (box[1] == 'X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}
		else if (box[3] == box[5] && box[5] == box[7]) {
			Point A(3, -3);
			Point B(-3, 3);
			Line Win_1(A, B); 
			j = 10;
			if (box[3] == 'X') {
				cwin << Win_1 << Message(B, "Player X wins");
			}
			else {
				cwin << Win_1 << Message(B, "Player O wins");
			}
		}

	}

	return 0;
}