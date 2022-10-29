#pragma once
#include <memory>
#include <optional>
#include <string>

#include "Paragraph/IParagraph.h"
#include "Image/IImage.h"
#include "DocumentItems/ConstDocumentItem.h"
#include "DocumentItems/DocumentItem.h"

using Path = std::string;

/*
�������� ���������
*/
class IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) = 0;

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images
	// ��� ������������� ��������������� ������
	virtual std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		std::optional<size_t> position = std::nullopt)
		= 0;

	// ���������� ���������� ��������� � ���������
	virtual size_t GetItemsCount() const = 0;

	// ������ � ��������� �����������
	virtual ConstDocumentItem GetItem(size_t index) const = 0;
	virtual DocumentItem GetItem(size_t index) = 0;

	// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual std::string GetTitle() const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const std::string& title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo() const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo() const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	virtual void Save(const Path& path) const = 0;

	virtual ~IDocument() = default;
};
