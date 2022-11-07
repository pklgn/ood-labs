#include "../../pch.h"
#include "InsertImageCommand.h"
#include "../../common/StringCommon.h"

const std::string IMAGE_FILENAME_PREFIX = "img";
const std::string IMAGES_DIRECTORY = "images";

namespace fs = std::filesystem;

Path CopyImage(const Path& srcPath);
Path GetRelativeImagePath(const Path& path);

InsertImageCommand::InsertImageCommand(std::vector<DocumentItem>& items, const std::shared_ptr<IImage>& imagePtr, size_t position)
	: m_items(items)
	, m_imagePtr(imagePtr)
	, m_position(position)
{
	if (items.size() < m_position)
	{
		throw std::out_of_range("Position out of range");
	}

	auto imagePath = CopyImage(m_imagePtr->GetPath());
	
	m_imagePtr->SetPath(imagePath);
}

InsertImageCommand::~InsertImageCommand()
{
	fs::path removePath = fs::current_path();
	removePath += fs::path::preferred_separator;
	removePath += m_imagePtr->GetPath();
	if (!WasExecuted())
	{
		fs::remove(removePath);
	}
}

void InsertImageCommand::DoExecute()
{
	if (m_position == m_items.size())
	{
		m_items.push_back(DocumentItem(m_imagePtr));
	}
	else
	{
		m_items.insert(m_items.begin() + m_position, DocumentItem(m_imagePtr));
	}
}

void InsertImageCommand::DoUnexecute()
{
	m_items.erase(m_items.begin() + m_position);
}


Path GetRelativeImagePath(const Path& path)
{
	fs::path filePath = path;
	std::string imageFileName = IMAGE_FILENAME_PREFIX + GetCurrentDateTimeString() + filePath.extension().string();

	fs::path relativePath;
	relativePath += IMAGES_DIRECTORY;
	relativePath += std::filesystem::path::preferred_separator;
	relativePath += imageFileName;

	return relativePath.string();
}

Path CopyImage(const Path& srcPath)
{
	Path relativePath;
	try
	{
		if (!fs::exists(IMAGES_DIRECTORY))
		{
			fs::create_directory(IMAGES_DIRECTORY);
		}

		relativePath = GetRelativeImagePath(srcPath);

		fs::copy_file(srcPath, relativePath, fs::copy_options::overwrite_existing);
	}
	catch (...)
	{
		throw std::runtime_error("Fail to copy image with specified path");
	}

	return relativePath;
}
