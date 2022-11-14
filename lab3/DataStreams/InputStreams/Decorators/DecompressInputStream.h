#pragma once

class DecompressInputStream : public IInputStream
{
public:
	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

	virtual uint32_t DecompressByte(void* dstBuffer, const void* srcBuffer) = 0;

	virtual void DecompressBlock(void* dstBuffer, uint32_t RLECount) = 0;

protected:
	DecompressInputStream(IInputStreamPtr&& inputStream);

private:
	IInputStreamPtr m_inputStream;
};