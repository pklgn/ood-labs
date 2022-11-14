#pragma once
#include "../shape_drawing_lib/shape_drawing_lib.hpp"
#include "../modern_graphics_lib/modern_graphics_lib.hpp"
#include "../adapter/ModernGraphicsRendererAdapter.hpp"

namespace app
{
void PaintPicture(shape_drawing_lib::CanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	Triangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	Rectangle rectangle({ 30, 40 }, 18, 24);

	// TODO: ���������� ������������� � ����������� ��� ������ painter
	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::Canvas simpleCanvas;
	shape_drawing_lib::CanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::ModernGraphicsRenderer renderer(std::cout);

	// TODO: ��� ������ ������������ ������� PaintPicture() ����������
	// ������� �� renderer
	// ���������: ����������� ������� "�������"
	ModernGraphicsRendererAdapter rendererAdapter(renderer);
	shape_drawing_lib::CanvasPainter painter(rendererAdapter);
	PaintPicture(painter);
}

} // namespace app
