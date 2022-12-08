#include "../pch.h"
#include "../SFMLMath/Math.h"
#include "SFMLCanvas.h"

const size_t CIRCLE_SHAPE_POINT_COUNT = 90;
const size_t POLYLINE_SEGMENT_VERTICES_COUNT = 5;
const unsigned int DEFAULT_CANVAS_LINE_THICKNESS = 1;

SFMLCanvas::SFMLCanvas(sf::RenderTarget& target)
	: m_renderTarget(target)
	, m_lineColor(sf::Color::White)
	, m_fillColor(sf::Color::Black)
	, m_lineThickness(DEFAULT_CANVAS_LINE_THICKNESS)
{
}

void SFMLCanvas::DrawLine(const Point& from, const Point& to)
{
	auto distanceX = to.x - from.x;
	auto distanceY = to.y - from.y;
	auto angle = atan2(distanceY, distanceX);

	auto cosAngle = cos(angle);
	auto width = (distanceX != 0)
		? distanceX / cosAngle
		: distanceY;

	sf::RectangleShape line(sf::Vector2f((float)std::abs(width), (float)m_lineThickness));
	line.setPosition((float)from.x, (float)from.y);
	line.setOutlineColor(m_fillColor);

	auto angleDeg = (float)(angle * 180 / M_PI);
	if (angle <= M_PI_2)
	{
		line.setOrigin(0, (float)m_lineThickness);
		
	}
	line.rotate(angleDeg);

	m_renderTarget.draw(line);
}

void SFMLCanvas::DrawClosedPolyLine(std::vector<Point>& points)
{
	auto pointCount = points.size();

	if (pointCount < 3)
	{
		throw std::invalid_argument("Unable to draw polyline with less than 3 vertices");
	}

	for (size_t index = 0; index < pointCount; ++index)
	{
		DrawClosedPolyLineSegment(index, points);
	}

}

void SFMLCanvas::DrawClosedPolyLineSegment(size_t index, const std::vector<Point>& points)
{
	auto pointCount = points.size();
	if (pointCount <= index)
	{
		throw std::out_of_range("Polyline segment index is out of range");
	}

	sf::ConvexShape polyLineSegment;
	polyLineSegment.setPointCount(POLYLINE_SEGMENT_VERTICES_COUNT);

	auto thickness = (float)m_lineThickness / 2;

	auto prevIndex = ((index - 1) + pointCount) % pointCount;
	auto nextIndex = (index + 1) % pointCount;
	sf::Vector2f prevPoint((float)points[prevIndex].x, (float)points[prevIndex].y);
	sf::Vector2f currPoint((float)points[index].x, (float)points[index].y);
	auto lineVector = currPoint - prevPoint;
	auto normal = Math::Normalized(sf::Vector2f(-lineVector.y, lineVector.x));
	sf::Vector2f a = prevPoint - thickness * normal;
	sf::Vector2f b = prevPoint + thickness * normal;

	sf::Vector2f nextPoint((float)points[nextIndex].x, (float)points[nextIndex].y);
	auto nextLineVector = nextPoint - currPoint;
	auto nextNormal = Math::Normalized(sf::Vector2f(-nextLineVector.y, nextLineVector.x));
	sf::Vector2f nextA = currPoint - thickness * nextNormal;

	sf::Vector2f tangent = Math::Normalized(Math::Normalized(nextPoint - currPoint) + Math::Normalized(currPoint - prevPoint));
	sf::Vector2f miter = sf::Vector2f(-tangent.y, tangent.x); // normal of the tangent
	float length = thickness / Math::DotProduct(miter, normal);

	sf::Vector2f m1 = currPoint - length * miter;
	sf::Vector2f m2 = currPoint + length * miter;

	polyLineSegment.setPoint(0, a);
	polyLineSegment.setPoint(1, b);
	polyLineSegment.setPoint(2, m2);
	polyLineSegment.setPoint(3, nextA);
	polyLineSegment.setPoint(4, m1);

	m_renderTarget.draw(polyLineSegment);
}


void SFMLCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	auto ellipse = sf::CircleShape((float)width / 2, CIRCLE_SHAPE_POINT_COUNT);

	ellipse.setPosition((float)leftTop.x, (float)leftTop.y);
	ellipse.setScale(1, (float)(height / width));

	ellipse.setOutlineColor(m_lineColor);
	ellipse.setOutlineThickness((float)m_lineThickness);

	ellipse.setFillColor(sf::Color::Transparent);

	m_renderTarget.draw(ellipse);
}

void SFMLCanvas::FillEllipse(const Point& leftTop, double width, double height)
{
	auto ellipse = sf::CircleShape((float)width / 2, CIRCLE_SHAPE_POINT_COUNT);

	ellipse.setPosition((float)leftTop.x, (float)leftTop.y);
	ellipse.setScale(1, (float)(height / width));

	ellipse.setOutlineThickness(0);
	ellipse.setFillColor(m_fillColor);

	m_renderTarget.draw(ellipse);
}

void SFMLCanvas::FillPolygon(std::vector<Point>& points)
{
	sf::ConvexShape convex;

	auto pointCount = points.size();
	convex.setPointCount(pointCount);

	for (size_t index = 0; index < pointCount; ++index)
	{
		Point point = points[index];
		convex.setPoint(index, sf::Vector2f((float)point.x, (float)point.y));
	}

	convex.setFillColor(m_fillColor);

	m_renderTarget.draw(convex);
}

void SFMLCanvas::SetFillColor(uint32_t color)
{
	m_fillColor = sf::Color(color);
}

void SFMLCanvas::SetLineColor(uint32_t color)
{
	m_lineColor = sf::Color(color);
}

void SFMLCanvas::SetLineThickness(unsigned int thickness)
{
	m_lineThickness = thickness;
}

void SFMLCanvas::Capture(const std::string& outputFileName) const
{
	sf::Vector2u renderSize = m_renderTarget.getSize();
	sf::Texture texture;
	texture.create(renderSize.x, renderSize.y);
	
	try
	{
		sf::RenderWindow& window = dynamic_cast<sf::RenderWindow&>(m_renderTarget);
		texture.update(window);
		sf::Image screenshot = texture.copyToImage();
		screenshot.saveToFile(outputFileName);
	}
	catch (const std::bad_cast&)
	{
		throw std::runtime_error("Unable to capture canvas with not sf::RenderWindow render target type");
	}
}
