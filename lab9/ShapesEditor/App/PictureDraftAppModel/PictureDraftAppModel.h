﻿#pragma once
#include "../../Model/PictureDraft/PictureDraft.h"
#include "../../Model/Shape/Shape.h"
#include "../History/IHistory.h"
#include "../ShapeAppModel/ShapeAppModel.h"

class PictureDraftAppModel
{
public:
	PictureDraftAppModel(const std::shared_ptr<PictureDraft>&, const std::shared_ptr<IHistory>);

	std::shared_ptr<PictureDraft> GetPictureDraft() const;
	size_t GetShapeCount() const;
	std::shared_ptr<ShapeAppModel> GetShape(size_t index) const;

	connection DoOnShapeAdded(const std::function<void(size_t index)>&);
	connection DoOnShapeDeleted(const std::function<void(size_t index, std::shared_ptr<ShapeAppModel> shape)>&);

	void Undo();
	void Redo();

private:
	std::shared_ptr<PictureDraft> m_pictureDraft;
	std::vector<std::shared_ptr<ShapeAppModel>> m_shapesAppModel;
	signal<void(size_t index)> m_shapeAdded;
	signal<void(size_t index, std::shared_ptr<ShapeAppModel>)> m_shapeDeleted;
	std::shared_ptr<IHistory> m_history;
};
