#pragma once
#include <memory>

#include "../Image/IImage.h"
#include "../Paragraph/IParagraph.h"

/*
������������ ������� ���������
*/
class ConstDocumentItem
{
public:
	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const;

	virtual ~ConstDocumentItem() = default;
};
