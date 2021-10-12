modded class DropdownPrefab extends ScriptedWidgetEventHandler
{
	int AddElement( string text, Widget content = null )
	{
		ButtonWidget element = ButtonWidget.Cast( GetGame().GetWorkspace().CreateWidgets( "SP_Menu/gui/layouts/new_ui/dropdown_prefab/dropdown_element.layout", m_ContentContainer ) );
		element.SetText( text );
		
		if( content )
		{
			element.AddChild( content, false );
		}
		m_ContentContainer.Update();
		m_Root.Update();
		
		m_Content.Insert( element );
		return m_Content.Count() - 1;
	};
};