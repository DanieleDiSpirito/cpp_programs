#include <iostream>
#include <synchapi.h>
#include <conio.h>
#include <windows.h>
#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>

using namespace std;

pair<int, int> UP    		= make_pair(0, -1);
pair<int, int> DOWN  		= make_pair(0, 1);
pair<int, int> RIGHT 		= make_pair(1, 0);
pair<int, int> LEFT  		= make_pair(-1, 0);
pair<int, int> STAY  		= make_pair(0, 0);
pair<int, int> LEFT_GAME 	= make_pair(-1, -1);
pair<int, int> apple		= make_pair(rand() % 30, rand() % 15);
bool appleEaten = false;
vector<pair <int, int>> body {
	make_pair(10, 10), 
	make_pair(10, 9),
	make_pair(10, 8),
	make_pair(10, 7),
	make_pair(10, 6),
	make_pair(10, 5),
};
pair<int, int> dir = STAY;

void draw() { // THERE COULD BE PROBLEMS WHEN y = 0 OR x = 0
	system("cls");
	vector<int> y {};
	for(int i = 0; i < body.size(); i++) {
		y.push_back(body.at(i).second);
	}
	y.push_back(apple.second);
	sort(y.begin(), y.end());
	int prev_y = 0, prev_x, this_y, this_x;
	for(int i = 0; i < y.size(); i++) {
		if(i > 0) {
			prev_y = y.at(i-1);
		}
		this_y = y.at(i);
		for(int j = 0; j < this_y - prev_y; j++) {
			cout << "\n";
		}
		if(this_y != prev_y || prev_y == 0) { // <-- HERE!
			vector<int> x {};
			for(int j = 0; j < body.size(); j++) {
				if(body.at(j).second == this_y) {
					x.push_back(body.at(j).first);
				}
			}
			if(apple.second == this_y) {
				x.push_back(apple.first);
			}
			sort(x.begin(), x.end());
			prev_x = 0;
			for(int k = 0; k < x.size(); k++) {
				if(k > 0) {
					prev_x = x.at(k-1);
				}
				this_x = x.at(k);
				for(int l = 0; l < this_x - prev_x - 1; l++) {
					cout << " ";
				}
				if(this_x == apple.first && this_y == apple.second) {
					cout << "M";
				}
				else {
					cout << "S";
				}
			}
		}	
	}
}

void input() {
	if(_kbhit()) {
		switch(_getch()) {
			case 'w': case 'W':
				dir = UP;
				break;
			case 's': case 'S':
				dir = DOWN;
				break;
			case 'a': case 'A':
				dir = LEFT;
				break;
			case 'd': case 'D':
				dir = RIGHT;
				break;
			case 'l': case 'L':
				dir = LEFT_GAME;
				break;
		}
	}
}

void addApple() {
	apple = make_pair(rand() % 30, rand() % 15);
}

void chCoord() {
	if(appleEaten) {
		addApple();
		appleEaten = false;
	}
	Sleep(150);
	for(int i = body.size()-1; i > 0; i--) {
		body.at(i) = body.at(i-1);
	}
	if(dir != LEFT_GAME) {
		body.at(0) = make_pair(body.at(0).first + dir.first, body.at(0).second + dir.second);
	}
}

void growSnake() {
	body.push_back(make_pair(body.at(0).first - dir.first, body.at(0).second - dir.second));
}

void checkApple() {
	if(body.at(0).first == apple.first && body.at(0).second == apple.second) {
		appleEaten = true;
		growSnake();
	}
}

void checkGame() {
	if(body.at(0).first < 0 || body.at(0).second < 0) {
		dir = LEFT_GAME;
	}
}

int main() { 
	srand(time(NULL));
	cout << "Press any command to start...";
	getch();
	system("cls");
	while(dir != LEFT_GAME) {
		draw();
		input();
		chCoord();
		checkApple();
		checkGame();
	}
	cout << endl << "YOU LOST!";
	return 0;
}
