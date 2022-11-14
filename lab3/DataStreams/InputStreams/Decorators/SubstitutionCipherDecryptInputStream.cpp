#include "../../pch.h"

constexpr int ALPHABET_SIZE = 256;

SubstitutionCipherDecryptInputStream::SubstitutionCipherDecryptInputStream(uint8_t decryptKey, IInputStreamPtr&& inputStream)
	: DecryptInputStream(std::move(inputStream))
	, m_decryptKey(decryptKey)
{
	std::vector<uint8_t> cryptTable(ALPHABET_SIZE);
	std::iota(cryptTable.begin(), cryptTable.end(), 0);

	std::shuffle(cryptTable.begin(), cryptTable.end(), std::mt19937(m_decryptKey));

	m_decryptTable.resize(ALPHABET_SIZE);

	std::for_each(cryptTable.begin(), cryptTable.end(), [&, decryptedByte = 0](uint8_t encryptedByte) mutable {
		m_decryptTable[encryptedByte] = decryptedByte++;
	});
}

uint8_t SubstitutionCipherDecryptInputStream::DecryptByte(uint8_t encryptedByte)
{
	return m_decryptTable[encryptedByte];
}

void SubstitutionCipherDecryptInputStream::DecryptBlock(void* dstBuffer, std::streamsize size)
{
	for (std::streamsize bytePosition = 0; bytePosition < size; bytePosition++)
	{
		reinterpret_cast<uint8_t*>(dstBuffer)[bytePosition] = m_decryptTable[reinterpret_cast<uint8_t*>(dstBuffer)[bytePosition]];
	}
}
