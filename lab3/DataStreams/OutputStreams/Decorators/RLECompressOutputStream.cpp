#include "../../pch.h"

RLECompressOutputStream::RLECompressOutputStream(IOutputStreamPtr&& outputStream)
	: CompressOutputStream(std::move(outputStream))
{
}

std::streamsize RLECompressOutputStream::CompressBlock(void* dstData, const void* srcData, std::streamsize size)
{
	std::streamsize RLEPairSize = 0;

	for (uint8_t srcPosition = 0; srcPosition < size; ++srcPosition)
	{
		uint8_t count = 1;
		const uint8_t* byte = reinterpret_cast<const uint8_t*>(srcData) + srcPosition;
		while (*byte == reinterpret_cast<const uint8_t*>(srcData)[srcPosition + 1])
		{
			count++;
			srcPosition++;
		}

		reinterpret_cast<uint8_t*>(dstData)[RLEPairSize * 2] = count;
		reinterpret_cast<uint8_t*>(dstData)[RLEPairSize * 2 + 1] = *byte;
		++RLEPairSize;
	}

	return RLEPairSize * 2;
}
