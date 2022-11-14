#include "../../pch.h"

void CompressOutputStream::WriteByte(uint8_t data)
{
	m_outputStream->WriteByte('1');
	m_outputStream->WriteByte(data);
}

void CompressOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	uint8_t* compressBuffer = new uint8_t[size];
	std::streamsize actualSize = CompressBlock(compressBuffer, srcData, size);
	m_outputStream->WriteBlock(compressBuffer, actualSize);
}

CompressOutputStream::CompressOutputStream(IOutputStreamPtr&& outputStream)
	: m_outputStream(std::move(outputStream))
{
}
