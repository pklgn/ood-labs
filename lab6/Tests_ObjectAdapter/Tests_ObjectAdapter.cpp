#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include <sstream>
#include "../ObjectAdapter/graphics_lib/graphics_lib.hpp"
#include "../ObjectAdapter/modern_graphics_lib/modern_graphics_lib.hpp"
#include "../ObjectAdapter/adapter/ModernGraphicsRendererAdapter.hpp"

TEST_CASE("Test Adapter")
{
	std::ostringstream oss;
	modern_graphics_lib::ModernGraphicsRenderer renderer(oss);
	ModernGraphicsRendererAdapter adapter(renderer);
	SECTION("Check BeginDraw was enabled in adapter")
	{
		REQUIRE_THROWS_AS(renderer.BeginDraw(), std::logic_error);
	}

	SECTION("Check BeginDraw default position")
	{
		adapter.LineTo(0, 0);
		REQUIRE(oss.str() == "<draw>\n"
							 "  <line fromX=\"0\" fromY=\"0\" toX=\"0\" toY=\"0\"/>\n");
	}

	SECTION("Check MoveTo change start position value")
	{
		adapter.MoveTo(100, 200);
		adapter.LineTo(400, 500);
		REQUIRE(oss.str() == "<draw>\n"
							 "  <line fromX=\"100\" fromY=\"200\" toX=\"400\" toY=\"500\"/>\n");
	}

	SECTION("Use edge values for adapter MoveTo method")
	{
		REQUIRE_NOTHROW(adapter.MoveTo(INT_MIN, INT_MIN));
		REQUIRE_NOTHROW(adapter.MoveTo(INT_MIN, INT_MAX));
		REQUIRE_NOTHROW(adapter.MoveTo(INT_MAX, INT_MIN));
		REQUIRE_NOTHROW(adapter.MoveTo(INT_MAX, INT_MAX));
	}

	SECTION("Use edge values for adapter LineTo method")
	{
		REQUIRE_NOTHROW(adapter.LineTo(INT_MIN, INT_MIN));
		REQUIRE_NOTHROW(adapter.LineTo(INT_MIN, INT_MAX));
		REQUIRE_NOTHROW(adapter.LineTo(INT_MAX, INT_MIN));
		REQUIRE_NOTHROW(adapter.LineTo(INT_MAX, INT_MAX));
	}

	SECTION("Check renderer EndDraw was raised when adapter die")
	{
		adapter.~ModernGraphicsRendererAdapter();
		REQUIRE_THROWS(renderer.EndDraw());
		REQUIRE_NOTHROW(renderer.BeginDraw());
	}

	SECTION("Check output will have close tag when adapter die")
	{
		adapter.~ModernGraphicsRendererAdapter();
		REQUIRE(oss.str() == "<draw>\n"
							 "</draw>\n");
	}
}