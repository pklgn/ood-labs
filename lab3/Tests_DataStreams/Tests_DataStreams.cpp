#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../DataStreams/pch.h"

const std::string SINGLE_LINE_FILENAME = "single_line.test.txt";
const std::string MULTIPLE_LINES_FILENAME = "multiple_lines.test.txt";
constexpr size_t SINGLE_LINE_FILE_CONTENT_SIZE = 6;
constexpr size_t MULTIPLE_LINES_FILE_CONTENT_SIZE = 20;

TEST_CASE("Check file input stream constructor")
{
	std::unique_ptr<FileInputStream> fileInputStreamPtr;
	REQUIRE_THROWS(fileInputStreamPtr.reset(new FileInputStream("fileDoesntExist.txt")));

	REQUIRE_NOTHROW(fileInputStreamPtr.reset(new FileInputStream(SINGLE_LINE_FILENAME)));
}

TEST_CASE("Check IsEOF() for existing single line file")
{
	FileInputStream fileInputStream(SINGLE_LINE_FILENAME);
	REQUIRE_FALSE(fileInputStream.IsEOF());

	char* buffer = new char[SINGLE_LINE_FILE_CONTENT_SIZE];
	fileInputStream.ReadBlock(buffer, SINGLE_LINE_FILE_CONTENT_SIZE);
	REQUIRE_FALSE(fileInputStream.IsEOF());

	REQUIRE_THROWS(fileInputStream.ReadByte());
	REQUIRE(fileInputStream.IsEOF());
}

TEST_CASE("Check IsEOF() for existing multiline file")
{
	FileInputStream fileInputStream(MULTIPLE_LINES_FILENAME);
	REQUIRE_FALSE(fileInputStream.IsEOF());

	char* buffer = new char[MULTIPLE_LINES_FILE_CONTENT_SIZE];
	//read past the eof
	fileInputStream.ReadBlock(buffer, MULTIPLE_LINES_FILE_CONTENT_SIZE + 1);

	REQUIRE(fileInputStream.IsEOF());
}

TEST_CASE("Read byte from file consistently")
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

TEST_CASE("Try reading byte when eof happens")
{
	FileInputStream fileInputStream(SINGLE_LINE_FILENAME);

	for (size_t i = 0; i < SINGLE_LINE_FILE_CONTENT_SIZE; ++i)
	{
		fileInputStream.ReadByte();
	}

	//attempt to read eof
	REQUIRE_THROWS(fileInputStream.ReadByte());
}

TEST_CASE("Read block of data from file consistently")
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

TEST_CASE("Try reading block of data past eof")
{
	FileInputStream fileInputStream(MULTIPLE_LINES_FILENAME);
	char* buffer = new char[MULTIPLE_LINES_FILE_CONTENT_SIZE];

	std::streamsize actualReadSize = fileInputStream.ReadBlock(buffer, MULTIPLE_LINES_FILE_CONTENT_SIZE);
	REQUIRE(actualReadSize == MULTIPLE_LINES_FILE_CONTENT_SIZE);
	
	std::streamsize readSizePastEOF = fileInputStream.ReadBlock(buffer, 2);
	REQUIRE(readSizePastEOF == 0);
}
