#include "../pch.h"

MemoryInputStream::MemoryInputStream(const std::vector<uint8_t>& input)
	: m_memoryStorage(input)
	, m_memoryStorageIterator(m_memoryStorage.begin())
{
}

bool MemoryInputStream::IsEOF() const
{
	return m_memoryStorageIterator != m_memoryStorage.end();
}

uint8_t MemoryInputStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios_base::failure("EOF was found while reading the file\n");
	}

	return *m_memoryStorageIterator++;
}

std::streamsize MemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (IsEOF())
	{
		throw std::ios_base::failure("EOF was found while reading the file\n");
	}

	std::streamsize actualSize = std::min(size, std::distance(m_memoryStorageIterator, m_memoryStorage.end()));

	std::memcpy(dstBuffer, &(*m_memoryStorageIterator), actualSize);

	return actualSize;
}
