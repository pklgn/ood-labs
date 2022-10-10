#pragma once

class EncryptOutputStream : public IOutputStream
{
public:
	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

	virtual uint8_t EncryptByte(uint8_t) = 0;

	virtual void EncryptBlock(void* srcData, std::streamsize size) = 0;

protected:
	EncryptOutputStream(IOutputStreamPtr&& outputStream);

private:
	IOutputStreamPtr m_outputStream;
};