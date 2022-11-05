#include "../pch.h"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Commands/DeleteItemCommand.h"
#include "Commands/InsertImageCommand.h"
#include "Commands/InsertParagraphCommand.h"
#include "Commands/SetTitleCommand.h"
#include "Commands/ReplaceTextCommand.h"
#include "Commands/ResizeImageCommand.h"
#include "DocumentItems/Elements/Image/Image.h"
#include "DocumentItems/Elements/Paragraph/Paragraph.h"
#include "HTMLDocument.h"

const std::string IMAGE_FILENAME_PREFIX = "img";
const std::string HTML_DOCUMENT_FILENAME_PREFIX = "Untitled";
const std::string IMAGES_DIRECTORY = "images";
const auto PLATFORM_SEPARATOR = std::filesystem::path::preferred_separator;

namespace fs = std::filesystem;

std::string GetCurrentDateTimeString();
Path GetRelativeImagePath(const Path& path);
std::string Trim(const std::string& str);
std::string HTMLEncode(const std::string& data);
void SaveHtmlDocumentItem(std::ofstream&, ConstDocumentItem&, const Path&);
void SaveHtmlDocumentImageItem(std::ofstream&, std::shared_ptr<const IImage>, const Path&);
void SaveHtmlDocumentParagraphItem(std::ofstream&, std::shared_ptr<const IParagraph>);

HTMLDocument::HTMLDocument()
	: m_title(HTML_DOCUMENT_FILENAME_PREFIX + GetCurrentDateTimeString())
{
	SetSavePath(fs::current_path().string());
}

std::shared_ptr<IParagraph> HTMLDocument::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
	auto insertPosition = ValidatePosition(position);

	auto paragraphPtr = std::make_shared<Paragraph>(text);

	m_history.AddAndExecuteCommand(std::make_unique<InsertParagraphCommand>(m_items, paragraphPtr, insertPosition));

	return paragraphPtr;
}

//TODO: вынести построение относительного пути в функцию
std::shared_ptr<IImage> HTMLDocument::InsertImage(const Path& path, size_t width, size_t height, std::optional<size_t> position)
{
	Path imagePath = CopyImage(path);

	auto insertPosition = ValidatePosition(position);
	auto imagePtr = std::make_shared<Image>(width, height, imagePath);

	m_history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(m_items, imagePtr, insertPosition));

	return imagePtr;
}

size_t HTMLDocument::GetItemsCount() const
{
	return m_items.size();
}

ConstDocumentItem HTMLDocument::GetItem(size_t index) const
{
	if (m_items.size() <= index)
	{
		throw std::out_of_range("Item index is out of range");
	}

	return m_items.at(index);
}

DocumentItem HTMLDocument::GetItem(size_t index)
{
	if (m_items.size() <= index)
	{
		throw std::out_of_range("Item index is out of range");
	}

	return m_items.at(index);
}

void HTMLDocument::DeleteItem(size_t index)
{
	if (m_items.size() <= index)
	{
		throw std::out_of_range("Index is out of range");
	}

	m_history.AddAndExecuteCommand(std::make_unique<DeleteItemCommand>(m_items, index));
}

std::string HTMLDocument::GetTitle() const
{
	return m_title;
}

void HTMLDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(m_title, title));
}

bool HTMLDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void HTMLDocument::Undo()
{
	m_history.Undo();
}

bool HTMLDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void HTMLDocument::Redo()
{
	m_history.Redo();
}

//TODO: добавить копирование images/ при сохранении
void HTMLDocument::Save(const Path& path) const
{
	fs::path fsPath = path;
	if (!fsPath.empty() && fsPath.generic_string().back() != PLATFORM_SEPARATOR)
	{
		fsPath += PLATFORM_SEPARATOR;
	}
	fs::path savedImagesDirectory = fsPath.string() + IMAGES_DIRECTORY;

	if (!fs::exists(savedImagesDirectory))
	{
		fs::create_directory(savedImagesDirectory);
	}

	std::ofstream outputFile(fsPath.string() + m_title + ".html");

	outputFile << "<html>\n"
			   << "<head>\n"
			   << "<title>" << HTMLEncode(m_title) << "</title>\n"
			   << "</html>\n"
			   << "<body>\n";

	for (size_t itemIndex = 0; itemIndex < m_items.size(); ++itemIndex)
	{
		auto item = GetItem(itemIndex);
		SaveHtmlDocumentItem(outputFile, item, fsPath.string());
	}

	outputFile << "</body>\n";
	outputFile << "</html>\n";
}

