#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <filesystem>
#include "../Editor/Editor/Editor.h"
#include "../Editor/Document/HTMLDocument.h"
#include "../Editor/Document/DocumentItems/Elements/Paragraph/Paragraph.h"
#include "../Editor/Document/DocumentItems/Elements/Image/Image.h"
#include "../Editor/Document/DocumentItems/ConstDocumentItem.h"
#include "../Editor/Document/DocumentItems/DocumentItem.h"
#include "../Editor/History/History.h"
#include "../Editor/Document/Commands/SetTitleCommand.h"
#include "../Editor/Document/Commands/ResizeImageCommand.h"
#include "../Editor/Document/Commands/ReplaceTextCommand.h"
#include "../Editor/Document/Commands/InsertImageCommand.h"
#include "../Editor/Document/Commands/InsertParagraphCommand.h"
#include "../Editor/Document/Commands/DeleteItemCommand.h"
#include "../Editor/Editor/Menu.h"

namespace fs = std::filesystem;

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

	SECTION("Create image with all valid arguments")
	{
		REQUIRE_NOTHROW(imagePtr.reset(new Image(800, 600, ".\\output.jpg")));
	}

	Image image(800, 600, ".\\output.jpg");
	SECTION("Get image properties")
	{
		REQUIRE(image.GetWidth() == 800);
		REQUIRE(image.GetHeight() == 600);
		REQUIRE(image.GetPath() == ".\\output.jpg");
	}

	SECTION("Perform resize")
	{
		REQUIRE_NOTHROW(image.Resize(100, 200));

		auto exceptionMessage = "Image sizes must have appropriate values";
		REQUIRE_THROWS(image.Resize(10001, 1), exceptionMessage);
		REQUIRE_THROWS(image.Resize(300, 10001), exceptionMessage);
		REQUIRE_THROWS(image.Resize(0, 100), exceptionMessage);
		REQUIRE_THROWS(image.Resize(200, 0), exceptionMessage);
		REQUIRE_THROWS(image.Resize(0, 0), exceptionMessage);
		REQUIRE_THROWS(image.Resize(10001, 10001), exceptionMessage);
	}
}

TEST_CASE("Check DocumentItem methods")
{
	SECTION("Check wrapped image")
	{
		DocumentItem imageDocumentItem(std::make_shared<Image>(800, 600, ".\\output.jpg"));
		REQUIRE_FALSE(imageDocumentItem.GetImage() == nullptr);
		REQUIRE(imageDocumentItem.GetParagraph() == nullptr);
	}

	SECTION("Check wrapped paragrpap")
	{
		DocumentItem paragraphDocumentItem(std::make_shared<Paragraph>("paragraph"));
		REQUIRE_FALSE(paragraphDocumentItem.GetParagraph() == nullptr);
		REQUIRE(paragraphDocumentItem.GetImage() == nullptr);
	}
}

TEST_CASE("Check ConstDocumentItem methods")
{
	SECTION("Check wrapped image")
	{
		ConstDocumentItem imageDocumentItem(std::make_shared<Image>(800, 600, ".\\output.jpg"));
		REQUIRE_FALSE(imageDocumentItem.GetImage() == nullptr);
		REQUIRE(imageDocumentItem.GetParagraph() == nullptr);
	}

	SECTION("Check wrapped paragrpap")
	{
		ConstDocumentItem paragraphDocumentItem(std::make_shared<Paragraph>("paragraph"));
		REQUIRE_FALSE(paragraphDocumentItem.GetParagraph() == nullptr);
		REQUIRE(paragraphDocumentItem.GetImage() == nullptr);
	}
}

