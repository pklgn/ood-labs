#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../PictureManager/Designer/Designer.h"
#include "../PictureManager/Painter/Painter.h"
#include "../PictureManager/Canvas/Canvas.h"
#include "../PictureManager/Shapes/Factory/ShapeFactory.h"
#include "../PictureManager/Shapes/Factory/IShapeFactory.h"
#include "../PictureManager/Shapes/Ellipse.h"
#include "../PictureManager/Shapes/Rectangle.h"
#include "../PictureManager/Shapes/RegularPolygon.h"
#include "../PictureManager/Shapes/Triangle.h"
#include "MockCanvas.h"

TEST_CASE("Create triangle with proper values")
{
	//arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();
	
	//act
	auto shape = factory->CreateShape("triangle 450 150 600 250 450 350 pink");

	//assert
	REQUIRE(shape->GetColor() == Color::Pink);
	auto triangle = static_cast<Triangle*>(shape.get());
	REQUIRE(triangle->GetVertex1().x == 450);
	REQUIRE(triangle->GetVertex1().y == 150);
	REQUIRE(triangle->GetVertex2().x == 600);
	REQUIRE(triangle->GetVertex2().y == 250);
	REQUIRE(triangle->GetVertex3().x == 450);
	REQUIRE(triangle->GetVertex3().y == 350);
}

TEST_CASE("Create triangle with invalid values")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("triangle 450 150 600 250 450 pink");

	// assert
	REQUIRE(shape == nullptr);
}

TEST_CASE("Draw triangle with a mock canvas")
{
	//arrange
	std::ostringstream os;
	MockCanvas mockCanvas(os);
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();
	auto shape = factory->CreateShape("triangle 450 150 600 250 450 350 pink");
	std::stringstream expectedResult("e5acb6\n"
									 "450-150 600-250\n"
									 "600-250 450-350\n"
									 "450-150 450-350\n");

	//act
	shape->Draw(mockCanvas);

	//assert
	REQUIRE(expectedResult.str() == os.str());
}

TEST_CASE("Create ellipse with proper values")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("ellipse 350 250 50 50 blue");

	// assert
	REQUIRE(shape->GetColor() == Color::Blue);
}

TEST_CASE("Create ellipse with invalid values")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("ellipse 350 250 50 50");

	// assert
	REQUIRE(shape == nullptr);
}

TEST_CASE("Draw ellipse with a mock canvas")
{
	// arrange
	std::ostringstream os;
	MockCanvas mockCanvas(os);
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();
	auto shape = factory->CreateShape("ellipse 350 250 50 50 blue");
	std::stringstream expectedResult("96ff\n"
									 "250-250\n"
									 "width: 100\n"
									 "heigth: 100\n"
									 "pointCount: 30\n");

	// act
	shape->Draw(mockCanvas);

	// assert
	REQUIRE(expectedResult.str() == os.str());
}

TEST_CASE("Create rectangle with proper values")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("rectangle 150 150 450 350 yellow");

	// assert
	REQUIRE(shape->GetColor() == Color::Yellow);
}

TEST_CASE("Create rectanlge with invalid values")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("ellipse 350");

	// assert
	REQUIRE(shape == nullptr);
}

TEST_CASE("Draw rectanlge with a mock canvas")
{
	// arrange
	std::ostringstream os;
	MockCanvas mockCanvas(os);
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();
	auto shape = factory->CreateShape("rectangle 150 150 450 350 yellow");
	std::stringstream expectedResult("ffea00\n"
									 "150-150 450-150\n"
									 "450-150 450-350\n"
									 "450-350 150-350\n"
									 "150-350 150-150\n");

	// act
	shape->Draw(mockCanvas);

	// assert
	REQUIRE(expectedResult.str() == os.str());
}

TEST_CASE("Create regular polygon with proper values")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("regular-polygon 550 250 10 200 red");

	// assert
	REQUIRE(shape->GetColor() == Color::Red);
}

TEST_CASE("Create regular polygon with invalid values")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("regular-polygon 550 250 10 ed");

	// assert
	REQUIRE(shape == nullptr);
}

TEST_CASE("Draw regular polygon with a mock canvas")
{
	// arrange
	std::ostringstream os;
	MockCanvas mockCanvas(os);
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();
	auto shape = factory->CreateShape("regular-polygon 550 250 10 200 red");
	std::stringstream expectedResult("ee4b2b\n"
									 "550-250\n"
									 "width: 200\n"
									 "heigth: 200\n"
									 "pointCount: 10\n");

	// act
	shape->Draw(mockCanvas);

	// assert
	REQUIRE(expectedResult.str() == os.str());
}

