#include "mvApp.h"
#include "mvCore.h"
#include "mvLogger.h"
#include "AppItems/mvInputText.h"
#include "AppItems/mvTab.h"
#include "AppItems/mvMenu.h"
#include "AppItems/mvSpacing.h"
#include "AppItems/mvSameLine.h"
#include "AppItems/mvRadioButton.h"
#include "AppItems/mvButton.h"
#include "AppItems/mvChild.h"
#include "AppItems/mvGroup.h"
#include "AppItems/mvTooltip.h"
#include "AppItems/mvCollapsingHeader.h"
#include "AppItems/mvSeperator.h"
#include "AppItems/mvColorEdit4.h"
#include "AppItems/mvInputInt.h"
#include "AppItems/mvInputFloat.h"
#include "AppItems/mvCheckbox.h"
#include "AppItems/mvListbox.h"
#include "AppItems/mvText.h"
#include "AppItems/mvCombo.h"
#include "AppItems/mvPlot.h"
#include "AppItems/mvSimplePlot.h"
#include "AppItems/mvIndent.h"
#include "AppItems/mvDrawing.h"
#include "AppItems/mvWindowAppItem.h"

namespace Marvel {

	mvApp* mvApp::s_instance = nullptr;

	static void SetStyle(ImGuiStyle& style, mvStyle& mvstyle)
	{
		style.Alpha = mvstyle["Alpha"].x;
		style.WindowPadding = { mvstyle["WindowPadding"].x, mvstyle["WindowPadding"].y };
		style.WindowRounding = mvstyle["WindowRounding"].x;
		style.WindowBorderSize = mvstyle["WindowBorderSize"].x;
		style.WindowTitleAlign = { mvstyle["WindowTitleAlign"].x, mvstyle["WindowTitleAlign"].y };
		style.ChildRounding = mvstyle["ChildRounding"].x;
		style.ChildBorderSize = mvstyle["ChildBorderSize"].x;
		style.PopupRounding = mvstyle["PopupRounding"].x;
		style.PopupBorderSize = mvstyle["PopupBorderSize"].x;
		style.FramePadding = { mvstyle["FramePadding"].x, mvstyle["FramePadding"].y };
		style.FrameRounding = mvstyle["FrameRounding"].x;
		style.FrameBorderSize = mvstyle["FrameBorderSize"].x;
		style.ItemSpacing = { mvstyle["ItemSpacing"].x, mvstyle["ItemSpacing"].y };
		style.ItemInnerSpacing = { mvstyle["ItemInnerSpacing"].x, mvstyle["ItemInnerSpacing"].y };
		style.TouchExtraPadding = { mvstyle["TouchExtraPadding"].x, mvstyle["TouchExtraPadding"].y };
		style.IndentSpacing = mvstyle["IndentSpacing"].x;
		style.ScrollbarSize = mvstyle["ScrollbarSize"].x;
		style.ScrollbarRounding = mvstyle["ScrollbarRounding"].x;
		style.GrabMinSize = mvstyle["GrabMinSize"].x;
		style.GrabRounding = mvstyle["GrabRounding"].x;
		style.TabRounding = mvstyle["TabRounding"].x;
		style.TabBorderSize = mvstyle["TabBorderSize"].x;
		style.ButtonTextAlign = { mvstyle["ButtonTextAlign"].x, mvstyle["ButtonTextAlign"].y };
		style.SelectableTextAlign = { mvstyle["SelectableTextAlign"].x, mvstyle["SelectableTextAlign"].y };
		style.DisplayWindowPadding = { mvstyle["DisplayWindowPadding"].x, mvstyle["DisplayWindowPadding"].y };
		style.DisplaySafeAreaPadding = { mvstyle["DisplaySafeAreaPadding"].x, mvstyle["DisplaySafeAreaPadding"].y };
		style.AntiAliasedLines = mvstyle["AntiAliasedLines"].x > 0.5f;
		style.AntiAliasedFill = mvstyle["AntiAliasedFill"].x > 0.5f;
		style.CurveTessellationTol = mvstyle["CurveTessellationTol"].x;
		style.CircleSegmentMaxError = mvstyle["CircleSegmentMaxError"].x;
	}

	mvApp* mvApp::GetApp()
	{
		if (s_instance)
			return s_instance;

		s_instance = new mvApp();
		return s_instance;
	}