TEST_CASE("Check History")
{
	History history;

	REQUIRE_FALSE(history.CanUndo());
	REQUIRE_FALSE(history.CanRedo());

	std::string oldText = "OLD TEXT";
	std::string targetString = oldText;
	std::string expectedString = "NEW TEXT";
	SECTION("Check undo")
	{
		history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(targetString, expectedString));

		REQUIRE(history.CanUndo());
		REQUIRE(targetString == expectedString);

		history.Undo();
		REQUIRE_FALSE(history.CanUndo());
		REQUIRE(targetString == oldText);
	}

	SECTION("Check redo")
	{
		history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(targetString, expectedString));

		REQUIRE_FALSE(history.CanRedo());

		history.Undo();
		REQUIRE(history.CanRedo());

		history.Redo();
		REQUIRE_FALSE(history.CanRedo());
		REQUIRE(targetString == expectedString);
	}

	SECTION("Check history depth level")
	{
		for (size_t command = 0; command < history.COMMANDS_DEPTH_LEVEL + 1; ++command)
		{
			history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(targetString, expectedString));
		}

		size_t undoCount = 0;
		while (history.CanUndo())
		{
			history.Undo();
			++undoCount;
		}

		REQUIRE(undoCount == history.COMMANDS_DEPTH_LEVEL);
	}

	SECTION("Check history branches")
	{
		for (size_t command = 0; command < 5; ++command)
		{
			history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(targetString, expectedString + std::to_string(command)));
		}
		history.Undo();
		history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(targetString, expectedString));
		history.Undo();
		history.Redo();
		
		REQUIRE(targetString == expectedString);
	}
}

TEST_CASE("Check Menu")
{
	std::istringstream iss;
	std::ostringstream oss;

	Menu menu(iss, oss);

	menu.AddItem("Shortcut", "Description", [&oss]() { oss << "Executed\n"; });

	SECTION("Check command reading")
	{
		iss.str("Shortcut");
		menu.Run();
		REQUIRE(oss.str() == ">"
							 "Executed\n"
							 ">");
	}

	SECTION("Check command reading")
	{
		iss.str("Wrong shortcut");
		menu.Run();
		REQUIRE(oss.str() == ">"
							 "Unknown command\n"
							 ">");
	}

	SECTION("Check instructions list")
	{
		menu.ShowInstructions();
		REQUIRE(oss.str() == "Commands list:\n"
							 "  Shortcut: Description\n");
	}

	SECTION("Add several instructions")
	{
		for (size_t instruction = 1; instruction < 5; ++instruction)
		{
			menu.AddItem("Shortcut" + std::to_string(instruction),
				"Description" + std::to_string(instruction),
				[&oss, instruction]() { oss << "Executed" + std::to_string(instruction) << std::endl; });
		}

		menu.ShowInstructions();
		REQUIRE(oss.str() == "Commands list:\n"
							 "  Shortcut: Description\n"
							 "  Shortcut1: Description1\n"
							 "  Shortcut2: Description2\n"
							 "  Shortcut3: Description3\n"
							 "  Shortcut4: Description4\n");
		oss.str("");

		iss.str("Shortcut3");
		menu.Run();
		REQUIRE(oss.str() == ">"
							 "Executed3\n"
							 ">");
	}
}

TEST_CASE("Check SetTitle command")
{
	std::string title = "TITLE";
	std::string target = title;
	std::string settedTitle = "NEW TITLE";

	History history;

	history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(target, settedTitle));

	REQUIRE(target == settedTitle);

	SECTION("Undo")
	{
		history.Undo();
		REQUIRE(target == title);
	}
	SECTION("Redo")
	{
		history.Undo();
		REQUIRE(target == title);
		history.Redo();
		REQUIRE(target == settedTitle);
	}
}

TEST_CASE("Check ResizeImageCommand")
{
	History history;
	auto imagePtr = std::make_shared<Image>(800, 600, ".\\output.jpg");
	auto iImagePtr = std::dynamic_pointer_cast<IImage>(imagePtr);
	history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(iImagePtr, 700, 500));

	REQUIRE(imagePtr->GetWidth() == 700);
	REQUIRE(imagePtr->GetHeight() == 500);
	REQUIRE(imagePtr->GetPath() == ".\\output.jpg");

	SECTION("Check invalid resize commands")
	{
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(iImagePtr, 10001, 1)));
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(iImagePtr, 300, 10001)));
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(iImagePtr, 0, 100)));
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(iImagePtr, 200, 0)));
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(iImagePtr, 0, 0)));
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(iImagePtr, 10001, 10001)));
	}

	SECTION("Undo")
	{
		history.Undo();
		REQUIRE(imagePtr->GetWidth() == 800);
		REQUIRE(imagePtr->GetHeight() == 600);
	}

	SECTION("Redo")
	{
		history.Undo();
		history.Redo();
		REQUIRE(imagePtr->GetWidth() == 700);
		REQUIRE(imagePtr->GetHeight() == 500);
	}
}

