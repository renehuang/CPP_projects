#include "ccc_win.h"
#include <time.h>

//function for drawing pumpkin
void drawPumpkin(Point center, double scale) {
	Circle Pumpkin(center, 1.0*scale);
	double center_x = center.get_x();
	double center_y = center.get_y();
	Point N1(center_x+0*scale, center_y+0.1*scale);
	Point N2(center_x + 0.1*scale, center_y -0.1*scale);
	Point N3(center_x -0.1*scale, center_y -0.1*scale);
	Line nose1(N1, N2);
	Line nose2(N2, N3);
	Line nose3(N1, N3);
	Point LE1(center_x -0.3*scale, center_y + 0.2*scale);
	Point LE2(center_x -0.7*scale, center_y + 0.2*scale);
	Point LE3(center_x -0.45*scale, center_y + 0.5*scale);
	Line lefteye1(LE1, LE2);
	Line lefteye2(LE2, LE3);
	Line lefteye3(LE3, LE1);
	Point RE1(center_x+0.3*scale, center_y + 0.2*scale);
	Point RE2(center_x + 0.7*scale, center_y + 0.2*scale);
	Point RE3(center_x + 0.45*scale, center_y + 0.5*scale);
	Line righteye1(RE1, RE2);
	Line righteye2(RE2, RE3);
	Line righteye3(RE3, RE1);
	Point M1(center_x + 0.2*scale, center_y -0.4*scale);
	Point M2(center_x + 0.2*scale, center_y -0.5*scale);
	Point M3(center_x + 0.4*scale, center_y -0.5*scale);
	Point M4(center_x + 0.4*scale, center_y -0.4*scale);
	Point M5(center_x + 0.7*scale, center_y -0.3*scale);
	Point M6(center_x + 0.5*scale, center_y -0.7*scale);
	Point M7(center_x + 0.1*scale, center_y -0.7*scale);
	Point M8(center_x + 0.1*scale, center_y -0.6*scale);
	Point M9(center_x -0.1*scale, center_y-0.6*scale);
	Point M10(center_x -0.1*scale, center_y -0.7*scale);
	Point M11(center_x -0.5*scale, center_y -0.7*scale);
	Point M12(center_x -0.7*scale, center_y -0.3*scale);
	Point M13(center_x -0.4*scale, center_y -0.4*scale);
	Point M14(center_x -0.4*scale, center_y -0.5*scale);
	Point M15(center_x -0.2*scale, center_y -0.5*scale);
	Point M16(center_x -0.2*scale, center_y -0.4*scale);
	Line mouse1(M1, M2);
	Line mouse2(M2, M3);
	Line mouse3(M3, M4);
	Line mouse4(M4, M5);
	Line mouse5(M5, M6);
	Line mouse6(M6, M7);
	Line mouse7(M7, M8);
	Line mouse8(M8, M9);
	Line mouse9(M9, M10);
	Line mouse10(M10, M11);
	Line mouse11(M11, M12);
	Line mouse12(M12, M13);
	Line mouse13(M13, M14);
	Line mouse14(M14, M15);
	Line mouse15(M15, M16);
	Line mouse16(M16, M1);
	Point T1(center_x -0.1*scale, center_y+1.0 * scale);
	Point T2(center_x+0.1*scale, center_y + 1.0 * scale);
	Point T3(center_x -0.1*scale, center_y + 1.4*scale);
	Point T4(center_x+0.1*scale, center_y + 1.4*scale);
	Line top1(T1, T3);
	Line top2(T3, T4);
	Line top3(T4, T2);
	cwin << Pumpkin;
	cwin << nose1 << nose2 << nose3;
	cwin << lefteye1 << lefteye2 << lefteye3;
	cwin << righteye1 << righteye2 << righteye3;
	cwin << mouse1 << mouse2 << mouse3 << mouse4 << mouse5 << mouse6 << mouse7 << mouse8 << mouse9 << mouse10 << mouse11 << mouse12 << mouse13 << mouse14 << mouse15 << mouse16;
	cwin << top1 << top2 << top3;
}

