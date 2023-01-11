﻿#include "../../pch.h"
#include "PictureDraftAppModel.h"

PictureDraftAppModel::PictureDraftAppModel(std::shared_ptr<PictureDraft> pictureDraft)
	: m_pictureDraft(pictureDraft)
{
	m_pictureDraft->DoOnShapeAdded([&, this](size_t index) {
		auto shapeAppModel = std::make_shared<ShapeAppModel>(pictureDraft->GetShape(index));
		m_shapesAppModel.push_back(shapeAppModel);
		m_shapeAdded(index);
	});

	// TODO: а нужен ли здесь в качестве второго параметра shape?
	m_pictureDraft->DoOnShapeDeleted([&, this](size_t index, std::shared_ptr<Shape> shape) {
		auto shapeAppModel = m_shapesAppModel.at(index);
		m_shapesAppModel.erase(m_shapesAppModel.begin() + index);
		m_shapeDeleted(index, shapeAppModel);
	});
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

void PictureDraftAppModel::CreateInsertShapeUseCase()
{
	// TODO: реализовать сначала InsertShapeUseCase
}

connection PictureDraftAppModel::DoOnShapeAdded(const std::function<void(size_t index)>& handler)
{
	return m_shapeAdded.connect(handler);
}

connection PictureDraftAppModel::DoOnShapeDeleted(const std::function<void(size_t index, std::shared_ptr<ShapeAppModel> shape)>& handler)
{
	return m_shapeDeleted.connect(handler);
}
