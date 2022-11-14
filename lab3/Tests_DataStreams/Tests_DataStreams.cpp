#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../DataStreams/pch.h"

const std::string SINGLE_LINE_FILENAME = "single_line.test.txt";
const std::string MULTIPLE_LINES_FILENAME = "multiple_lines.test.txt";
const std::string NO_LINES_FILENAME = "empty.test.txt";
const std::string OUTPUT_FILENAME = "output.test.txt";
constexpr size_t SINGLE_LINE_FILE_CONTENT_SIZE = 6;
constexpr size_t MULTIPLE_LINES_FILE_CONTENT_SIZE = 20;
constexpr size_t NO_LINES_FILE_CONTENT_SIZE = 0;

// Tests for InputStreams
TEST_CASE("Check file input stream constructor for not existing file")
{
	std::unique_ptr<FileInputStream> fileInputStreamPtr;

	REQUIRE_THROWS(fileInputStreamPtr.reset(new FileInputStream("fileDoesntExist.txt")));
}

TEST_CASE("Check file input stream constructor for an existing empty file")
{
	std::unique_ptr<FileInputStream> fileInputStreamPtr;

	REQUIRE_NOTHROW(fileInputStreamPtr.reset(new FileInputStream(NO_LINES_FILENAME)));
}

TEST_CASE("Check file input stream constructor for an existing not-empty file")
{
	std::unique_ptr<FileInputStream> fileInputStreamPtr;

	REQUIRE_NOTHROW(fileInputStreamPtr.reset(new FileInputStream(SINGLE_LINE_FILENAME)));
}

TEST_CASE("Check IsEOF() for a single line file")
{
	FileInputStream fileInputStream(SINGLE_LINE_FILENAME);
	REQUIRE_FALSE(fileInputStream.IsEOF());

	char* buffer = new char[SINGLE_LINE_FILE_CONTENT_SIZE];
	fileInputStream.ReadBlock(buffer, SINGLE_LINE_FILE_CONTENT_SIZE);
	REQUIRE_FALSE(fileInputStream.IsEOF());

	REQUIRE_THROWS(fileInputStream.ReadByte());
	REQUIRE(fileInputStream.IsEOF());
}

TEST_CASE("Check IsEOF() for a multiline file")
{
	FileInputStream fileInputStream(MULTIPLE_LINES_FILENAME);
	REQUIRE_FALSE(fileInputStream.IsEOF());

	char* buffer = new char[MULTIPLE_LINES_FILE_CONTENT_SIZE];
	//read past the eof
	fileInputStream.ReadBlock(buffer, MULTIPLE_LINES_FILE_CONTENT_SIZE + 1);

	REQUIRE(fileInputStream.IsEOF());
}

TEST_CASE("Check IsEOF() for an empty file")
{
	FileInputStream fileInputStream(NO_LINES_FILENAME);
	REQUIRE_FALSE(fileInputStream.IsEOF());

	// read past the eof
	REQUIRE_THROWS(fileInputStream.ReadByte());

	REQUIRE(fileInputStream.IsEOF());
}

TEST_CASE("Read byte from file stream consistently")
{
	FileInputStream fileInputStream(SINGLE_LINE_FILENAME);

	std::vector<uint8_t> fileContent;
	fileContent.push_back(fileInputStream.ReadByte());
	REQUIRE(fileContent.back() == 's');

	fileContent.push_back(fileInputStream.ReadByte());
	REQUIRE(fileContent.back() == 'i');

	fileContent.push_back(fileInputStream.ReadByte());
	REQUIRE(fileContent.back() == 'm');
}

TEST_CASE("Try reading byte from file stream when EOF appear")
{
	FileInputStream fileInputStream(SINGLE_LINE_FILENAME);

	for (size_t i = 0; i < SINGLE_LINE_FILE_CONTENT_SIZE; ++i)
	{
		fileInputStream.ReadByte();
	}

	//attempt to read eof
	REQUIRE_THROWS(fileInputStream.ReadByte());
}

TEST_CASE("Read block of data from file stream consistently")
{
	FileInputStream fileInputStream(SINGLE_LINE_FILENAME);

	size_t firstBlockSize = 4;
	char* firstBlock = new char[firstBlockSize];
	fileInputStream.ReadBlock(firstBlock, firstBlockSize);

	size_t secondBlockSize = 2;
	char* secondBlock = new char[secondBlockSize];
	fileInputStream.ReadBlock(secondBlock, secondBlockSize);

	std::vector<uint8_t> expectedFirstBlock{ 's', 'i', 'm', 'p' };
	std::vector<uint8_t> expectedSecondBlock{ 'l', 'e' };
	
	for (size_t i = 0; i < firstBlockSize; ++i)
	{
		REQUIRE(firstBlock[i] == expectedFirstBlock[i]);
	}

	for (size_t i = 0; i < secondBlockSize; ++i)
	{
		REQUIRE(secondBlock[i] == secondBlock[i]);
	}
}

