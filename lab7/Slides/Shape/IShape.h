#pragma once
#include "IDrawable.h"
#include "../Frame/Frame.h"
#include "../Style/LineStyle/ILineStyle.h"
#include "../Style/FillStyle/IFillStyle.h"

class IShape : public IDrawable
{
public:
	virtual ~IShape() = default;

	virtual RectD GetFrame() = 0;
	virtual void SetFrame(const RectD&) = 0;

	virtual std::shared_ptr<ILineStyle> GetLineStyle() = 0;
	virtual std::shared_ptr<const ILineStyle> GetLineStyle() const = 0;
	virtual void SetLineStyle(std::shared_ptr<ILineStyle>) = 0;

	virtual std::shared_ptr<IFillStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IFillStyle> GetFillStyle() const = 0;
	virtual void SetFillStyle(std::shared_ptr<IFillStyle>) = 0;

	virtual std::shared_ptr<const IShape> GetGroupShape() const = 0;
};