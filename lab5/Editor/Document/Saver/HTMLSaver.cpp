#include "../../pch.h"
#include "HTMLSaver.h"
#include "../../common/StringCommon.h"

namespace fs = std::filesystem;

const std::string IMAGES_DIRECTORY = "images";
const auto PLATFORM_SEPARATOR = std::filesystem::path::preferred_separator;

std::string HTMLEncode(const std::string& data);

HTMLSaver::HTMLSaver(IDocument& document)
	: m_document(document)
{
}

void HTMLSaver::Save(const Path& path) const
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

	std::ofstream outputFile(fsPath.string() + m_document.GetTitle() + ".html");

	outputFile << "<html>\n"
			   << "<head>\n"
			   << "<title>" << HTMLEncode(m_document.GetTitle()) << "</title>\n"
			   << "</html>\n"
			   << "<body>\n";

	for (size_t itemIndex = 0; itemIndex < m_document.GetItemsCount(); ++itemIndex)
	{
		auto item = m_document.GetItem(itemIndex);
		SaveHtmlDocumentItem(outputFile, item, path);
	}

	outputFile << "</body>\n";
	outputFile << "</html>\n";
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

void HTMLSaver::SaveHtmlDocumentItem(std::ostream& output, ConstDocumentItem& item, const Path& path) const
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

void HTMLSaver::SaveHtmlDocumentImageItem(std::ostream& output, std::shared_ptr<const IImage> imagePtr, const Path& path) const
{
	Path trimmedPath = Trim(path);
	Path imagePath = imagePtr->GetPath();
	if (!fs::exists(trimmedPath + imagePath))
	{
		fs::copy_file(imagePath, trimmedPath + imagePath);
	}

	output << "<div><img "
		   << "src=" << HTMLEncode(imagePtr->GetPath()) << "\n\t"
		   << "width=" << imagePtr->GetWidth() << "\n\t"
		   << "height=" << imagePtr->GetHeight() << "\n\t"
		   << "/></div>\n";
}

void HTMLSaver::SaveHtmlDocumentParagraphItem(std::ostream& output, std::shared_ptr<const IParagraph> paragraphPtr) const
{
	output << "<p>"
		   << HTMLEncode(Trim(paragraphPtr->GetText()))
		   << "</p>\n";
}