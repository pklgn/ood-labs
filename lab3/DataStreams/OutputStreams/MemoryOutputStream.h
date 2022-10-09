#pragma once

class MemoryOutputStream : public IOutputStream
{
public:
	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::vector<uint8_t> m_outputStorage;
};