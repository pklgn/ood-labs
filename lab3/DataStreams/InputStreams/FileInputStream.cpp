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
	if (m_inputFile.fail())
	{
		throw std::ios_base::failure("Specified file seems not good");
	}

	return m_inputFile.eof();
}

uint8_t FileInputStream::ReadByte()
{
	uint8_t byte;

	if (IsEOF())
	{
		throw std::ios_base::failure("EOF was found\n");
	}

	m_inputFile >> byte;

	if (!m_inputFile)
	{
		throw std::ios_base::failure("Error was found while reading the file\n");
	}

	return byte;
}

std::streamsize FileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
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

