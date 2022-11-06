#pragma once
#include "../IDocument.h"

class HTMLSaver
{
public:
	HTMLSaver(IDocument& document);

	void Save(const Path&) const;

private:
	void SaveHtmlDocumentItem(std::ostream&, ConstDocumentItem& item, const Path&) const;

	void SaveHtmlDocumentImageItem(std::ostream&, std::shared_ptr<const IImage> imagePtr, const Path&) const;

	void SaveHtmlDocumentParagraphItem(std::ostream&, std::shared_ptr<const IParagraph> paragraphPtr) const;

	IDocument& m_document;
};