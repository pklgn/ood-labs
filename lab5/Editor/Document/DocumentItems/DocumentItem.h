#pragma once
#include "ConstDocumentItem.h"

/*
������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class DocumentItem : public ConstDocumentItem
{
public:
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph();
};