//function for drawing bird
//if the pumpkin is at the right side of the bird, then we draw bird whose mouse points to the right
void drawrightBird(Point rightbird) {
	double rightbird_x = rightbird.get_x();
	double rightbird_y = rightbird.get_y();
	Circle body(rightbird, 1.5*0.5);
	Point E(rightbird_x+0.5*0.5, rightbird_y + 0.5*0.5);
	Circle eye(E, 0.7*0.5);
	Point E1(rightbird_x + 0.75*0.5, rightbird_y + 0.75*0.5);
	Point W1(rightbird_x -1 * 0.5, rightbird_y + 0.25*0.5);
	Point W2(rightbird_x -2 * 0.5, rightbird_y + 0.25*0.5);
	Point W3(rightbird_x -1 * 0.5, rightbird_y -0.75*0.5);
	Line Wing1(W1, W2);
	Line Wing2(W2, W3);
	Point M1(rightbird_x + 1 * 0.5, rightbird_y -0.05*0.5);
	Point M2(rightbird_x + 2.25*0.5, rightbird_y -0.05*0.5);
	Point M3(rightbird_x + 1 * 0.5, rightbird_y -0.175*0.5);
	Point M4(rightbird_x + 2.25*0.5, rightbird_y -0.175*0.5);
	Point M5(rightbird_x + 2 * 0.5, rightbird_y -0.175*0.5);
	Point M6(rightbird_x + 1 * 0.5, rightbird_y -0.3*0.5);
	Point M7(rightbird_x + 2 * 0.5, rightbird_y -0.3*0.5);
	Line Mouse1(M1, M2);
	Line Mouse2(M2, M4);
	Line Mouse3(M4, M3);
	Line Mouse4(M1, M6);
	Line Mouse5(M6, M7);
	Line Mouse6(M7, M5);
	cwin << body << eye << E1 << Wing1 << Wing2 << Mouse1 << Mouse2 << Mouse3 << Mouse4 << Mouse5 << Mouse6;
}

//if the pumpkin is at the left side of the bird, then we draw bird whose mouse points to the left
void drawleftBird(Point leftbird) {
	double leftbird_x = leftbird.get_x();
	double leftbird_y = leftbird.get_y();
	Circle body(leftbird, 1.5*0.5);
	Point E(leftbird_x - 0.5*0.5, leftbird_y + 0.5*0.5);
	Circle eye(E, 0.7*0.5);
	Point E1(leftbird_x - 0.75*0.5, leftbird_y + 0.75*0.5);
	Point W1(leftbird_x + 1 * 0.5, leftbird_y + 0.25*0.5);
	Point W2(leftbird_x + 2 * 0.5, leftbird_y + 0.25*0.5);
	Point W3(leftbird_x + 1 * 0.5, leftbird_y - 0.75*0.5);
	Line Wing1(W1, W2);
	Line Wing2(W2, W3);
	Point M1(leftbird_x - 1 * 0.5, leftbird_y - 0.05*0.5);
	Point M2(leftbird_x - 2.25*0.5, leftbird_y - 0.05*0.5);
	Point M3(leftbird_x - 1 * 0.5, leftbird_y - 0.175*0.5);
	Point M4(leftbird_x - 2.25*0.5, leftbird_y - 0.175*0.5);
	Point M5(leftbird_x - 2 * 0.5, leftbird_y - 0.175*0.5);
	Point M6(leftbird_x - 1 * 0.5, leftbird_y - 0.3*0.5);
	Point M7(leftbird_x - 2 * 0.5, leftbird_y - 0.3*0.5);
	Line Mouse1(M1, M2);
	Line Mouse2(M2, M4);
	Line Mouse3(M4, M3);
	Line Mouse4(M1, M6);
	Line Mouse5(M6, M7);
	Line Mouse6(M7, M5);
	cwin << body << eye << E1 << Wing1 << Wing2 << Mouse1 << Mouse2 << Mouse3 << Mouse4 << Mouse5 << Mouse6;
}

void pause(int x)
{
	clock_t goal = x + clock();
	while (goal > clock());
}

int ccc_win_main() {

	string response = "yes";

	while (response == "yes" || response == "Yes") {

		Point bird = cwin.get_mouse("Please click a point");
		Point pumpkin = cwin.get_mouse("Please click another point");
		double bird_x = bird.get_x();
		double bird_y = bird.get_y();
		double pumpkin_x = pumpkin.get_x();
		double pumpkin_y = pumpkin.get_y();

		//change the size of pumpkin and let bird move towards pumpkin
		for (double i = 0; i < 20; i++) {
			drawPumpkin(pumpkin, 1.0 + i*0.1);
			bird = Point(bird_x + (pumpkin_x - bird_x) / 20 * i, bird_y + (pumpkin_y - bird_y) / 20 * i);
			if (bird_x < pumpkin_x) {
				drawrightBird(bird);
			}
			else {
				drawleftBird(bird);
			}
			
			pause(100);
			cwin.clear();
		}
		Point O(0, 0);
		cwin << Message(pumpkin, "Happy Halloween!");

		//get response from the user
		response = cwin.get_string(" Do you want to play one more time? yes/no");
		cwin.clear();
	}
	return 0;
}