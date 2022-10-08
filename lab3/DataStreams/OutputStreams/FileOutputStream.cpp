#include "../pch.h"

FileOutputStream::FileOutputStream(const std::string fileName)
	: m_outputFile(fileName)
{
	if (!m_outputFile)
	{
		throw std::runtime_error("Couldn't open " + fileName + " file\n");
	}
}

void FileOutputStream::WriteByte(uint8_t data)
{
	if (m_outputFile)
	{
		m_outputFile << data;
	}

	if (m_outputFile.fail())
	{
		throw std::ios_base::failure("Error was found while writing into the file\n");
	}
}

void FileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	if (srcData == nullptr)
	{
		throw std::ios_base::failure("Couldn't write data from null memory pointer\n");
	}

	try
	{
		m_outputFile.write(reinterpret_cast<const char*>(srcData), size);
	}
	catch (...)
	{
		throw std::ios_base::failure("Error was found while writing into the file\n");
	}
}
