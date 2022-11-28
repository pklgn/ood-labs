#pragma once
#include "IGroupShape.h"
#include "../../Style/LineStyle/CompositeLineStyle/CompositeLineStyle.h"
#include "../../Style/FillStyle/CompositeFillStyle/CompositeFillStyle.h"
#include "../../Style/LineStyle/Enumerator/ILineStyleEnumerator.h"
#include "../../Style/FillStyle/Enumerator/IFillStyleEnumerator.h"

class GroupShape : public IGroupShape, std::enable_shared_from_this<GroupShape>
{
public:
	std::shared_ptr<GroupShape> GetPtr();
	std::shared_ptr<const GroupShape> GetPtr() const;

	[[nodiscard]] static std::shared_ptr<GroupShape> Create(std::vector<std::shared_ptr<IShape>> shapes)
	{
		//CARE Not using std::make_shared<Best> because the c'tor is private.
		return std::make_shared<GroupShape>(shapes);
	}

	RectD GetFrame() override;
	void SetFrame(const RectD&) override;

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;
	void SetLineStyle(std::shared_ptr<ILineStyle>) override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	std::shared_ptr<const IFillStyle> GetFillStyle() const override;
	void SetFillStyle(std::shared_ptr<IFillStyle>) override;

	std::shared_ptr<const IShape> GetGroupShape() const override;

private:
	GroupShape(std::vector<std::shared_ptr<IShape>>);

	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<CompositeLineStyle> m_lineStyle;
	std::shared_ptr<CompositeFillStyle> m_fillStyle;
	RectD m_frame;
};
