#pragma once
#include <deque>
#include <vector>

#include "../History/History.h"
#include "DocumentItems/DocumentItem.h"
#include "IDocument.h"

class HTMLDocument : public IDocument
{
public:
	inline static const Path noPath = "";

	HTMLDocument();
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt)
		override;

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images
	// ��� ������������� ��������������� ������
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		std::optional<size_t> position = std::nullopt)
		override;

	// ���������� ���������� ��������� � ���������
	size_t GetItemsCount() const override;

	// ������ � ��������� �����������
	ConstDocumentItem GetItem(size_t index) const override;
	DocumentItem GetItem(size_t index) override;

	// ������� ������� �� ���������
	void DeleteItem(size_t index) override;

	// ���������� ��������� ���������
	std::string GetTitle() const override;
	// �������� ��������� ���������
	void SetTitle(const std::string& title) override;

	// �������� � ����������� �������� Undo
	bool CanUndo() const override;
	// �������� ������� ��������������
	void Undo() override;

	// �������� � ����������� �������� Redo
	bool CanRedo() const override;
	// ��������� ���������� ������� ��������������
	void Redo() override;

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	void Save() const override;

	Path GetSavePath() const override;
	void SetSavePath(const Path&) override;

	std::vector<DocumentItem> GetDocumentItems() const;

private:
	size_t ValidatePosition(const std::optional<size_t>& position);

	std::string m_title;
	History m_history;
	std::vector<DocumentItem> m_items;
	Path m_savePath;
};