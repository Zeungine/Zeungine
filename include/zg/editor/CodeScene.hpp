#pragma once
#include <zg/Scene.hpp>
#include <zg/Window.hpp>
using namespace std;
namespace zg::editor
{
	using namespace zg;
	struct CodeScene : Scene
	{
		explicit CodeScene(Window &window);
	};
}