void HTMLDocument::SetSavePath(const Path& path)
{
	fs::path fsPath = path;
	if (!fsPath.empty() && fsPath.generic_string().back() != PLATFORM_SEPARATOR)
	{
		fsPath += PLATFORM_SEPARATOR;
	}

	m_savePath = fsPath.string();
}

void HTMLDocument::ReplaceText(size_t index, const std::string& newText)
{
	auto item = GetItem(index);
	auto paragraph = item.GetParagraph();
	if (paragraph == nullptr)
	{
		throw std::runtime_error("Couldn't replace text for non-paragraph document item");
	}

	m_history.AddAndExecuteCommand(std::make_unique<ReplaceTextCommand>(paragraph, newText));
}

void HTMLDocument::ResizeImage(size_t index, size_t width, size_t height)
{
	auto item = GetItem(index);
	auto image = item.GetImage();
	if (image == nullptr)
	{
		throw std::runtime_error("Couldn't resize non-image document item");
	}

	m_history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(image, width, height));
}

size_t HTMLDocument::ValidatePosition(const std::optional<size_t>& position)
{
	if (m_items.size() < position)
	{
		throw std::invalid_argument("Position argument must not exceed the number of elements in the document");
	}

	return position.value_or(m_items.size());
}

std::string Trim(const std::string& str)
{
	auto result = str;
	result.erase(str.find_last_not_of(' ') + 1); // suffixing spaces
	result.erase(0, str.find_first_not_of(' ')); // prefixing spaces

	return result;
}

void SaveHtmlDocumentItem(std::ofstream& output, ConstDocumentItem& item, const Path& path)
{
	auto imagePtr = item.GetImage();
	auto paragraphPtr = item.GetParagraph();

	if (imagePtr != nullptr)
	{
		SaveHtmlDocumentImageItem(output, imagePtr, path);
	}
	else if (paragraphPtr != nullptr)
	{
		SaveHtmlDocumentParagraphItem(output, paragraphPtr);
	}
}

void SaveHtmlDocumentImageItem(std::ofstream& output, std::shared_ptr<const IImage> imagePtr, const Path& path)
{
	Path trimmedPath = Trim(path);
	Path imagePath = imagePtr->GetPath();
	if (!fs::exists(trimmedPath + imagePath))
	{
		fs::copy_file(imagePath, trimmedPath + imagePath);
	}

	output << "<img "
		   << "src=" << HTMLEncode(imagePtr->GetPath()) << "\n\t"
		   << "width=" << imagePtr->GetWidth() << "\n\t"
		   << "height=" << imagePtr->GetHeight() << "\n\t"
		   << "/>\n";
}

void SaveHtmlDocumentParagraphItem(std::ofstream& output, std::shared_ptr<const IParagraph> paragraphPtr)
{
	output << "<p>"
		   << HTMLEncode(Trim(paragraphPtr->GetText()))
		   << "</p>\n";
}

std::string HTMLEncode(const std::string& data)
{
	std::string buffer;
	buffer.reserve(data.size());
	for (size_t pos = 0; pos != data.size(); ++pos)
	{
		switch (data[pos])
		{
		case '&':
			buffer.append("&amp;");
			break;
		case '\"':
			buffer.append("&quot;");
			break;
		case '\'':
			buffer.append("&apos;");
			break;
		case '<':
			buffer.append("&lt;");
			break;
		case '>':
			buffer.append("&gt;");
			break;
		default:
			buffer.append(&data[pos], 1);
			break;
		}
	}

	return buffer;
}

std::string GetCurrentDateTimeString()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d%m%Y%H%M%S", timeinfo);
	std::string str(buffer);

	return str;
}

Path GetRelativeImagePath(const Path& path)
{
	fs::path filePath = path;
	std::string imageFileName = IMAGE_FILENAME_PREFIX + GetCurrentDateTimeString() + filePath.extension().string();

	fs::path relativePath;
	relativePath += IMAGES_DIRECTORY;
	relativePath += PLATFORM_SEPARATOR;
	relativePath += imageFileName;

	return relativePath.string();
}

Path HTMLDocument::CopyImage(const Path& srcPath)
{
	if (!fs::exists(IMAGES_DIRECTORY))
	{
		fs::create_directory(IMAGES_DIRECTORY);
	}

	Path relativePath = GetRelativeImagePath(srcPath);
	fs::path imagePath = m_savePath + relativePath;

	fs::copy_file(Trim(srcPath), imagePath);

	return relativePath;
}