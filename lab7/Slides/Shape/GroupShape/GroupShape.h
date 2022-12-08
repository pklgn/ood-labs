#pragma once
#include "IGroupShape.h"
#include "../../Style/LineStyle/CompositeLineStyle/CompositeLineStyle.h"
#include "../../Style/FillStyle/CompositeFillStyle/CompositeFillStyle.h"
#include "../../Style/LineStyle/Enumerator/ILineStyleEnumerator.h"
#include "../../Style/FillStyle/Enumerator/IFillStyleEnumerator.h"

class GroupShape : public IGroupShape, std::enable_shared_from_this<GroupShape>
{
public:
	[[nodiscard]] static std::shared_ptr<GroupShape> Create()
	{
		return std::shared_ptr<GroupShape>(new GroupShape());
	}

	[[nodiscard]] static std::shared_ptr<GroupShape> Create(std::vector<std::shared_ptr<IShape>>& shapes)
	{
		//Not using std::make_shared<GroupShape> because the c'tor is private.
		return std::shared_ptr<GroupShape>(new GroupShape(shapes));
	}

	RectD GetFrame() override;
	void SetFrame(const RectD&) override;

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	std::shared_ptr<const IFillStyle> GetFillStyle() const override;

	std::shared_ptr<const IShape> GetGroupShape() const override;

	size_t GetShapesCount() override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t) override;
	void InsertShape(std::shared_ptr<IShape>, size_t index) override;
	void RemoveShapeAtIndex(size_t) override;

	void Draw(ICanvas&) override;

private:
	GroupShape();
	GroupShape(std::vector<std::shared_ptr<IShape>>&);
	std::shared_ptr<const GroupShape> GetPtr() const;

	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<CompositeLineStyle> m_lineStyle;
	std::shared_ptr<CompositeFillStyle> m_fillStyle;
};
