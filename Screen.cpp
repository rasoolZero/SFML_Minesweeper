#include "Screen.h"
#include "ManagerManager.h"
Screen::Screen(RenderWindow& window_ref, ManagerManager& manager_ref, std::string fontname, short int normalFontSize, Color normalTextColor, Color selectedTextColor)
	:window_ref(window_ref)
	,manager_ref(manager_ref)
	,normalFontSize(normalFontSize)
	,normalTextColor(normalTextColor)
	,selectedTextColor(selectedTextColor)
{
	if (!font.loadFromFile(fontname)) {
		throw std::runtime_error("font could not be loaded\n");
	}
}
