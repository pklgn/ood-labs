#include "../../pch.h"

constexpr int ALPHABET_SIZE = 256;

SubstitutionCipherEncryptOutputStream::SubstitutionCipherEncryptOutputStream(uint32_t encryptKey, IOutputStreamPtr&& outputStream)
	: EncryptOutputStream(std::move(outputStream))
	, m_encryptKey(encryptKey)
{
	m_encryptTable.resize(ALPHABET_SIZE);
	std::iota(m_encryptTable.begin(), m_encryptTable.end(), 0);

	std::shuffle(m_encryptTable.begin(), m_encryptTable.end(), std::mt19937(m_encryptKey));
}
//TODO: вынести в стат класс реализацию создания таблицы

uint8_t SubstitutionCipherEncryptOutputStream::EncryptByte(uint8_t data)
{
	return m_encryptTable[data];
}

void SubstitutionCipherEncryptOutputStream::EncryptBlock(void* srcData, std::streamsize size)
{
	for (std::streamsize bytePosition = 0; bytePosition < size; ++bytePosition)
	{
		reinterpret_cast<uint8_t*>(srcData)[bytePosition] = m_encryptTable[reinterpret_cast<uint8_t*>(srcData)[bytePosition]];
	}
}