TEST_CASE("Try reading block of data from file stream when EOF appear")
{
	FileInputStream fileInputStream(MULTIPLE_LINES_FILENAME);
	char* buffer = new char[MULTIPLE_LINES_FILE_CONTENT_SIZE];

	std::streamsize actualReadSize = fileInputStream.ReadBlock(buffer, MULTIPLE_LINES_FILE_CONTENT_SIZE);
	REQUIRE(actualReadSize == MULTIPLE_LINES_FILE_CONTENT_SIZE);
	
	std::streamsize readSizePastEOF = fileInputStream.ReadBlock(buffer, 2);
	REQUIRE(readSizePastEOF == 0);
}

TEST_CASE("Check memory input constructor")
{
	std::unique_ptr<MemoryInputStream> memoryInputStreamPtr;
	REQUIRE_NOTHROW(memoryInputStreamPtr.reset(new MemoryInputStream(std::vector<uint8_t>{})));

	REQUIRE_NOTHROW(memoryInputStreamPtr.reset(new MemoryInputStream(std::vector<uint8_t>{ '1', '2' })));
}

TEST_CASE("Check IsEOF() method for an empty memory stream")
{
	MemoryInputStream memoryInputStream(std::vector<uint8_t>{});

	REQUIRE(memoryInputStream.IsEOF());
}

TEST_CASE("Check IsEOF() method for non-empty memory stream")
{
	MemoryInputStream memoryInputStream(std::vector<uint8_t>{ 't', 'e', 's', 't' });

	REQUIRE_FALSE(memoryInputStream.IsEOF());

	char* buffer = new char[4];
	memoryInputStream.ReadBlock(buffer, 4);

	REQUIRE(memoryInputStream.IsEOF());
}

TEST_CASE("Check block memory read past EOF for an empty memory stream")
{
	std::vector<uint8_t> sourceVector;
	MemoryInputStream memoryInputStream(sourceVector);
	char* buffer = new char[sourceVector.size() + 1];

	REQUIRE_THROWS(memoryInputStream.ReadBlock(buffer, sourceVector.size() + 1));
	REQUIRE(memoryInputStream.IsEOF());
}

TEST_CASE("Check block memory read past EOF for not empty memory stream with initial EOF false")
{
	std::vector<uint8_t> sourceVector{ 't', 'e', 's', 't' };
	MemoryInputStream memoryInputStream(sourceVector);

	REQUIRE_FALSE(memoryInputStream.IsEOF());

	char* buffer = new char[sourceVector.size() + 1];
	std::streamsize actualReadSize = memoryInputStream.ReadBlock(buffer, sourceVector.size() + 1);

	REQUIRE(actualReadSize == sourceVector.size());
	for (size_t i = 0; i < sourceVector.size(); ++i)
	{
		REQUIRE(sourceVector[i] == buffer[i]);
	}

	REQUIRE(memoryInputStream.IsEOF());
}

TEST_CASE("Check block memory read past EOF for not empty memory stream with initial EOF true")
{
	std::vector<uint8_t> sourceVector{ 't', 'e', 's', 't' };
	MemoryInputStream memoryInputStream(sourceVector);
	char* buffer = new char[sourceVector.size() + 1];

	memoryInputStream.ReadBlock(buffer, sourceVector.size());
	REQUIRE_THROWS(memoryInputStream.ReadBlock(buffer, 1));
}

TEST_CASE("Check byte memory read past EOF for an empty memory stream")
{
	std::vector<uint8_t> sourceVector;
	MemoryInputStream memoryInputStream(sourceVector);

	REQUIRE_THROWS(memoryInputStream.ReadByte());
	REQUIRE(memoryInputStream.IsEOF());
}

TEST_CASE("Check byte memory read past EOF for not empty memory stream with initial EOF true")
{
	std::vector<uint8_t> sourceVector{ 't', 'e', 's', 't' };
	MemoryInputStream memoryInputStream(sourceVector);
	char* buffer = new char[sourceVector.size() + 1];

	memoryInputStream.ReadBlock(buffer, sourceVector.size() );
	REQUIRE_THROWS(memoryInputStream.ReadByte());
}

// Tests for OutputStreams
TEST_CASE("Check file output stream constructor")
{
	std::unique_ptr<FileOutputStream> fileOutputStreamPtr;

	REQUIRE_NOTHROW(fileOutputStreamPtr.reset(new FileOutputStream(OUTPUT_FILENAME)));
}

