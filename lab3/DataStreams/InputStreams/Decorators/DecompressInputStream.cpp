#include "../../pch.h"

bool DecompressInputStream::IsEOF() const
{
	return m_inputStream->IsEOF();
}

uint8_t DecompressInputStream::ReadByte()
{
	return m_inputStream->ReadByte();
}

std::streamsize DecompressInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto actualSize = m_inputStream->ReadBlock(dstBuffer, size * 2);

	DecompressBlock(dstBuffer, size);

	return actualSize;
}

DecompressInputStream::DecompressInputStream(IInputStreamPtr&& inputStream)
	: m_inputStream(std::move(inputStream))
{
}
