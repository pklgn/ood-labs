#include "../pch.h"

FileInputStream::FileInputStream(const std::string& fileName)
	: m_inputFile(fileName)
{
	if (!m_inputFile)
	{
		throw std::runtime_error("Couldn't open " + fileName + " file\n");
	}
}

bool FileInputStream::IsEOF() const
{
	return m_inputFile.eof();
}

uint8_t FileInputStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios_base::failure("EOF was found\n");
	}

	uint8_t byte = 0;
	ReadBlock(&byte, 1);

	if (IsEOF())
	{
		throw std::ios_base::failure("Trying to read EOF\n");
	}

	return byte;
}

std::streamsize FileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (dstBuffer == nullptr)
	{
		throw std::ios_base::failure("Couldn't read data to null memory pointer\n");
	}

	try
	{
		m_inputFile.read(reinterpret_cast<char*>(dstBuffer), size);
	}
	catch (...)
	{
		throw std::ios_base::failure("Error was found while reading the file\n");
	}

	return m_inputFile.gcount();
}

