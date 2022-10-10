#pragma once

typedef std::unique_ptr<IInputStream> IInputStreamPtr;

class DecryptInputStream : public IInputStream
{
public:
	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

	virtual uint8_t DecryptByte(uint8_t) = 0;

	virtual void DecryptBlock(void* dstBuffer, std::streamsize size) = 0;

protected:
	DecryptInputStream(IInputStreamPtr&& inputStream);

private:
	IInputStreamPtr m_inputStream;
};