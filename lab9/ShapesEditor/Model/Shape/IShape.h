#pragma once
#include "../../common/ShapeType/ShapeType.h"
#include "../../common/Frame/Frame.h"
#include "../Style/LineStyle/ILineStyle.h"
#include "../Style/FillStyle/IFillStyle.h"

class IShape
{
public:
	using Id = std::string;
	virtual Id GetId() const = 0;

	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD&) = 0;

	virtual std::shared_ptr<ILineStyle> GetLineStyle() = 0;
	virtual std::shared_ptr<const ILineStyle> GetLineStyle() const = 0;

	virtual std::shared_ptr<IFillStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IFillStyle> GetFillStyle() const = 0;
};