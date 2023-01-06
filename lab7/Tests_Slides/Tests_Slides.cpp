#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../Slides/Shape/GroupShape/GroupShape.h"
#include "../Slides/Shape/IShape.h"
#include "../Slides/Shape/SimpleShape/Triangle/Triangle.h"
#include "../Slides/Shape/SimpleShape/Ellipse/Ellipse.h"
#include "../Slides/Shape/SimpleShape/Rectangle/Rectangle.h"
#include "../Slides/Canvas/ConsoleCanvas.h"

bool IsSameLineStyle(const std::shared_ptr<ILineStyle> expected, const std::shared_ptr<ILineStyle> actual)
{
	return expected->IsEnabled() == actual->IsEnabled() &&
		expected->GetColor() == actual->GetColor() &&
		expected->GetThickness() == actual->GetThickness();
}

bool IsSameShape(const std::shared_ptr<IShape> expectedShape, const std::shared_ptr<IShape> actualShape)
{
	auto expectedLineStyle = expectedShape->GetLineStyle();
	auto actualLineStyle = actualShape->GetLineStyle();

	auto expectedFillStyle = expectedShape->GetFillStyle();
	auto actualFillStyle = actualShape->GetFillStyle();

	auto expectedFrame = expectedShape->GetFrame();
	auto actualFrame = actualShape->GetFrame();

	auto expectedGroupShape = expectedShape->GetGroupShape();
	auto actualGroupShape = actualShape->GetGroupShape();

	return IsSameLineStyle(expectedLineStyle, actualLineStyle) &&
		expectedFillStyle->IsEnabled() == actualFillStyle->IsEnabled() &&
		expectedFillStyle->GetColor() == actualFillStyle->GetColor() &&
		expectedFrame == actualFrame &&
		expectedGroupShape == actualGroupShape;
}

TEST_CASE("Create group shape")
{
	auto vertexA = Point{ 30, 400 };
	auto vertexB = Point{ 300, 200 };
	auto vertexC = Point{ 700, 500 };
	uint32_t fillcolor = 0x00D678FF;
	uint32_t linecolor = 0xFFFFFFFF;

	auto simpleLineStyle = std::make_shared<SimpleLineStyle>(linecolor, 1);
	auto simpleFillStyle = std::make_shared<SimpleFillStyle>(fillcolor);
	auto triangle = std::make_shared<Triangle>(vertexA, vertexB, vertexC, simpleLineStyle, simpleFillStyle);

	auto rectangleWidth = 400;
	auto rectangleHeight = 300;
	auto rectangle = std::make_shared<Rectangle>(Point{ 70, 80 }, rectangleWidth, rectangleHeight, simpleLineStyle, simpleFillStyle);
	
	SECTION("Create empty group shape")
	{
		std::vector<std::shared_ptr<IShape>> shapes;

		auto groupShape = GroupShape::Create(shapes);

		REQUIRE(groupShape->GetShapesCount() == 0);
	}

	SECTION("Create empty group shape without shapes vector")
	{
		auto groupShape = GroupShape::Create();

		REQUIRE(groupShape->GetShapesCount() == 0);
	}

	SECTION("Create group shape with one shape")
	{
		std::vector<std::shared_ptr<IShape>> shapes{ triangle };

		auto groupShape = GroupShape::Create(shapes);

		REQUIRE(groupShape->GetShapesCount() == 1);
		REQUIRE(IsSameShape(triangle, groupShape->GetShapeAtIndex(0)));
	}

	SECTION("Create group shape with several shapes")
	{
		std::vector<std::shared_ptr<IShape>> shapes{ triangle, rectangle };

		auto groupShape = GroupShape::Create(shapes);

		REQUIRE(groupShape->GetShapesCount() == 2);
		REQUIRE(IsSameShape(triangle, groupShape->GetShapeAtIndex(0)));
		REQUIRE(IsSameShape(rectangle, groupShape->GetShapeAtIndex(1)));
	}
}

