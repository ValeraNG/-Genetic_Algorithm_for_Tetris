#pragma once
#include <iostream>
#include <stdio.h>
#include <windows.h>
using namespace std;

class Window {
public: 
	Window(size_t width, size_t height) {
		this->width = width;
		this->height = height;
		_COORD coord;
		coord.X = width;
		coord.Y = height;
		_SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Right = width - 1;
		Rect.Bottom = height - 1;
		HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleScreenBufferSize(Handle, coord);
		SetConsoleWindowInfo(Handle, TRUE, &Rect);

		screen = new wchar_t[width * height];
		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
		dwBytesWritten = 0;
	}

	void setPixel(size_t x, size_t y, char c) {
		screen[y * width + x * biasX] = c;
	}
	void clear(char c = ' ') {
		for (size_t i = 0; i < height; ++i) {
			for (size_t j = 0; j < width; ++j) {
				screen[i * width + j] = c;
			}
		}
	}
	void display() {
		WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
	}
	void setBiasX(uint8_t bias) { biasX = bias; }

	~Window() { delete[] screen; }

private:
	uint8_t biasX = 1;
	size_t width, height;

	wchar_t* screen = nullptr;
	HANDLE hConsole;
	DWORD dwBytesWritten = 0;
};