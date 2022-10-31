#pragma once
#include <string>

#include "../DocumentItems/IBaseDocumentItem.h"

using Path = std::string;

/*
�����������
*/
class IImage : public IBaseDocumentItem
{
public:
	// ���������� ���� ������������ �������� ���������
	virtual Path GetPath() const = 0;

	// ������ ����������� � ��������
	virtual size_t GetWidth() const = 0;
	// ������ ����������� � ��������
	virtual size_t GetHeight() const = 0;

	// �������� ������ �����������
	virtual void Resize(int width, int height) = 0;

	//virtual ~IImage() = default;
};
