/*
	File Name: global.cpp

	This file defines global variables.
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

#include <d2d1.h>
#include <dwrite.h>
#include <map>
#include <vector>
#include "defs.h"
#include "game.h"
#include "utility.h"
#include <windows.h>
#include <wincodec.h>
using namespace std;

int currentStage;

buttonUI *buttons[maxButton + 1];
gameStage gameStages[maxStage + 1];

ID2D1Factory *d2dFactory = NULL;
IWICImagingFactory *imageFactory = NULL;
IDWriteFactory *writeFactory = NULL;
IDWriteTextFormat *textFormatNormal = NULL;
ID2D1DCRenderTarget *renderTarget = NULL;
ID2D1Bitmap *bkgImage = NULL, *wallImage = NULL, *heroImage = NULL;
ID2D1Bitmap *bitmapBackground = NULL;
ID2D1SolidColorBrush *brushBlack = NULL;

float dpiX, dpiY;

int heroDirection;
int jumpCount;
//float heroVelocityY;
//float heroX, heroY;
pointVector heroPosition, heroVelocity;
XplorerDirection face;
bool isKeyDown[128];
