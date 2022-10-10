#pragma once

typedef std::pair<uint32_t, uint8_t> RLEPair;

class RLEDecompressInputStream : public DecompressInputStream
{
public:
	RLEDecompressInputStream(IInputStreamPtr&& inputStream);

protected:
	uint32_t DecompressByte(void* dstBuffer, const void* srcBuffer) override;

	void DecompressBlock(void* dstBuffer, uint32_t RLECount) override;
};