	void mvApp::prepareStandardCallbacks()
	{
		ImGuiIO& io = ImGui::GetIO();

		for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
		{

			if (ImGui::IsMouseClicked(i))
				triggerCallback(m_mouseClickCallback, std::to_string(i));

			if (io.MouseDownDuration[i] >= 0.0f)
				triggerCallback(m_mouseDownCallback, std::to_string(i), std::to_string(io.MouseDownDuration[i]));

			if (ImGui::IsMouseDoubleClicked(i))
				triggerCallback(m_mouseDoubleClickCallback, std::to_string(i));

			if (ImGui::IsMouseReleased(i))
				triggerCallback(m_mouseReleaseCallback, std::to_string(i));
		}

		for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++)
		{
			if (ImGui::IsKeyPressed(i))
				triggerCallback(m_keyPressCallback, std::to_string(i));

			if (io.KeysDownDuration[i] >= 0.0f)
				triggerCallback(m_keyDownCallback, std::to_string(i), std::to_string(io.KeysDownDuration[i]));

			if (ImGui::IsKeyReleased(i))
				triggerCallback(m_keyReleaseCallback, std::to_string(i));
		}
	}

	void mvApp::render()
	{
		// set imgui style to mvstyle
		updateStyle();

		// update mouse
		ImVec2 mousePos = ImGui::GetMousePos();
		m_mousePos.x = mousePos.x;
		m_mousePos.y = mousePos.y;

		prepareStandardCallbacks();
			
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(m_width, m_height));
		ImGui::Begin("Blah", (bool*)0, m_windowflags);

		m_parents.push(nullptr);

		// main callback
		triggerCallback(m_callback, "Main Application");

		for (mvAppItem* item : m_items)
		{
			// skip item if it's not shown
			if (!item->isShown())
				continue;

			// check if item is owned & it's parent is visible
			if (!doesParentAllowRender(item))
				continue;

			// if parent isn't the most recent parent, skip
			if (item->getParent() && m_parents.top() && item->getType() != mvAppItemType::Tooltip)
				if (!(m_parents.top()->getName() == item->getParent()->getName()))
					continue;

			// set item width
			if(item->getWidth() != 0)
				ImGui::SetNextItemWidth((float)item->getWidth());

			item->draw();

			// Regular Tooltip (simple)
			if (item->getTip() != "" && ImGui::IsItemHovered())
				ImGui::SetTooltip(item->getTip().c_str());

			item->setHovered(ImGui::IsItemHovered());
			item->setActive(ImGui::IsItemActive());
			item->setFocused(ImGui::IsItemFocused());
			item->setClicked(ImGui::IsItemClicked());
			item->setVisible(ImGui::IsItemVisible());
			item->setEdited(ImGui::IsItemEdited());
			item->setActivated(ImGui::IsItemActivated());
			item->setDeactivated(ImGui::IsItemDeactivated());
			item->setDeactivatedAfterEdit(ImGui::IsItemDeactivatedAfterEdit());
			item->setToggledOpen(ImGui::IsItemToggledOpen());
			item->setRectMin({ ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y});
			item->setRectMax({ ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y });
			item->setRectSize({ ImGui::GetItemRectSize().x, ImGui::GetItemRectSize().y });
		}

		ImGui::End();
	}

	bool mvApp::isMouseButtonPressed(int button) const
	{
		ImGuiIO& io = ImGui::GetIO();
		return io.MouseDown[button];
	}

	bool mvApp::isKeyPressed(int keycode) const
	{
		ImGuiIO& io = ImGui::GetIO();
		return io.KeysDown[keycode];
	}

	bool mvApp::doesParentAllowRender(mvAppItem* item)
	{
		if (item->getParent())
		{
			switch (item->getParent()->getType())
			{
			case mvAppItemType::TabItem:
				return static_cast<mvTab*>(item->getParent())->getValue();
				break;

			case mvAppItemType::Menu:
				return static_cast<mvMenu*>(item->getParent())->getValue();
				break;

			case mvAppItemType::Child:
				return static_cast<mvChild*>(item->getParent())->getValue();
				break;

			case mvAppItemType::Tooltip:
				return static_cast<mvTooltip*>(item->getParent())->getValue();
				break;

			case mvAppItemType::CollapsingHeader:
			{
				if (!static_cast<mvCollapsingHeader*>(item->getParent())->getValue())
				{
					item->hide();
					return false;
				}
				else
					item->show();
				break;
			}

			default:
				return item->getParent()->isShown();
			}
		}

		// doesn't have a parent
		return true;
	}

	void mvApp::pushParent(mvAppItem* item)
	{
		m_parents.push(item);
	}

	mvAppItem* mvApp::popParent()
	{
		mvAppItem* item = m_parents.top();
		m_parents.pop();
		return item;
	}

	mvAppItem* mvApp::topParent()
	{
		if(m_parents.size() != 0)
			return m_parents.top();
		return nullptr;
	}

	void mvApp::setItemCallback(const std::string& name, const std::string& callback)
	{
		auto item = getItem(name);
		if (item)
			item->setCallback(callback);
	}

	void mvApp::setItemTip(const std::string& name, const std::string& tip)
	{
		auto item = getItem(name);
		if (item)
			item->setTip(tip);
	}

	void mvApp::setItemWidth(const std::string& name, int width)
	{
		auto item = getItem(name);
		if (item)
			item->setWidth(width);
	}

	mvAppItem* mvApp::getItem(const std::string& name)
	{
		for (mvAppItem* item : m_items)
		{
			if (item->getName() == name)
				return item;
		}

		return nullptr;
	}

	bool mvApp::isItemHovered(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemHovered();
		return false;
	}

	bool mvApp::isItemActive(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemActive();
		return false;
	}

	bool mvApp::isItemFocused(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemFocused();
		return false;
	}

	bool mvApp::isItemClicked(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemClicked();
		return false;
	}
	
	bool mvApp::isItemVisible(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemVisible();
		return false;
	}
	
	bool mvApp::isItemEdited(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemEdited();
		return false;
	}
	
	bool mvApp::isItemActivated(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemActivated();
		return false;
	}
	
	bool mvApp::isItemDeactivated(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemDeactivated();
		return false;
	}
	
	bool mvApp::isItemDeactivatedAfterEdit(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemDeactivatedAfterEdit();
		return false;
	}
	
	bool mvApp::isItemToogledOpen(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->isItemToogledOpen();
		return false;
	}
	
	mvVec2 mvApp::getItemRectMin(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->getItemRectMin();
		return {0.0f, 0.0f};
	}
	
	mvVec2 mvApp::getItemRectMax(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->getItemRectMax();
		return { 0.0f, 0.0f };
	}
	
	mvVec2 mvApp::getItemRectSize(const std::string& item)
	{
		if (mvAppItem* pitem = getItem(item))
			return pitem->getItemRectSize();
		return { 0.0f, 0.0f };
	}

	void mvApp::triggerCallback(const std::string& name, const std::string& sender)
	{
		if (name == "")
			return;

		PyErr_Clear();

		PyObject* pHandler = PyDict_GetItemString(m_pDict, name.c_str()); // borrowed reference

		PyObject* pArgs = PyTuple_New(1);
		PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(sender.c_str()));

		PyObject* result = PyObject_CallObject(pHandler, pArgs);

		// check if error occurred
		PyErr_Print();


		Py_XDECREF(pArgs);
		Py_XDECREF(result);

	}

	void mvApp::triggerCallback(const std::string& name, const std::string& sender, const std::string& data)
	{
		if (name == "")
			return;

		PyErr_Clear();

		PyObject* pHandler = PyDict_GetItemString(m_pDict, name.c_str()); // borrowed reference

		PyObject* pArgs = PyTuple_New(2);
		PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(sender.c_str()));
		PyTuple_SetItem(pArgs, 1, PyUnicode_FromString(data.c_str()));

		PyObject* result = PyObject_CallObject(pHandler, pArgs);

		// check if error occurred
		PyErr_Print();


		Py_XDECREF(pArgs);
		Py_XDECREF(result);

	}

	void mvApp::setAppTheme(const std::string& theme)
	{
		if (theme == "dark")
			ImGui::StyleColorsDark();
		else if (theme == "classic")
			ImGui::StyleColorsClassic();
		else if (theme == "light")
			ImGui::StyleColorsLight();
		else
			ImGui::StyleColorsDark();
	}

	void mvApp::updateTheme()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		auto themecolors = m_theme.getColors();

		for (unsigned i = 0; i < m_theme.getNumberOfItems(); i++)
		{
			auto color = themecolors[i];
			colors[i] = ImVec4(color[0], color[1], color[2], color[3]);
		}
			
	}

	void mvApp::changeThemeItem(const char* name, mvColor color)
	{
		m_theme.changeThemeItem(name, color.r, color.g, color.b, color.a);
	}

	//-----------------------------------------------------------------------------
	// Styles
	//-----------------------------------------------------------------------------
	void mvApp::updateStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		SetStyle(style, m_style);
	}

	bool mvApp::setStyleItem(const std::string& item, float x, float y)
	{

		if (m_style.count(item) > 0)
		{
			m_style.at(item).x = x;
			m_style.at(item).y = y;
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------------
	// Basic AppItems
	//-----------------------------------------------------------------------------

	mvAppItem* mvApp::addInputText(const std::string& name, const std::string& hint, bool multiline)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvInputText(parent, name, hint, multiline);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addInputInt(const std::string& name, int default_value)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvInputInt(parent, name, default_value);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addInputFloat(const std::string& name, float default_value)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvInputFloat(parent, name, default_value);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addButton(const std::string& name)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvButton(parent, name);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addColorEdit4(const std::string& name, mvColor color)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvColorEdit4(parent, name, color.r, color.g, color.b, color.a);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addRadioButtons(const std::string& name, const std::vector<std::string>& itemnames, int default_value)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvRadioButton(parent, name, itemnames, default_value);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addCheckbox(const std::string& name, bool default_value)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvCheckbox(parent, name, default_value);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addListbox(const std::string& name, const std::vector<std::string>& itemnames, int default_value, int height)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvListbox(parent, name, itemnames, default_value, height);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addCombo(const std::string& name, const std::vector<std::string>& itemnames, const std::string& default_value)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvCombo(parent, name, itemnames, default_value);
		m_items.push_back(item);
		return item;
	}

	//-----------------------------------------------------------------------------
	// Tabs
	//-----------------------------------------------------------------------------

	mvAppItem* mvApp::addTabBar(const std::string& name)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvTabBar(parent, name);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::addTab(const std::string& name)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvTab(parent, name);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::endTab()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndTab(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	mvAppItem* mvApp::endTabBar()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndTabBar(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	//-----------------------------------------------------------------------------
	// Adding Menus
	//-----------------------------------------------------------------------------

	mvAppItem* mvApp::addMenuBar(const std::string& name)
	{
		m_windowflags |= ImGuiWindowFlags_MenuBar;
		mvAppItem* item = new mvMenuBar(name);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::addMenu(const std::string& name)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvMenu(parent, name);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::addMenuItem(const std::string& name)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvMenuItem(parent, name);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::endMenu()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndMenu(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	mvAppItem* mvApp::endMenuBar()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndMenuBar(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	//-----------------------------------------------------------------------------
	// Groups
	//-----------------------------------------------------------------------------

	mvAppItem* mvApp::addGroup(const std::string& name)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvGroup(parent, name);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::endGroup()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndGroup(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	//-----------------------------------------------------------------------------
	// Child Window
	//-----------------------------------------------------------------------------

	mvAppItem* mvApp::addChild(const std::string& name, int width, int height)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvChild(parent, name, width, height);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::endChild()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndChild(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	mvAppItem* mvApp::addWindow(const std::string& name, int width, int height)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvWindowAppitem(parent, name, width, height);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::endWindow()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndWindowAppitem(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	//-----------------------------------------------------------------------------
	// Misc Items
	//-----------------------------------------------------------------------------

	mvAppItem* mvApp::addCollapsingHeader(const std::string& name)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvCollapsingHeader(parent, name);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::endCollapsingHeader()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndCollapsingHeader(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	mvAppItem* mvApp::addSpacing(int count)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvSpacing(parent, count);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addSameLine(float offsetx, float spacing)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvSameLine(parent, offsetx, spacing);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addTooltip(const std::string& parent, const std::string& name)
	{

		mvAppItem* item = new mvTooltip(parent, name);
		m_items.push_back(item);
		pushParent(item);
		return item;
	}

	mvAppItem* mvApp::endTooltip()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvEndTooltip(parent);
		m_items.push_back(item);
		popParent();
		return item;
	}

	mvAppItem* mvApp::addSeperator()
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvSeparator(parent);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::indent(float offset)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvIndent(parent, offset);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::unindent(float offset)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvUnindent(parent, offset);
		m_items.push_back(item);
		return item;
	}

	//-----------------------------------------------------------------------------
	// Text
	//-----------------------------------------------------------------------------

	mvAppItem* mvApp::addText(const std::string& name, int wrap, mvColor color, bool bullet)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvText(parent, name, wrap, color, bullet);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addLabelText(const std::string& name, const std::string& value, int wrap, mvColor color, bool bullet)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvLabelText(parent, name, value, wrap, color, bullet);
		m_items.push_back(item);
		return item;
	}

	//-----------------------------------------------------------------------------
	// Logging
	//-----------------------------------------------------------------------------

	void mvApp::Log(const std::string& text, const std::string& level)
	{
		if (m_loglevel < 1)
			AppLog::getLogger()->AddLog("[%05d] [%1s]  %2s\n", ImGui::GetFrameCount(), level.c_str(), text.c_str());
	}

	void mvApp::LogDebug(const std::string& text)
	{
		if (m_loglevel < 2)
			AppLog::getLogger()->AddLog("[%05d] [DEBUG]  %1s\n", ImGui::GetFrameCount(), text.c_str());
	}

	void mvApp::LogInfo(const std::string& text)
	{
		if (m_loglevel < 3)
			AppLog::getLogger()->AddLog("[%05d] [INFO]  %1s\n", ImGui::GetFrameCount(), text.c_str());
	}

	void mvApp::LogWarning(const std::string& text)
	{
		if (m_loglevel < 4)
			AppLog::getLogger()->AddLog("[%05d] [WARNING]  %1s\n", ImGui::GetFrameCount(), text.c_str());
	}

	void mvApp::LogError(const std::string& text)
	{
		if (m_loglevel < 5)
			AppLog::getLogger()->AddLog("[%05d] [ERROR]  %1s\n", ImGui::GetFrameCount(), text.c_str());
	}

	void mvApp::ClearLog()
	{
		AppLog::getLogger()->Clear();
	}

	mvAppItem* mvApp::addSimplePlot(const std::string& name, const std::vector<float> value, const std::string& overlay, float scale_min, float scale_max, float height, bool histogram)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvSimplePlot(parent, name, value, overlay, scale_min, scale_max, height, histogram);
		m_items.push_back(item);
		return item;
	}

	mvAppItem* mvApp::addPlot(const std::string& name, int width, int height)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvPlot(parent, name, width, height);
		m_items.push_back(item);
		return item;
	}

	//-----------------------------------------------------------------------------
	// Drawing
	//-----------------------------------------------------------------------------
	mvAppItem* mvApp::addDrawing(const std::string& name, int width, int height)
	{
		std::string parent = "";
		if (mvAppItem* parentitem = topParent())
			parent = parentitem->getName();

		mvAppItem* item = new mvDrawing(parent, name, width, height);
		m_items.push_back(item);
		return item;
	}

	void mvApp::clearDrawing(const std::string& drawing)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->clear();
	}

	void mvApp::drawLine(const std::string& drawing, const mvVec2& p1, const mvVec2& p2, const mvColor& color, int thickness)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawLine(p1, p2, color, thickness);
	}

	void mvApp::drawTriangle(const std::string& drawing, const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvColor& color, const mvColor& fill, float thickness)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawTriangle(p1, p2, p3, color, fill, thickness);
	}

	void mvApp::drawRectangle(const std::string& drawing, const mvVec2& pmin, const mvVec2& pmax, const mvColor& color, const mvColor& fill, float rounding, float thickness)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawRectangle(pmin, pmax, color, fill, rounding, thickness);
	}

	void mvApp::drawQuad(const std::string& drawing, const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvVec2& p4, const mvColor& color, const mvColor& fill, float thickness)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawQuad(p1, p2, p3, p4, color, fill, thickness);
	}

	void mvApp::drawText(const std::string& drawing, const mvVec2& pos, const std::string& text, const mvColor& color, int size)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawText(pos, text, color, size);
	}

	void mvApp::drawCircle(const std::string& drawing, const mvVec2& center, float radius, const mvColor& color, int segments, float thickness, const mvColor& fill)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawCircle(center, radius, color, segments, thickness, fill);
	}

	void mvApp::drawPolyline(const std::string& drawing, const std::vector<mvVec2>& points, const mvColor& color, bool closed, float thickness)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawPolyline(points, color, closed, thickness);
	}

	void mvApp::drawPolygon(const std::string& drawing, const std::vector<mvVec2>& points, const mvColor& color, const mvColor& fill, float thickness)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawPolygon(points, color, fill, thickness);
	}

	void mvApp::drawBezierCurve(const std::string& drawing, const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvVec2& p4, const mvColor& color, float thickness, int segments)
	{
		mvAppItem* item = getItem(drawing);
		mvDrawing* dwg = static_cast<mvDrawing*>(item);
		dwg->drawBezierCurve(p1, p2, p3, p4, color, thickness, segments);
	}

}