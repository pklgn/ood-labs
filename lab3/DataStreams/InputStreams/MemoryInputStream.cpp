#include "../pch.h"

MemoryInputStream::MemoryInputStream(const std::vector<uint8_t>& input)
{
	m_inputStorage = input;
	m_inputStorageIterator = m_inputStorage.begin();
}

bool MemoryInputStream::IsEOF() const
{
	return m_inputStorageIterator == m_inputStorage.end();
}

uint8_t MemoryInputStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios_base::failure("EOF was found\n");
	}

	return *m_inputStorageIterator++;
}

std::streamsize MemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (IsEOF())
	{
		throw std::ios_base::failure("EOF was found\n");
	}

	std::streamsize actualSize = std::min(size, std::distance(m_inputStorageIterator, m_inputStorage.end()));

	std::memcpy(dstBuffer, &(*m_inputStorageIterator), actualSize * sizeof(uint8_t));
	m_inputStorageIterator += actualSize;

	return actualSize;
}
