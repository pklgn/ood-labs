#pragma once

class IInputStream
{
public:
	// ���������� ������� ���������� ����� ������ ������
	// ����������� ���������� std::ios_base::failuer � ������ ������
	virtual bool IsEOF() const = 0;

	// ��������� ���� �� ������.
	// ����������� ���������� std::ios_base::failure � ������ ������
	virtual uint8_t ReadByte() = 0;

	// ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
	// �� ������ dstBuffer
	// ���������� ���������� ������� ����������� ����. ����������� ���������� � ������ ������
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

	virtual ~IInputStream() = default;
};

typedef std::unique_ptr<IInputStream> IInputStreamPtr;
