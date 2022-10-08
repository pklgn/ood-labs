#pragma once

class FileInputStream : public IInputStream
{
public:
	FileInputStream(const std::string& fileName);

	bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::ifstream m_inputFile;
};