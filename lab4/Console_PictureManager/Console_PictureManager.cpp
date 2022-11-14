// Console_PictureManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../PictureManager/Designer/Designer.h"
#include "../PictureManager/Painter/Painter.h"
#include "../PictureManager/Canvas/Canvas.h"

int main()
{
	std::cout << "Enter input file name: ";
	std::string inputFileName;
	std::cin >> inputFileName;
	std::cout << "Enter output file name: ";
	std::string outputFileName;
	std::cin >> outputFileName;
	std::ifstream inputFile(inputFileName);
	Canvas canvas(800, 600, "shapes");
	Painter painter;
	Designer designer;
	painter.DrawPicture(designer.CreateDraft(inputFile), canvas);

	canvas.CaptureShapes(outputFileName);
}