TEST_CASE("Check ReplaceTextCommand")
{
	History history;
	auto paragraphPtr = std::make_shared<Paragraph>("TEXT");
	auto iParagraphPtr = std::dynamic_pointer_cast<IParagraph>(paragraphPtr);
	history.AddAndExecuteCommand(std::make_unique<ReplaceTextCommand>(iParagraphPtr, "NEW TEXT"));

	SECTION("Undo")
	{
		history.Undo();
		REQUIRE(paragraphPtr->GetText() == "TEXT");
	}

	SECTION("Redo")
	{
		history.Undo();
		history.Redo();
		REQUIRE(paragraphPtr->GetText() == "NEW TEXT");
	}
}

TEST_CASE("Check InsertParagraphCommand")
{
	History history;
	std::vector<DocumentItem> items;
	auto paragraphPtr = std::make_shared<Paragraph>("TEXT");
	auto iParagraphPtr = std::dynamic_pointer_cast<IParagraph>(paragraphPtr);

	REQUIRE_NOTHROW(history.AddAndExecuteCommand(std::make_unique<InsertParagraphCommand>(items, iParagraphPtr, 0)));
	REQUIRE(items.size() == 1);
	REQUIRE(items.front().GetParagraph() != nullptr);
	REQUIRE(items.front().GetParagraph()->GetText() == "TEXT");

	SECTION("Out of range position")
	{
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<InsertParagraphCommand>(items, iParagraphPtr, 100)));
	}

	SECTION("Undo")
	{
		history.Undo();
		REQUIRE(items.size() == 0);
	}

	SECTION("Redo")
	{
		history.Undo();
		history.Redo();
		REQUIRE(items.size() == 1);
		REQUIRE(items.front().GetParagraph()->GetText() == "TEXT");
	}
}

TEST_CASE("Check InsertImageCommand")
{
	History history;
	std::vector<DocumentItem> items;
	auto imagePtr = std::make_shared<Image>(800, 600, ".\\output.jpg");
	auto iImagePtr = std::dynamic_pointer_cast<IImage>(imagePtr);

	REQUIRE_NOTHROW(history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(items, iImagePtr, 0)));
	REQUIRE(items.size() == 1);
	REQUIRE(items.front().GetImage() != nullptr);
	REQUIRE(items.front().GetImage()->GetWidth() == 800);
	REQUIRE(items.front().GetImage()->GetHeight() == 600);

	Path imagePath = items.front().GetImage()->GetPath();
	history.Undo();
	SECTION("Delete a canceled command")
	{
		std::string target;
		for (size_t counter = 0; counter < history.COMMANDS_DEPTH_LEVEL; ++counter)
		{
			history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(target, std::to_string(counter)));
		}
		REQUIRE_FALSE(fs::exists(imagePath));
	}

	SECTION("Out of range position")
	{
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(items, iImagePtr, 100)));
	}
}

TEST_CASE("Check InsertImageCommand for executed deletion")
{
	History history;
	std::vector<DocumentItem> items;
	auto imagePtr = std::make_shared<Image>(800, 600, ".\\output1.jpg");
	auto iImagePtr = std::dynamic_pointer_cast<IImage>(imagePtr);
	REQUIRE_NOTHROW(history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(items, iImagePtr, 0)));
	Path imagePath = items.front().GetImage()->GetPath();
	//overflow history
	std::string target;
	for (size_t counter = 0; counter < history.COMMANDS_DEPTH_LEVEL; ++counter)
	{
		history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(target, std::to_string(counter)));
	}

	REQUIRE(fs::exists(imagePath));
}
//TODO: передавать объект в test_case
TEST_CASE("Check DeleteItemCommand")
{
	History history;
	std::vector<DocumentItem> items;
	auto imagePtr = std::make_shared<Image>(800, 600, ".\\output.jpg");
	auto iImagePtr = std::dynamic_pointer_cast<IImage>(imagePtr);

	REQUIRE_NOTHROW(history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(items, iImagePtr, 0)));
	REQUIRE_NOTHROW(history.AddAndExecuteCommand(std::make_unique<DeleteItemCommand>(items, 0)));

	SECTION("Out of range position")
	{
		REQUIRE_THROWS(history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(items, iImagePtr, 100)));
	}

	SECTION("Check delete when depth level overflowed")
	{
		auto imagePath = iImagePtr->GetPath();
		REQUIRE(fs::exists(imagePath));
		std::string target;
		for (size_t counter = 0; counter < history.COMMANDS_DEPTH_LEVEL; ++counter)
		{
			history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(target, std::to_string(counter)));
		}
		REQUIRE_FALSE(fs::exists(imagePath));
	}

	SECTION("Delete a canceled action")
	{
		history.Undo();
		std::string target;
		history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(target, "NEW"));
		auto imagePath = iImagePtr->GetPath();
		REQUIRE(fs::exists(imagePath));
	}
}

