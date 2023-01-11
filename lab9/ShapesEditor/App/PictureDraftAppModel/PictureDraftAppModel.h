#pragma once
#include "../../Model/PictureDraft/PictureDraft.h"
#include "../../Model/Shape/Shape.h"
#include "../ShapeAppModel/ShapeAppModel.h"

//using namespace boost::signals2;

class PictureDraftAppModel
{
public:
	PictureDraftAppModel(std::shared_ptr<PictureDraft>);

	std::shared_ptr<PictureDraft> GetPictureDraft() const;
	size_t GetShapeCount() const;
	std::shared_ptr<ShapeAppModel> GetShape(size_t index) const;
	// TODO: заменить возвращаемый тип на InsertShapeUseCase
	void CreateInsertShapeUseCase();

	connection DoOnShapeAdded(const std::function<void(size_t index)>&);
	connection DoOnShapeDeleted(const std::function<void(size_t index, std::shared_ptr<ShapeAppModel> shape)>&);

private:
	std::shared_ptr<PictureDraft> m_pictureDraft;
	std::vector<std::shared_ptr<ShapeAppModel>> m_shapesAppModel;
	signal<void(size_t index)> m_shapeAdded;
	signal<void(size_t index, std::shared_ptr<ShapeAppModel>)> m_shapeDeleted;
};