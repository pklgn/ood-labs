#pragma once
#include <vector>
#include "../Shapes/Factory/IShapeFactory.h"

typedef std::vector<ShapePtr> Storage;

class PictureDraft
{
public:
	size_t GetShapeCount() const;
	// return raw pointer
	Storage::const_iterator GetShape(size_t index) const;
	void AddShape(ShapePtr&&);

	Storage::const_iterator begin() const;
	Storage::const_iterator end() const;

private:
	Storage m_storage;
};
