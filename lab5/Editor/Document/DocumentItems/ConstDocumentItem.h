#pragma once
#include <memory>
#include <variant>

#include "../Image/IImage.h"
#include "../Paragraph/IParagraph.h"

/*
������������ ������� ���������
*/
class ConstDocumentItem
{
public:
	ConstDocumentItem(std::shared_ptr<IBaseDocumentItem>);
	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const;

	virtual ~ConstDocumentItem() = default;

protected:
	std::shared_ptr<IBaseDocumentItem> m_item;
};
