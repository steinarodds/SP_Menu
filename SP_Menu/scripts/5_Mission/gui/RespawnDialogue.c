// Disabled as syberia runs its own, Respawn dialogue (BANOV)

/* modded class RespawnDialogue extends UIScriptedMenu
{
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("SP_Menu/gui/layouts/day_z_respawn_dialogue.layout");
		m_DetailsRoot 				= layoutRoot.FindAnyWidget( "menu_details_tooltip" );
		m_DetailsLabel				= TextWidget.Cast( m_DetailsRoot.FindAnyWidget( "menu_details_label" ) );
		m_DetailsText				= RichTextWidget.Cast( m_DetailsRoot.FindAnyWidget( "menu_details_tooltip_content" ) );
		
		Widget custom_respawn 		= layoutRoot.FindAnyWidget("respawn_button_custom");
		SetFocus(custom_respawn);
		return layoutRoot;
	};

    protected void ColorHighlight(Widget w)
    {
        if (!w)
            return;

        ButtonSetColor(w, ARGB(0, 0, 0, 0));
        ButtonSetTextColor(w, UIColor);
    };
}; /*