TEST_CASE("Write a byte to the newly created output file stream")
{
	FileOutputStream fileOutputStream(OUTPUT_FILENAME);

	REQUIRE_NOTHROW(fileOutputStream.WriteByte('a'));
}

TEST_CASE("Write a block of data to the newly created output file stream")
{
	FileOutputStream fileOutputStream(OUTPUT_FILENAME);

	const char* buffer = "test";
	REQUIRE_NOTHROW(fileOutputStream.WriteBlock(buffer, 4));
}

TEST_CASE("Write a block of data to the newly created output file stream from null buffer pointer")
{
	FileOutputStream fileOutputStream(OUTPUT_FILENAME);

	const char* buffer = nullptr;
	REQUIRE_THROWS(fileOutputStream.WriteBlock(buffer, 4));
}

TEST_CASE("Check memory output stream constructor")
{
	std::unique_ptr<MemoryOutputStream> memoryOutputStreamPtr;

	REQUIRE_NOTHROW(memoryOutputStreamPtr.reset(new MemoryOutputStream()));
}

TEST_CASE("Write a byte to the newly created output memory stream")
{
	MemoryOutputStream memoryOutputStreamPtr;

	REQUIRE_NOTHROW(memoryOutputStreamPtr.WriteByte('a'));
}

TEST_CASE("Write a byte to the created output memory stream consistently")
{
	MemoryOutputStream memoryOutputStreamPtr;

	memoryOutputStreamPtr.WriteByte('a');
	REQUIRE_NOTHROW(memoryOutputStreamPtr.WriteByte('b'));
}

TEST_CASE("Write a block of data to the newly created output memory stream")
{
	MemoryOutputStream memoryOutputStreamPtr;
	const char* buffer = "anotherData";

	REQUIRE_NOTHROW(memoryOutputStreamPtr.WriteBlock(buffer, 2));
}

TEST_CASE("Write a block of data to the newly created output memory stream from null buffer pointer")
{
	MemoryOutputStream memoryOutputStreamPtr;
	const char* buffer = nullptr;

	REQUIRE_THROWS(memoryOutputStreamPtr.WriteBlock(buffer, 4));
}

TEST_CASE("Write a block of data to the newly created output memory stream with size = 0")
{
	MemoryOutputStream memoryOutputStreamPtr;
	const char* buffer = "anotherData";

	REQUIRE_NOTHROW(memoryOutputStreamPtr.WriteBlock(buffer, 0));
}

TEST_CASE("Write a block of data to the created output memory stream consistently")
{
	MemoryOutputStream memoryOutputStreamPtr;
	const char* buffer = "anotherData";

	REQUIRE_NOTHROW(memoryOutputStreamPtr.WriteBlock(buffer, 2));
	REQUIRE_NOTHROW(memoryOutputStreamPtr.WriteBlock(buffer, 5));
}

TEST_CASE("Encrypt text file")
{
	auto fileOutputStream = std::make_unique<FileOutputStream>("test.crypt.txt");
	auto encryptedOutputStream = std::make_unique<SubstitutionCipherEncryptOutputStream>(1, std::move(fileOutputStream));
	const char* buffer = "anotherData";

	REQUIRE_NOTHROW(encryptedOutputStream->WriteBlock(buffer, 7));
}

TEST_CASE("Decrypt produced file")
{
	auto fileInputStream = std::make_unique<FileInputStream>("test.crypt.txt");
	auto decryptedOutputStream = std::make_unique<SubstitutionCipherDecryptInputStream>(1, std::move(fileInputStream));

	char* buffer = new char[7];
	const char* expectedResult = "another";
	decryptedOutputStream->ReadBlock(buffer, 7);
	for (size_t i = 0; i < 7; ++i)
	{
		REQUIRE(expectedResult[i] == buffer[i]);
	}
}

TEST_CASE("Compress text file")
{
	auto fileOutputStream = std::make_unique<FileOutputStream>("test.compress.txt");
	auto compressedOutputStream = std::make_unique<RLECompressOutputStream>(std::move(fileOutputStream));
	const char* buffer = "aaaaanotherData";

	REQUIRE_NOTHROW(compressedOutputStream->WriteBlock(buffer, 7));
}

TEST_CASE("Decompress text file")
{
	auto fileInputStream = std::make_unique<FileInputStream>("test.compress.txt");
	auto decompressedInputStream = std::make_unique<RLEDecompressInputStream>(std::move(fileInputStream));

	char* buffer = new char[7];
	decompressedInputStream->ReadBlock(buffer, 3);
	const char* expectedResult = "aaaaano";
	for (size_t i = 0; i < 7; ++i)
	{
		REQUIRE(expectedResult[i] == buffer[i]);
	}
}