TEST_CASE("Insert into created group shape")
{
	uint32_t fillcolor = 0x00D678FF;
	uint32_t linecolor = 0xFFFFFFFF;
	auto simpleLineStyle = std::make_shared<SimpleLineStyle>(linecolor, 1);
	auto simpleFillStyle = std::make_shared<SimpleFillStyle>(fillcolor);

	auto rectangleWidth = 400;
	auto rectangleHeight = 300;
	auto rectangle = std::make_shared<Rectangle>(Point{ 70, 80 }, rectangleWidth, rectangleHeight, simpleLineStyle, simpleFillStyle);

	auto ellipseWidth = 300;
	auto ellipseHeight = 200;
	auto ellipse = std::make_shared<Ellipse>(Point{ 0, 0 }, ellipseWidth, ellipseHeight, simpleLineStyle, simpleFillStyle);

	std::vector<std::shared_ptr<IShape>> shapes;
	auto groupShape = GroupShape::Create(shapes);
	auto defaultGroupShape = GroupShape::Create();

	auto group = GENERATE_COPY(groupShape, defaultGroupShape);
	SECTION("Insert new shape into the group")
	{
		group->InsertShape(rectangle, 0);

		REQUIRE(group->GetShapesCount() == 1);
		REQUIRE(IsSameShape(rectangle, group->GetShapeAtIndex(0)));
	}

	SECTION("Insert several shapes into the group")
	{
		group->InsertShape(rectangle, 0);
		group->InsertShape(ellipse, 1);

		REQUIRE(group->GetShapesCount() == 2);
		REQUIRE(IsSameShape(rectangle, group->GetShapeAtIndex(0)));
		REQUIRE(IsSameShape(ellipse, group->GetShapeAtIndex(1)));
	}

	SECTION("Insert new shape into the group with wrong index")
	{
		REQUIRE_THROWS_AS(group->InsertShape(rectangle, 1), std::out_of_range);

		REQUIRE(group->GetShapesCount() == 0);
	}

	SECTION("Get shape at index with empty group")
	{
		REQUIRE_THROWS_AS(group->GetShapeAtIndex(0), std::out_of_range);
	}

	SECTION("Get shape at wrong index with not empty group")
	{
		group->InsertShape(rectangle, 0);

		REQUIRE_NOTHROW(group->GetShapeAtIndex(0));
		REQUIRE_THROWS_AS(group->GetShapeAtIndex(1), std::out_of_range);
	}
}

