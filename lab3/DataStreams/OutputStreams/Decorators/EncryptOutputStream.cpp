#include "../../pch.h"

void EncryptOutputStream::WriteByte(uint8_t data)
{
	uint8_t encryptedByte = EncryptByte(data);

	m_outputStream->WriteByte(encryptedByte);
}

void EncryptOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	uint8_t* buffer = new uint8_t[size];
	std::memcpy(buffer, srcData, size * sizeof(uint8_t));

	EncryptBlock(buffer, size);

	m_outputStream->WriteBlock(buffer, size);
}

EncryptOutputStream::EncryptOutputStream(IOutputStreamPtr&& outputStream)
	: m_outputStream(std::move(outputStream))
{
}
