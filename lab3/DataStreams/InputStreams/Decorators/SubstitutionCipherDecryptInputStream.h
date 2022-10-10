#pragma once

class SubstitutionCipherDecryptInputStream : public DecryptInputStream
{
public:
	SubstitutionCipherDecryptInputStream(uint8_t decryptKey, IInputStreamPtr&&);

protected:
	uint8_t DecryptByte(uint8_t) override;

	void DecryptBlock(void* dstBuffer, std::streamsize size) override;

private:
	uint8_t m_decryptKey;
	std::vector<uint8_t> m_decryptTable;
};