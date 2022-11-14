#include "../../pch.h"

DecryptInputStream::DecryptInputStream(IInputStreamPtr&& inputStream)
	: m_inputStream(std::move(inputStream))
{
}

bool DecryptInputStream::IsEOF() const
{
	return m_inputStream->IsEOF();
}

uint8_t DecryptInputStream::ReadByte()
{
	uint8_t encryptedByte = m_inputStream->ReadByte();

	return DecryptByte(encryptedByte);
}

std::streamsize DecryptInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	std::streamsize actualReadSize = m_inputStream->ReadBlock(dstBuffer, size);

	DecryptBlock(dstBuffer, actualReadSize);

	return actualReadSize;
}
