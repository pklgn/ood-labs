#pragma once

class RLECompressOutputStream : public CompressOutputStream
{
public:
	RLECompressOutputStream(IOutputStreamPtr&&);

protected:
	std::streamsize CompressBlock(void* dstData, const void* srcData, std::streamsize size) override;
};