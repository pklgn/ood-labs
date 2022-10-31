#pragma once
#include "ConstDocumentItem.h"

/*
������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class DocumentItem : public ConstDocumentItem
{
public:
	DocumentItem(std::shared_ptr<IBaseDocumentItem>);
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph();
};
