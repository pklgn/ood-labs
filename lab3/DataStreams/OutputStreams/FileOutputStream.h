#pragma once

class FileOutputStream : public IOutputStream
{
public:
	FileOutputStream(const std::string fileName);

	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_outputFile;
};