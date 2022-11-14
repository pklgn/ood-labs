#pragma once

class MemoryInputStream : public IInputStream
{
public:
	MemoryInputStream(const std::vector<uint8_t>& input);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::vector<uint8_t> m_inputStorage;
	std::vector<uint8_t>::iterator m_inputStorageIterator;
};