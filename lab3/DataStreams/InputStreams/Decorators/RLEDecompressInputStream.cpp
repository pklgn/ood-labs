#include "../../pch.h"

RLEDecompressInputStream::RLEDecompressInputStream(IInputStreamPtr&& inputStream)
	: DecompressInputStream(std::move(inputStream))
{
}

uint32_t RLEDecompressInputStream::DecompressByte(void* dstBuffer, const void* srcBuffer)
{
	uint8_t length = reinterpret_cast<const uint8_t*>(srcBuffer)[0];
	uint8_t value = reinterpret_cast<const uint8_t*>(srcBuffer)[1];
	
	uint8_t* result = new uint8_t[length];
	for (uint8_t position = 0; position < length; ++position)
	{
		result[position] = value;
	}

	std::memcpy(dstBuffer, result, length);

	return length;
}

void RLEDecompressInputStream::DecompressBlock(void* dstBuffer, uint32_t RLECount)
{
	uint8_t* compressBuffer = new uint8_t[RLECount * 2];
	std::memcpy(compressBuffer, dstBuffer, RLECount * 2);
	uint32_t RLELength = 0;
	for (uint32_t RLENumber = 0; RLENumber < RLECount; ++RLENumber)
	{
		RLELength += DecompressByte(reinterpret_cast<uint8_t*>(dstBuffer) + RLELength * sizeof(uint8_t), reinterpret_cast<uint8_t*>(compressBuffer) + 2 * RLENumber);
	}
}
