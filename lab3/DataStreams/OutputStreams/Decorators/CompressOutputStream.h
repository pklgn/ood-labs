#pragma once

typedef std::unique_ptr<IOutputStream> IOutputStreamPtr;

class CompressOutputStream : public IOutputStream
{
public:
	void WriteByte(uint8_t data) override;

	void WriteBlock(const void* srcData, std::streamsize size) override;

	virtual std::streamsize CompressBlock(void* dstData, const void* srcData, std::streamsize size) = 0;

protected:
	CompressOutputStream(IOutputStreamPtr&& outputStream);

private:
	IOutputStreamPtr m_outputStream;
};