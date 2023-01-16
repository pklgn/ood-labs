#include "../../pch.h"
#include "PictureDraftAppModel.h"

PictureDraftAppModel::PictureDraftAppModel(std::shared_ptr<PictureDraft> pictureDraft, const std::shared_ptr<IHistory> history)
	: m_pictureDraft(pictureDraft)
	, m_history(history)
{
	m_pictureDraft->DoOnShapeAdded([&, this](size_t index) {
		auto shapeAppModel = std::make_shared<ShapeAppModel>(m_pictureDraft->GetShape(index));
		m_shapesAppModel.insert(m_shapesAppModel.begin() + index, shapeAppModel);
		m_shapeAdded(index);

		std::cout << "Shape " << ShapeTypeToString(shapeAppModel->GetType()) << " was added\n";
	});

	m_pictureDraft->DoOnShapeDeleted([&, this](size_t index, std::shared_ptr<Shape> shape) {
		auto shapeAppModel = m_shapesAppModel.at(index);
		m_shapesAppModel.erase(m_shapesAppModel.begin() + index);
		m_shapeDeleted(index, shapeAppModel);

		std::cout << "Shape " << ShapeTypeToString(shapeAppModel->GetType()) << " was deleted\n";
	});

	auto shapeSize = m_pictureDraft->GetShapeCount();
	for (size_t i = 0; i < shapeSize; ++i)
	{
		auto shape = m_pictureDraft->GetShape(i);
		auto shapeAppModel = std::make_shared<ShapeAppModel>(shape);
		m_shapesAppModel.push_back(shapeAppModel);
	}
}

std::shared_ptr<PictureDraft> PictureDraftAppModel::GetPictureDraft() const
{
	return m_pictureDraft;
}

size_t PictureDraftAppModel::GetShapeCount() const
{
	return m_shapesAppModel.size();
}

std::shared_ptr<ShapeAppModel> PictureDraftAppModel::GetShape(size_t index) const
{
	return m_shapesAppModel.at(index);
}

std::unique_ptr<InsertShapeUseCase> PictureDraftAppModel::CreateInsertShapeUseCase()
{
	// FIXED: реализовать сначала InsertShapeUseCase
	return std::make_unique<InsertShapeUseCase>(*this, m_history);
}

connection PictureDraftAppModel::DoOnShapeAdded(const std::function<void(size_t index)>& handler)
{
	return m_shapeAdded.connect(handler);
}

connection PictureDraftAppModel::DoOnShapeDeleted(const std::function<void(size_t index, std::shared_ptr<ShapeAppModel> shape)>& handler)
{
	return m_shapeDeleted.connect(handler);
}