TEST_CASE("Modify group shape styles draw and remove")
{
	auto vertexA = Point{ 25, 300 };
	auto vertexB = Point{ 200, 400 };
	auto vertexC = Point{ 700, 200 };
	uint32_t fillcolor = 0x123456FF;
	uint32_t linecolor = 0xFFFFFFFF;

	auto simpleLineStyle = std::make_shared<SimpleLineStyle>(linecolor, 1);
	auto simpleFillStyle = std::make_shared<SimpleFillStyle>(fillcolor);
	auto triangle = std::make_shared<Triangle>(vertexA, vertexB, vertexC, simpleLineStyle, simpleFillStyle);

	auto ellipseWidth = 300;
	auto ellipseHeight = 200;
	auto ellipse = std::make_shared<Ellipse>(Point{ 0, 0 }, ellipseWidth, ellipseHeight, simpleLineStyle, simpleFillStyle);

	std::vector<std::shared_ptr<IShape>> shapes{ triangle, ellipse };
	auto groupShape = GroupShape::Create(shapes);

	auto defaultGroupShape = GroupShape::Create();
	defaultGroupShape->InsertShape(triangle, 0);
	defaultGroupShape->InsertShape(ellipse, 1);

	auto simpleLineStyle2 = std::make_shared<SimpleLineStyle>(linecolor, 1);
	auto simpleFillStyle2 = std::make_shared<SimpleFillStyle>(fillcolor);
	auto ellipse2 = std::make_shared<Ellipse>(Point{ 0, 0 }, ellipseWidth, ellipseHeight, simpleLineStyle2, simpleFillStyle2);
	std::vector<std::shared_ptr<IShape>> shapes2{ triangle, ellipse2 };
	auto groupShapeDiffStyle = GroupShape::Create(shapes2);
	auto defaultGroupShapeDiffStyle = GroupShape::Create();
	defaultGroupShapeDiffStyle->InsertShape(triangle, 0);
	defaultGroupShapeDiffStyle->InsertShape(ellipse2, 1);

	auto group = GENERATE_COPY(groupShape, defaultGroupShape);
	auto groupDiffStyle = GENERATE_COPY(groupShapeDiffStyle, defaultGroupShapeDiffStyle);

	DYNAMIC_SECTION("Change line color of the group")
	{
		auto color = 0x654321FF;
		auto lineStyle = group->GetLineStyle();

		lineStyle->SetColor(color);

		REQUIRE(triangle->GetLineStyle()->GetColor() == color);
		REQUIRE(ellipse->GetLineStyle()->GetColor() == color);
		REQUIRE(group->GetLineStyle()->GetColor() == color);
	}

	DYNAMIC_SECTION("Change line thickness of the group")
	{
		auto thickness = 2;
		auto lineStyle = group->GetLineStyle();

		lineStyle->SetThickness(thickness);

		REQUIRE(triangle->GetLineStyle()->GetThickness() == thickness);
		REQUIRE(ellipse->GetLineStyle()->GetThickness() == thickness);
		REQUIRE(group->GetLineStyle()->GetThickness() == thickness);
	}

	DYNAMIC_SECTION("Change fill color of the group")
	{
		auto fillColor = 0x001122FF;
		auto fillStyle = group->GetFillStyle();

		fillStyle->SetColor(fillColor);

		REQUIRE(triangle->GetFillStyle()->GetColor() == fillColor);
		REQUIRE(group->GetFillStyle()->GetColor() == fillColor);
	}

	DYNAMIC_SECTION("Change frame of the group")
	{
		auto frame = RectD{ 0, 0, 350, 200 };
		auto expectedTriangleFrame = RectD{ 12.5, 100, 337.5, 100 };
		auto expectedEllipseFrame = RectD{ 0, 0, 150, 100 };

		group->SetFrame(frame);

		REQUIRE((frame == group->GetFrame()));
		REQUIRE((expectedTriangleFrame == triangle->GetFrame()));
		REQUIRE((expectedEllipseFrame == ellipse->GetFrame()));
	}

	DYNAMIC_SECTION("Change enabled line style of different shapes with the same style ptr")
	{
		auto groupLineStyle = group->GetLineStyle();

		REQUIRE(groupLineStyle->IsEnabled());
		REQUIRE_THROWS_AS(groupLineStyle->Disable(), std::logic_error);
	}

	DYNAMIC_SECTION("Change enabled fill style of different shapes with the same style ptr")
	{
		auto groupFillStyle = group->GetFillStyle();

		REQUIRE(groupFillStyle->IsEnabled());
		REQUIRE_THROWS_AS(groupFillStyle->Disable(), std::logic_error);
	}

	DYNAMIC_SECTION("Change enabled line style of different shapes with the different style ptr")
	{
		auto groupLineStyle = groupDiffStyle->GetLineStyle();

		REQUIRE(groupLineStyle->IsEnabled());
		REQUIRE_NOTHROW(groupLineStyle->Disable());
	}

	DYNAMIC_SECTION("Remove shape from the group with correct index")
	{
		REQUIRE_NOTHROW(group->RemoveShapeAtIndex(0));

		REQUIRE(group->GetShapesCount() == 1);
		REQUIRE(IsSameShape(ellipse, group->GetShapeAtIndex(0)));
	}

	DYNAMIC_SECTION("Remove shape from the group with incorrect index")
	{
		REQUIRE_THROWS_AS(group->RemoveShapeAtIndex(2), std::out_of_range);

		REQUIRE(group->GetShapesCount() == 2);
		REQUIRE(IsSameShape(triangle, group->GetShapeAtIndex(0)));
		REQUIRE(IsSameShape(ellipse, group->GetShapeAtIndex(1)));
	}

	DYNAMIC_SECTION("Draw shapes group")
	{
		std::ostringstream oss;
		ConsoleCanvas canvas(oss);
		std::ifstream file("TEST.EXMPL.TXT");
		std::stringstream expectedOutput;
		expectedOutput << file.rdbuf();

		group->Draw(canvas);
		REQUIRE(oss.str() == expectedOutput.str());
	}

	DYNAMIC_SECTION("Get group line color property with different shapes colors")
	{
		auto triangle = groupDiffStyle->GetShapeAtIndex(0);
		triangle->GetLineStyle()->SetColor(0xDDDDDDFF);

		auto groupLineColor = groupDiffStyle->GetLineStyle()->GetColor();

		REQUIRE(!groupLineColor.has_value());
	}

	DYNAMIC_SECTION("Get group line thickness property with different shapes thicknesses")
	{
		auto ellipse = groupDiffStyle->GetShapeAtIndex(1);
		ellipse->GetLineStyle()->SetThickness(10);

		auto groupLineThickness = groupDiffStyle->GetLineStyle()->GetThickness();

		REQUIRE(!groupLineThickness.has_value());
	}

	DYNAMIC_SECTION("Get group fill color property with different shapes colors")
	{
		auto triangle = groupDiffStyle->GetShapeAtIndex(0);
		triangle->GetFillStyle()->SetColor(0xBBBBBBFF);

		auto groupFillColor = groupDiffStyle->GetFillStyle()->GetColor();

		REQUIRE(!groupFillColor.has_value());
	}
}