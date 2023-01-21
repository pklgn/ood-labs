#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../ShapesEditor/Model/Shape/Shape.h"
#include "../ShapesEditor/App/UseCases/UseCaseFactory/UseCaseFactory.h"
#include "../ShapesEditor/App/ShapeSelectionModel/ShapeSelectionModel.h"
#include "../ShapesEditor/App/History/CommandsHistory.h"

TEST_CASE("Create domain shape")
{
	auto rectangle = Shape(ShapeType::Rectangle);
	SECTION("Check defaults")
	{
		auto frame = rectangle.GetFrame();
		REQUIRE(frame.left == 0);
		REQUIRE(frame.top == 0);
		REQUIRE(frame.width == 100);
		REQUIRE(frame.height == 100);
	}

	SECTION("Set frame with some values")
	{
		RectD newFrame = { 100, 200, 423, 76 };

		rectangle.SetFrame(newFrame);

		auto frame = rectangle.GetFrame();
		REQUIRE(frame.left == 100);
		REQUIRE(frame.top == 200);
		REQUIRE(frame.width == 423);
		REQUIRE(frame.height == 76);
	}

	SECTION("Check shape type")
	{
		REQUIRE(rectangle.GetType() == ShapeType::Rectangle);

		auto ellipse = Shape(ShapeType::Ellipse);
		REQUIRE(ellipse.GetType() == ShapeType::Ellipse);

		auto triangle = Shape(ShapeType::Triangle);
		REQUIRE(triangle.GetType() == ShapeType::Triangle);
	}
}

TEST_CASE("Check move use cases")
{
	ShapeSelectionModel shapeSelectionModel;
	CommandsHistory commandsContainer;
	auto useCaseFactory = UseCaseFactory(shapeSelectionModel, commandsContainer);

	auto triangle = std::make_shared<Shape>(ShapeType::Triangle);
	auto shapeAppModel = std::make_shared<ShapeAppModel>(triangle);
	shapeSelectionModel.SetSelectedShapes({ shapeAppModel });

	SECTION("Move in forth coordinate quarter")
	{
		auto useCase = useCaseFactory.CreateMoveShapeUseCase();
		useCase->Move({ 10, 99 });

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == 10);
		REQUIRE(frame.top == 99);
		REQUIRE(frame.width == 100);
		REQUIRE(frame.height == 100);
	}

	SECTION("Move in first coordinate quarter")
	{
		auto useCase = useCaseFactory.CreateMoveShapeUseCase();
		useCase->Move({ 20, -127 });

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == 20);
		REQUIRE(frame.top == -127);
		REQUIRE(frame.width == 100);
		REQUIRE(frame.height == 100);
	}

	SECTION("Move in second coordinate quarter")
	{
		auto useCase = useCaseFactory.CreateMoveShapeUseCase();
		useCase->Move({ -30, -127 });

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == -30);
		REQUIRE(frame.top == -127);
		REQUIRE(frame.width == 100);
		REQUIRE(frame.height == 100);
	}

	SECTION("Move in third coordinate quarter")
	{
		auto useCase = useCaseFactory.CreateMoveShapeUseCase();
		useCase->Move({ -40, 220 });

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == -40);
		REQUIRE(frame.top == 220);
		REQUIRE(frame.width == 100);
		REQUIRE(frame.height == 100);
	}
}

TEST_CASE("Check resize use cases")
{
	ShapeSelectionModel shapeSelectionModel;
	CommandsHistory commandsContainer;
	auto useCaseFactory = UseCaseFactory(shapeSelectionModel, commandsContainer);

	auto triangle = std::make_shared<Shape>(ShapeType::Triangle);
	auto shapeAppModel = std::make_shared<ShapeAppModel>(triangle);
	shapeSelectionModel.SetSelectedShapes({ shapeAppModel });

	SECTION("Resize from left bottom corner")
	{
		auto useCase = useCaseFactory.CreateResizeShapeUseCase();
		useCase->Resize({ 10, 20 }, BasePoint::LeftBottom);

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == 0);
		REQUIRE(frame.top == 20);
		REQUIRE(frame.width == 110);
		REQUIRE(frame.height == 80);
	}

	SECTION("Resize when minimum size found")
	{
		auto useCase = useCaseFactory.CreateResizeShapeUseCase();
		useCase->Resize({ 10, 80 }, BasePoint::LeftBottom);

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == 0);
		REQUIRE(frame.top == 80);
		REQUIRE(frame.width == 110);
		REQUIRE(frame.height == 30);
	}

	SECTION("Resize from left top corner")
	{
		auto useCase = useCaseFactory.CreateResizeShapeUseCase();
		useCase->Resize({ 10, 20 }, BasePoint::LeftTop);

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == 0);
		REQUIRE(frame.top == 0);
		REQUIRE(frame.width == 110);
		REQUIRE(frame.height == 120);
	}

	SECTION("Resize from right bottom corner")
	{
		auto useCase = useCaseFactory.CreateResizeShapeUseCase();
		useCase->Resize({ 30, 40 }, BasePoint::RightBottom);

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == 30);
		REQUIRE(frame.top == 40);
		REQUIRE(frame.width == 70);
		REQUIRE(frame.height == 60);
	}

	SECTION("Resize from right top corner")
	{
		auto useCase = useCaseFactory.CreateResizeShapeUseCase();
		useCase->Resize({ 50, 60 }, BasePoint::RightTop);

		auto frame = shapeAppModel->GetFrame();
		REQUIRE(frame.left == 50);
		REQUIRE(frame.top == 0);
		REQUIRE(frame.width == 50);
		REQUIRE(frame.height == 160);
	}
}
