﻿#include "../../pch.h"
#include "SelectionFrameView.h"

const uint32_t DEFAULT_SELECTION_COLOR = 0x00FF00FF;
const unsigned int DEFAULT_SELECTION_THICKNESS = 2;
const size_t DEFAULT_SELECTION_CORNER_SIZE = 10;

SelectionFrameView::SelectionFrameView(ShapeAppModel& shape)
	: m_shapeAppModel(shape)
	, m_frame(shape.GetFrame())
	, m_id(shape.GetId())
{
	m_shapeAppModel.DoOnFrameChanged([&, this](const RectD& frame) {
		m_frame = frame;
	});
	// TODO: как перерисовать с новыми данными?
}

SelectionFrameView::Id SelectionFrameView::GetId() const
{
	return m_id;
}

void SelectionFrameView::Show(ICanvas& canvas)
{
	auto thickness = DEFAULT_SELECTION_THICKNESS;

	Point leftTop = { m_frame.left, m_frame.top };
	Point rightBottom = { m_frame.left + m_frame.width, m_frame.top + m_frame.height };
	Point rightTop = { rightBottom.x, m_frame.top};
	Point leftBottom = { m_frame.left, rightBottom.y };

	canvas.SetFillColor(DEFAULT_SELECTION_COLOR);

	canvas.SetLineThickness(thickness);

	canvas.DrawLine({ leftTop.x - thickness, leftTop.y }, { rightTop.x + thickness, rightTop.y });
	canvas.DrawLine(rightTop, rightBottom);
	canvas.DrawLine({ rightBottom.x + thickness, rightBottom.y + thickness }, { leftBottom.x - thickness, leftBottom.y + thickness });
	canvas.DrawLine(leftBottom, leftTop);

	// первый квадратик, за который можно перетаскивать
	ShowCorner(canvas, leftTop);
	ShowCorner(canvas, { rightTop.x - DEFAULT_SELECTION_CORNER_SIZE, rightTop.y });
	ShowCorner(canvas, { rightBottom.x - DEFAULT_SELECTION_CORNER_SIZE, rightBottom.y - DEFAULT_SELECTION_CORNER_SIZE });
	ShowCorner(canvas, { leftBottom.x, leftBottom.y - DEFAULT_SELECTION_CORNER_SIZE });
}

void SelectionFrameView::ShowCorner(ICanvas& canvas, const Point& leftTop)
{
	Point rightTop = { leftTop.x + DEFAULT_SELECTION_CORNER_SIZE, leftTop.y };
	Point rightBottom = { leftTop.x + DEFAULT_SELECTION_CORNER_SIZE, leftTop.y + DEFAULT_SELECTION_CORNER_SIZE };
	Point leftBottom = { leftTop.x, leftTop.y + DEFAULT_SELECTION_CORNER_SIZE };

	canvas.SetFillColor(DEFAULT_SELECTION_COLOR);

	std::vector<Point> points{ leftTop, rightTop, rightBottom, leftBottom };
	canvas.FillPolygon(points);
}
