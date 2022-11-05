#include "../pch.h"
#include <ctime>
#include <filesystem>
#include <format>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Commands/DeleteItemCommand.h"
#include "Commands/InsertImageCommand.h"
#include "Commands/InsertParagraphCommand.h"
#include "DocumentItems/Elements/Image/Image.h"
#include "DocumentItems/Elements/Paragraph/Paragraph.h"
#include "HTMLDocument.h"

const std::string IMAGE_FILENAME_PREFIX = "img";
const std::string HTML_DOCUMENT_FILENAME_PREFIX = "Untitled";
const std::string IMAGES_DIRECTORY = "images/";

namespace fs = std::filesystem;

std::string GetCurrentDateTimeString();
Path GetRelativeImagePath(const Path& path);
std::string Trim(const std::string& str);
std::string HTMLEncode(const std::string& data);
void SaveHtmlDocumentItem(std::ofstream&, ConstDocumentItem&);
void SaveHtmlDocumentImageItem(std::ofstream&, std::shared_ptr<const IImage>);
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
	Path relativeImagePath = GetRelativeImagePath(path);
	std::ofstream(m_savePath + relativeImagePath, std::ios::binary) << std::ifstream(path, std::ios::binary).rdbuf();

	auto insertPosition = ValidatePosition(position);
	auto imagePtr = std::make_shared<Image>(width, height, relativeImagePath);

	m_history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(m_items, imagePtr, insertPosition, m_savePath + relativeImagePath));

	return imagePtr;
}

size_t HTMLDocument::GetItemsCount() const
{
	return m_items.size();
}

ConstDocumentItem HTMLDocument::GetItem(size_t index) const
{
	return m_items.at(index);
}

DocumentItem HTMLDocument::GetItem(size_t index)
{
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
	m_title = title;
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
void HTMLDocument::Save() const
{
	std::ofstream outputFile(m_savePath + m_title + ".html");

	outputFile << "<html>\n"
			   << "<head>\n"
			   << "<title>" << HTMLEncode(m_title) << "</title>\n"
			   << "</html>\n"
			   << "<body>\n";

	for (size_t itemIndex = 0; itemIndex < m_items.size(); ++itemIndex)
	{
		auto item = GetItem(itemIndex);
		SaveHtmlDocumentItem(outputFile, item);
	}

	outputFile << "</body>\n";
	outputFile << "</html>\n";
}

Path HTMLDocument::GetSavePath() const
{
	return m_savePath;
}

void HTMLDocument::SetSavePath(const Path& path)
{
	m_savePath = Trim(path);
	if (m_savePath.back() != '/')
	{
		m_savePath.push_back('/');
	}
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

void SaveHtmlDocumentItem(std::ofstream& output, ConstDocumentItem& item)
{
	auto imagePtr = item.GetImage();
	auto paragraphPtr = item.GetParagraph();

	if (imagePtr != nullptr)
	{
		SaveHtmlDocumentImageItem(output, imagePtr);
	}
	else if (paragraphPtr != nullptr)
	{
		SaveHtmlDocumentParagraphItem(output, paragraphPtr);
	}
}

void SaveHtmlDocumentImageItem(std::ofstream& output, std::shared_ptr<const IImage> imagePtr)
{
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

	return IMAGES_DIRECTORY + imageFileName;
}