TEST_CASE("Factory return nullptr when wrong description was given")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("line 100 100 200 200 yellow");

	// assert
	REQUIRE(shape == nullptr);
}

TEST_CASE("Shape will have default black color when invalid color value was given")
{
	// arrange
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	auto shape = factory->CreateShape("regular-polygon 550 250 10 200 re1d");

	// assert
	REQUIRE(shape->GetColor() == Color::Black);
}

TEST_CASE("Create picture draft with valid description lines")
{
	//arrange
	PictureDraft pictureDraft;
	std::vector<std::string> descriptions = { "rectangle 150 150 450 350 yellow",
		"triangle 450 150 600 250 450 350 pink",
		"ellipse 350 250 50 50 blue" };
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	//act
	for (auto& desc : descriptions)
	{
		pictureDraft.AddShape(factory->CreateShape(desc));
	}

	//assert
	REQUIRE(pictureDraft.GetShapeCount() == 3);
	REQUIRE(pictureDraft.GetShape(1)->get()->GetColor() == Color::Pink);
}

TEST_CASE("Create picture draft with invalid description lines")
{
	// arrange
	PictureDraft pictureDraft;
	std::vector<std::string> descriptionsWithInvalidValues = { "rectangle 150 150 450 350 yellow",
		"line 400 150 400 75 blue",
		"ellipse 350 250 50 50 blue" };
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	// act
	for (auto& desc : descriptionsWithInvalidValues)
	{
		pictureDraft.AddShape(factory->CreateShape(desc));
	}

	// assert
	REQUIRE(pictureDraft.GetShapeCount() == 2);
	REQUIRE(pictureDraft.GetShape(1)->get()->GetColor() == Color::Blue);
}

TEST_CASE("Designer create all shapes draft")
{
	// arrange
	Designer designer;
	std::istringstream descriptions("rectangle 150 150 450 350 yellow\n"
							   "triangle 450 150 600 250 450 350 pink\n"
							   "ellipse 350 250 50 50 blue\n");

	// act
	auto pictureDraft = designer.CreateDraft(descriptions);

	// assert
	REQUIRE(pictureDraft.GetShapeCount() == 3);
	REQUIRE(pictureDraft.GetShape(2)->get()->GetColor() == Color::Blue);
}

TEST_CASE("Designer create all shapes draft excluding invalid lines")
{
	// arrange
	Designer designer;
	std::istringstream descriptions("rectangle 150 150 450 350 yellow\n"
									"invalid line\n"
									"ellipse 350 250 50 50 blue\n");

	// act
	auto pictureDraft = designer.CreateDraft(descriptions);

	// assert
	REQUIRE(pictureDraft.GetShapeCount() == 2);
	REQUIRE(pictureDraft.GetShape(1)->get()->GetColor() == Color::Blue);
}

TEST_CASE("Painter draw all shapes")
{
	//arrange
	Painter painter;
	std::ostringstream os;
	MockCanvas mockCanvas(os);
	Designer designer;
	std::istringstream descriptions("rectangle 150 150 450 350 yellow\n"
									"triangle 450 150 600 250 450 350 pink\n");
	std::ostringstream expectedResult("ffea00\n"
									  "150-150 450-150\n"
									  "450-150 450-350\n"
									  "450-350 150-350\n"
									  "150-350 150-150\n"
									  "e5acb6\n"
									  "450-150 600-250\n"
									  "600-250 450-350\n"
									  "450-150 450-350\n");

	//act
	painter.DrawPicture(designer.CreateDraft(descriptions), mockCanvas);

	//assert
	REQUIRE(expectedResult.str() == os.str());
}

TEST_CASE("Painter draw all shapes excluding invalid shapes")
{
	// arrange
	Painter painter;
	std::ostringstream os;
	MockCanvas mockCanvas(os);
	Designer designer;
	std::istringstream descriptions("rectangle 150 150 450 350 yellow\n"
									"invalid line\n");
	std::ostringstream expectedResult("ffea00\n"
									  "150-150 450-150\n"
									  "450-150 450-350\n"
									  "450-350 150-350\n"
									  "150-350 150-150\n");

	// act
	painter.DrawPicture(designer.CreateDraft(descriptions), mockCanvas);

	// assert
	REQUIRE(expectedResult.str() == os.str());
}