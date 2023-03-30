#pragma once
#include "Game.h"
#include "Net.h"

//class Control {
//public:
//	Control(NeuralNetwork& net) : net(net) {}
//	
//	int setInput(vector<float> input) {
//		auto out = net.goNet(input);
//		pair<float, int> temp{ 0, 0 };
//		for (size_t i = 0; i < out.size(); ++i) {
//			if (out[i] > temp.first) temp = { out[i], i };
//		}
//		return temp.second;
//	}
//	
//private:
//	NeuralNetwork& net;
//};



//#include <iostream>
//#include <chrono>
//#include "Window.h"
//#include "net.h"
//using namespace std;
//
//template<char symbol>
//bool PressingOne() {
//	static bool last = false;
//	bool pressing = (GetAsyncKeyState((unsigned short)symbol) & 0x8000);
//	return (pressing ? (!last ? last = true : false) : last = false);
//}
//
//const int BIAS_X = 2;
//const int WIDTH = 15, HEIGHT = 30;
//int field[HEIGHT][WIDTH] = { 0 };
//
//int FIGURES[7][4] =
//{
//	1,3,5,7, // I
//	2,4,5,7, // S
//	3,5,4,6, // Z
//	3,5,4,7, // T
//	2,3,5,7, // L
//	3,5,7,6, // J
//	2,3,4,5, // O
//};
//
//struct Point {
//	int x, y;
//} a[4], b[4];
//
//bool check() {
//	for (size_t i = 0; i < 4; ++i) {
//		auto x = a[i].x, y = a[i].y;
//		if (x < 0 || x >= WIDTH || y >= HEIGHT) return false;
//		else if (field[y][x]) return false;
//	}
//	return true;
//}
//
//void deleteLine() {
//	int k = HEIGHT - 1;
//	for (int i = HEIGHT - 1; i >= 0; --i) {
//		int count = 0;
//		for (size_t j = 0; j < WIDTH; j++) {
//			if (field[i][j]) ++count;
//			field[k][j] = field[i][j];
//		}
//		if (count < WIDTH) --k;
//	}
//}
//
//void game() {
//	Window window(WIDTH * BIAS_X - 1, HEIGHT);
//
//	auto tp1 = chrono::system_clock::now();
//	auto tp2 = chrono::system_clock::now();
//	float timer = 0, delay = 0.3, speed = 0.5;
//
//	int dx = 0, dy = 0;
//	bool rotate = false;
//	bool fearst = true;
//
//	while (true) {
//		tp2 = chrono::system_clock::now();
//		chrono::duration<float> elapsedTime = tp2 - tp1;
//		tp1 = tp2;
//		float fElapsedTime = elapsedTime.count();
//
//		if (PressingOne<'W'>()) rotate = true;
//		if (PressingOne<'A'>()) dx = -1;
//		if (PressingOne<'D'>()) dx = 1;
//		if (PressingOne<'S'>()) dy = 1;
//
//
//		if (rotate) {
//			Point p = a[1];
//			for (size_t i = 0; i < 4; ++i) {
//				int x = a[i].y - p.y;
//				int y = a[i].x - p.x;
//				a[i].x = p.x - x;
//				a[i].y = p.y + y;
//			}
//			if (!check()) for (size_t i = 0; i < 4; ++i) a[i] = b[i];
//		}
//
//		for (size_t i = 0; i < 4; ++i) {
//			b[i] = a[i];
//			a[i].x += dx;
//			a[i].y += dy;
//		}
//		if (!check()) for (size_t i = 0; i < 4; ++i) a[i] = b[i];
//		timer += (speed * 0.75f) * fElapsedTime;
//		if (timer > delay) {
//			for (size_t i = 0; i < 4; ++i) b[i] = a[i], a[i].y += 1;
//			if (!check()) {
//				int type = random(0, 6);
//				for (size_t i = 0; i < 4; ++i) {
//					auto [x, y] = b[i];
//					field[y][x] = 1;
//					a[i].x = FIGURES[type][i] % 2;
//					a[i].y = FIGURES[type][i] / 2;
//				}
//			}
//			timer = 0;
//			fearst = false;
//		}
//
//
//		/*-----RANDOM FIGURS-----*/
//		int type = random(0, 6);
//		if (fearst) {
//			for (size_t i = 0; i < 4; ++i) {
//				a[i].x = FIGURES[type][i] % 2;
//				a[i].y = FIGURES[type][i] / 2;
//			}
//			fearst = false;
//		}
//
//		deleteLine();
//
//		/*-----DRAW-----*/
//		window.clear();
//		for (size_t i = 0; i < HEIGHT; ++i) {
//			for (size_t j = 0; j < WIDTH; ++j) {
//				if (!field[i][j]) continue;
//				window.setPixel(j * BIAS_X, i, '#');
//			}
//		}
//
//		for (size_t i = 0; i < 4; ++i) {
//			int x = a[i].x * BIAS_X, y = a[i].y;
//			window.setPixel(x, y, '@');
//		}
//		window.display();
//
//		//////////////////////////////////////////////////
//		rotate = false;
//		dx = dy = 0;
//	}
//}