TEST_CASE("Check document")
{
	HTMLDocument document;

	REQUIRE(document.GetItemsCount() == 0);

	SECTION("Add paragraph")
	{
		document.InsertParagraph("TEXT", 0);

		REQUIRE(document.GetItemsCount() == 1);
		auto paragraph = document.GetItem(0).GetParagraph();
		REQUIRE(paragraph != nullptr);
		REQUIRE(paragraph->GetText() == "TEXT");
	}

	SECTION("Add invalid position paragraph")
	{
		REQUIRE_THROWS(document.InsertParagraph("TEXT", 100));
	}

	SECTION("Add image")
	{
		document.InsertImage(".\\output.jpg", 200, 100, 0);

		REQUIRE(document.GetItemsCount() == 1);
		auto image = document.GetItem(0).GetImage();
		REQUIRE(image != nullptr);
		REQUIRE(image->GetWidth() == 200);
		REQUIRE(image->GetHeight() == 100);
	}

	SECTION("Add invalid position image")
	{
		REQUIRE_THROWS(document.InsertImage(".\\output.jpg", 200, 100, 200));
	}

	SECTION("Set title")
	{
		document.SetTitle("NEW TITLE");

		REQUIRE(document.GetTitle() == "NEW TITLE");
	}

	SECTION("Delete item")
	{
		document.InsertParagraph("paragraph", 0);
		document.InsertParagraph("paragraph1", 1);

		document.DeleteItem(0);
		auto firstParagraph = document.GetItem(0).GetParagraph();
		REQUIRE(document.GetItemsCount() == 1);
		REQUIRE(firstParagraph->GetText() == "paragraph1");
	}

	SECTION("Delete item wrong position")
	{
		REQUIRE_THROWS(document.DeleteItem(10));
	}

	SECTION("Undo")
	{
		document.InsertParagraph("text", 0);
		document.InsertParagraph("text", 1);

		document.Undo();
		document.Undo();

		REQUIRE_FALSE(document.CanUndo());
		REQUIRE(document.CanRedo());
		REQUIRE(document.GetItemsCount() == 0);
	}

	SECTION("Redo")
	{
		document.InsertParagraph("text0", 0);
		document.InsertParagraph("text1", 1);

		document.Undo();
		document.Undo();
		
		document.Redo();
		auto paragraph = document.GetItem(0).GetParagraph();
		REQUIRE(paragraph != nullptr);
		REQUIRE(paragraph->GetText() == "text0");
	}

	SECTION("Replace text")
	{
		document.InsertParagraph("text", 0);
		document.ReplaceText(0, "new text");

		auto paragraph = document.GetItem(0).GetParagraph();
		REQUIRE(paragraph != nullptr);
		REQUIRE(paragraph->GetText() == "new text");
	}

	SECTION("Replace text for image")
	{
		document.InsertImage(".\\output.jpg", 200, 100, 0);

		REQUIRE_THROWS(document.ReplaceText(0, "new text"));
	}

	SECTION("Resize image")
	{
		document.InsertImage(".\\output.jpg", 200, 100, 0);
		document.ResizeImage(0, 300, 400);

		auto image = document.GetItem(0).GetImage();
		REQUIRE(image != nullptr);
		REQUIRE(image->GetWidth() == 300);
		REQUIRE(image->GetHeight() == 400);
	}

	SECTION("Reisze image for text")
	{
		document.InsertParagraph("text", 0);

		REQUIRE_THROWS(document.ResizeImage(0, 300, 400));
	}
}