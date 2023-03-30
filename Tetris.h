#pragma once
#include <iostream>
#include <random>
using namespace std;

int randomFigur(int a, int b) {
	static mt19937 gen(random_device{}());
	uniform_int_distribution dist(a, b);
	return dist(gen);
}

enum CELL {
	STOCKED = -1,
	EMPTY = 0,
	CURENT = 1
};

class Tetris {
public:
	Tetris(size_t width, size_t height) {
		this->width_ = width;
		this->height_ = height;
		field = new int* [height];
		for (size_t i = 0; i < height; ++i) field[i] = new int[width] { 0 };
		generationFigure<true>();
	}

	void update() {
		rotateFigur();
		move(dx, 0);
		move(0, dy);
		goDown();
		deleteLine();
		zeroing();
	}
	bool endGame() { return end_; }

	/*-----move-----*/
	void down() { dy = 1; }
	void right() { dx = 1; }
	void left() { dx = -1; }
	void rotate() { rotate_ = true; }

	/*-----for window-----*/
	const auto& getFigur() { return a; }
	auto getSizeFold() { return make_pair(width_, height_); }
	bool emptyCell(size_t x, size_t y) { return !field[y][x]; }
	const auto& getField(size_t x, size_t y) { return field[y][x]; }

	~Tetris() {
		for (size_t i = 0; i < height_; ++i) delete[] field[i];
		delete[] field;
	}

private:
	bool check() {
		for (size_t i = 0; i < 4; ++i) {
			auto x = a[i].x, y = a[i].y;
			if (x < 0 || width_ <= x || height_ <= y) return false;
			else if (field[y][x]) return false;
		}
		return true;
	}
	void deleteLine() {
		int k = height_ - 1;
		for (int i = height_ - 1; i >= 0; --i) {
			int count = 0;
			for (size_t j = 0; j < width_; ++j) {
				if (field[i][j]) ++count;
				field[k][j] = field[i][j];
			}
			if (count < width_) --k;
		}
	}

	/*-----logik func-----*/
	template<bool First>
	void generationFigure() {
		uint8_t type = randomFigur(0, 6);
		for (size_t i = 0; i < SIZEFIGUR; ++i) {
			auto& [x, y] = a[i];
			x = FIGURES[type][i] % 2;
			y = FIGURES[type][i] / 2;
			if (field[y][x]) end_ = true;
			if constexpr (!First) {
				auto [x, y] = b[i];
				field[y][x] = (int)CELL::STOCKED;
			}
		}
	}
	void rotateFigur() {
		if (!rotate_) return;
		Point p = a[1];
		for (size_t i = 0; i < SIZEFIGUR; ++i) {
			b[i] = a[i];
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!check()) copy(begin(b), end(b), begin(a));
	}
	void move(int dx, int dy) {
		if (!dx && !dy) return;
		for (size_t i = 0; i < SIZEFIGUR; ++i) {
			b[i] = a[i];
			a[i].x += dx;
			a[i].y += dy;
		}
		if (!check()) copy(begin(b), end(b), begin(a));
	}
	void goDown() {
		if (tempY < DELAY) return;
		for (size_t i = 0; i < SIZEFIGUR; ++i) b[i] = a[i], a[i].y += 1;
		if (!check()) generationFigure<false>();
		tempY = 0;
	}
	void zeroing() {
		dx = dy = 0;
		rotate_ = false;
		++tempY;
	}

	/*-----logik-----*/
	struct Point { int x, y; } a[4], b[4];
	int dx = 0, dy = 0;
	bool rotate_ = false;
	int tempY = 0;
	bool end_ = false;

	/*-----config-----*/
	size_t width_, height_;
	int** field = nullptr;

	static const int DELAY;
	static const int SIZEFIGUR;
	static const int FIGURES[7][4];
};

const int Tetris::DELAY = 3;
const int Tetris::SIZEFIGUR = 4;
const int Tetris::FIGURES[7][4]{
		1,3,5,7, // I
		2,4,5,7, // S
		3,5,4,6, // Z
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
};
