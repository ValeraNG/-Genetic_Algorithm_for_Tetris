#pragma once
#include <iostream>
#include "Window.h"
#include "Tetris.h"
#include "Net.h"
using namespace std;

template<char symbol>
bool PressingOne() {
	static bool last = false;
	bool pressing = (GetAsyncKeyState((unsigned short)symbol) & 0x8000);
	return (pressing ? (!last ? last = true : false) : last = false);
}

class Control {
public:
	Control(NeuralNetwork& net) : net(net) {}

	int setInput(vector<float> input) {
		auto out = net.goNet(input);
		pair<float, int> temp{ 0, 0 };
		for (size_t i = 0; i < out.size(); ++i) {
			if (out[i] > temp.first) temp = { out[i], i };
		}
		return temp.second;
	}

private:
	NeuralNetwork& net;
};


class Game {
public:
	Game(size_t widthG, size_t heightG) : tetris(widthG, heightG) {}
	static void createWindow(size_t widthW, size_t heightW, uint8_t bias) {
		widthW = widthW * bias - 1;
		window = new Window(widthW, heightW);
		window->setBiasX(bias);
	}

	template<bool Test = false>
	auto run() {
		while (!tetris.endGame()) {
			eventHantler();
			update();
			if constexpr (Test) {
				render();
				Sleep(50); ///test!!!!
			}
		}
	}

	auto getInput() {
		auto [w, h] = tetris.getSizeFold();
		vector input(w * h, 0.f);
		for (size_t i = 0; i < h; ++i) {
			for (size_t j = 0; j < w; ++j) {
				input[i * w + j] = tetris.getField(j, i);
			}
		}
		for (auto point : tetris.getFigur()) {
			auto [x, y] = point;
			input[y * w + x] = 1;
		}
		return input;
	}
	void setControl(NeuralNetwork& net) {
		control = new Control(net);
	}

private:
	void eventHantler() {
		int result = control->setInput(getInput());

		switch (result)
		{
		case 0:  tetris.rotate(); break;
		case 1:  tetris.left(); break;
		case 2:  tetris.right(); break;
		case 3:  tetris.down(); break;
		};
		//if (PressingOne<'W'>()) tetris.rotate();
		//if (PressingOne<'A'>()) tetris.left();
		//if (PressingOne<'D'>()) tetris.right();
		//if (PressingOne<'S'>()) tetris.down();
	}
	void update() {
		tetris.update();
	}
	void render() {
		window->clear();
		for (auto point : tetris.getFigur()) {
			auto [x, y] = point;
			window->setPixel(x, y, '@');
		}
		auto [w, h] = tetris.getSizeFold();
		for (size_t i = 0; i < h; ++i) {
			for (size_t j = 0; j < w; ++j) {
				bool empty = tetris.emptyCell(j, i);
				if (!empty) window->setPixel(j, i, '#');
			}
		}
		window->display();
	}

	/*-----components-----*/
	static Window* window;
	Tetris tetris;
	Control* control;

	/*-----logik-----*/
	float score = 0;
};
Window* Game::window = nullptr;