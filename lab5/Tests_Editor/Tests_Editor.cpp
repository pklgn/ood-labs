#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../Editor/Editor/Editor.h"
#include "../Editor/Document/HTMLDocument.h"
#include "../Editor/Document/DocumentItems/Elements/Paragraph/Paragraph.h"
#include "../Editor/Document/DocumentItems/Elements/Image/Image.h"

TEST_CASE("Check document creation")
{
	HTMLDocument document;

	REQUIRE(document.GetItemsCount() == 0);

	REQUIRE_FALSE(document.CanUndo());
	REQUIRE_FALSE(document.CanRedo());
}

TEST_CASE("Check paragraph methods")
{
	auto expectedText = "TEXT!";
	Paragraph paragraph(expectedText);

	SECTION("Get text from paragraph")
	{
		REQUIRE(paragraph.GetText() == expectedText);
	}

	SECTION("Change text value and check updated one")
	{
		auto settedText = "NEW!";
		paragraph.SetText(settedText);
		REQUIRE(paragraph.GetText() == settedText);
	}
}

TEST_CASE("Check image methods")
{
	std::unique_ptr<Image> imagePtr;
	SECTION("Create image with wrong sizes")
	{
		auto exceptionMessage = "Image sizes must have appropriate values";
		REQUIRE_THROWS(imagePtr.reset(new Image(10001, 1, ".\\")), exceptionMessage);
		REQUIRE_THROWS(imagePtr.reset(new Image(300, 10001, ".\\")), exceptionMessage);
		REQUIRE_THROWS(imagePtr.reset(new Image(0, 100, ".\\")), exceptionMessage);
		REQUIRE_THROWS(imagePtr.reset(new Image(200, 0, ".\\")), exceptionMessage);
		REQUIRE_THROWS(imagePtr.reset(new Image(0, 0, ".\\")), exceptionMessage);
		REQUIRE_THROWS(imagePtr.reset(new Image(10001, 10001, ".\\")), exceptionMessage);
	}

	SECTION("Create image with wrong path")
	{
		auto exceptionMessage = "Image path can't be found";
		REQUIRE_THROWS(imagePtr.reset(new Image(800, 600, "pathdoesntexist")), exceptionMessage);
	}

	SECTION("Create image with all wrong arguments")
	{
		auto exceptionMessage = "Image sizes must have appropriate values";
		REQUIRE_THROWS(imagePtr.reset(new Image(0, 0, "pathdoesntexist")), exceptionMessage);
	}

	SECTION("Create image will all valid arguments")
	{
		REQUIRE_NOTHROW(imagePtr.reset(new Image(800, 600, ".\\")));
	}
}

