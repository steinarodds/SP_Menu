modded class ItemDropWarningMenu extends UIScriptedMenu
{
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("SP_Menu/gui/layouts/day_z_dropped_items.layout");
		
		return layoutRoot;
	};
};