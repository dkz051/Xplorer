/*
	File Name: handler.cpp

	Window event handler for the game.
	------------------------------------------------------------
	Xplorer, yet another 2D jumping game
	Copyright (C) 2018 Chrogeek

	<https://github.com/Chrogeek/Xplorer>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "defs.h"
#include <d2d1.h>
#include <windows.h>
#include <wincodec.h>
#include "game.h"
#include "handler.h"
#include "utility.h"
#include "gameLevel.h"

//extern gameStage gameStages[maxStage + 1];
//extern int currentStage;
extern int currentChapter, currentLevel;
extern ID2D1Factory *d2dFactory;
extern ID2D1DCRenderTarget *mainRenderer;
extern IWICImagingFactory *imageFactory;
extern ID2D1Bitmap *bitmapBackground;
extern buttonUI *buttons[maxButton + 1];

extern bool isKeyDown[128];
extern gameHero hero;
extern UINT lastJumpTime;

extern gameManager gameMaster;

void gameTimer(HWND hwnd, UINT timerID) {
	if (currentChapter >= stageTutorial) {
		updateHero();
	}
	InvalidateRect(hwnd, nullptr, false);
	UpdateWindow(hwnd);
}

void initializeGame() {
//	gameStages[1].loadFromFile(L"levels/1.txt");
	currentChapter = stageMainMenu;
	gameMaster.load("./chapters");
}

void gameKeyDown(HWND hwnd, int keyCode) {
	if (!isInInterval(keyCode, 0, 128)) return;
	isKeyDown[keyCode] = true;
	if (currentChapter >= stageTutorial) {
		if (keyCode == VK_LEFT) hero.face = directionLeft, hero.lockX = false;
		else if (keyCode == VK_RIGHT) hero.face = directionRight, hero.lockX = false;
		else if (keyCode == jumpKey) {
			++hero.jumpCount;
			if (hero.jumpCount <= 2) { // we allow only two jumps in a row
				hero.lockY = false;
			//	hero.velocity += jumpVelocityDelta; // to be updated. this should not be the final acceleration scheme.
				lastJumpTime = timeGetTime();
				hero.velocity.vY = jumpStartVelocity.vY;
			}
		}
	}
}

void gameKeyUp(HWND hwnd, int keyCode) {
	if (!isInInterval(keyCode, 0, 128)) return;
	isKeyDown[keyCode] = false;
}

void gameMouseDown(HWND hwnd, int button, int X, int Y) {}

void gameMouseUp(HWND hwnd, int button, int X, int Y) {
	int buttonClicked = getClickedButtonID((double)X, (double)Y);
	switch (currentChapter) {
		case stageMainMenu:
		{
			if (buttonClicked == buttonExit) {
				PostQuitMessage(0);
			} else if (buttonClicked == buttonStart) {
				disableAllButtons();
				startLevel(0, 0);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

void gameMouseMove(HWND hwnd, int button, int X, int Y) {}

void renderWindow(HWND hwnd) {
	if (mainRenderer == nullptr) return;

	mainRenderer->BeginDraw();

	mainRenderer->Clear();
	switch (currentChapter) {
		case stageMainMenu:
		{
			mainRenderer->DrawBitmap(bitmapBackground, makeRectF(0, 0, windowClientWidth, windowClientHeight));
			buttonUI *btnStart = buttons[buttonStart], *btnExit = buttons[buttonExit];
			if (btnStart) btnStart->visible = true;
			if (btnExit) btnExit->visible = true;
			drawButton(btnStart);
			drawButton(btnExit);
			break;
		}
		default:
		{
			renderGame();
			break;
		}
	}

	mainRenderer->EndDraw();
}
