#include "../pch.h"

void MemoryOutputStream::WriteByte(uint8_t data)
{
	try
	{
		m_outputStorage.push_back(data);
	}
	catch (...)
	{
		throw std::ios_base::failure("Couldn't write byte to the stream\n");
	}
}

void MemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	try
	{
		m_outputStorage.resize(m_outputStorage.size() + size);
		std::memcpy(&m_outputStorage.back(), srcData, size * sizeof(uint8_t));
	}
	catch (...)
	{
		throw std::ios_base::failure("Couldn't write specified data to the stream\n");
	}
}
