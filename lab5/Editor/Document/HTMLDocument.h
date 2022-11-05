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
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt)
		override;

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images
	// под автоматически сгенерированным именем
	std::shared_ptr<IImage> InsertImage(const Path& path, size_t width, size_t height,
		std::optional<size_t> position = std::nullopt)
		override;

	// Возвращает количество элементов в документе
	size_t GetItemsCount() const override;

	// Доступ к элементам изображения
	ConstDocumentItem GetItem(size_t index) const override;
	DocumentItem GetItem(size_t index) override;

	// Удаляет элемент из документа
	void DeleteItem(size_t index) override;

	// Возвращает заголовок документа
	std::string GetTitle() const override;
	// Изменяет заголовок документа
	void SetTitle(const std::string& title) override;

	// Сообщает о доступности операции Undo
	bool CanUndo() const override;
	// Отменяет команду редактирования
	void Undo() override;

	// Сообщает о доступности операции Redo
	bool CanRedo() const override;
	// Выполняет отмененную команду редактирования
	void Redo() override;

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
	// Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	void Save(const Path&) const override;

	void ReplaceText(size_t index, const std::string&);

	void ResizeImage(size_t index, size_t width, size_t height);

protected:
	Path CopyImage(const Path& srcPath);

	void SetSavePath(const Path& path);

private:
	size_t ValidatePosition(const std::optional<size_t>& position);

	std::string m_title;
	History m_history;
	std::vector<DocumentItem> m_items;
	Path m_savePath;
};