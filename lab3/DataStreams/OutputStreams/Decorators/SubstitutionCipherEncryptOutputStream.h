#pragma once

class SubstitutionCipherEncryptOutputStream : public EncryptOutputStream
{
public:
	SubstitutionCipherEncryptOutputStream(uint32_t encryptKey, IOutputStreamPtr&&);

protected:
	uint8_t EncryptByte(uint8_t) override;

	void EncryptBlock(void* srcData, std::streamsize size) override;

private:
	uint32_t m_encryptKey;
	std::vector<uint8_t> m_encryptTable;
};