modded class OptionsMenu extends UIScriptedMenu
{
	override Widget Init()
	{
		m_Options			= new GameOptions();
		
		layoutRoot			= GetGame().GetWorkspace().CreateWidgets( "SP_Menu/gui/layouts/new_ui/options/pc/options_menu.layout", null );
		
		layoutRoot.FindAnyWidget( "Tabber" ).GetScript( m_Tabber );
		
		m_Details			= layoutRoot.FindAnyWidget( "settings_details" );
		m_Version			= TextWidget.Cast( layoutRoot.FindAnyWidget( "version" ) );
		
		m_GameTab			= new OptionsMenuGame( layoutRoot.FindAnyWidget( "Tab_0" ), m_Details, m_Options, this );
		m_SoundsTab			= new OptionsMenuSounds( layoutRoot.FindAnyWidget( "Tab_1" ), m_Details, m_Options, this );
		m_VideoTab			= new OptionsMenuVideo( layoutRoot.FindAnyWidget( "Tab_2" ), m_Details, m_Options, this );
		m_ControlsTab		= new OptionsMenuControls( layoutRoot.FindAnyWidget( "Tab_3" ), m_Details, m_Options, this );
		
		m_Apply				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "apply" ) );
		m_Back				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "back" ) );
		m_Reset				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "reset" ) );
		
		string version;
		GetGame().GetVersion( version );
		version = "#main_menu_version" + " " + version;
		m_Version.SetText( version );
		
		ToggleFocus();
		
		m_Tabber.m_OnTabSwitch.Insert( OnTabSwitch );
		
		OnChanged();

		#ifdef S_FRAMEWORK
		int newIndex = m_Tabber.GetTabCount(); //make it last so we son't have problem with possible future additions
		m_Tabber.AddTab(newIndex.ToString());
		TextWidget.Cast( layoutRoot.FindAnyWidget( "Tab_Control_"+newIndex+"_Title" )).SetText("sUDE");
		m_sUDETab = new OptionsMenuSUDE(layoutRoot.FindAnyWidget( "Tab_" + newIndex ));
		#endif
		
		return layoutRoot;
	};

    override void ColorHighlight(Widget w)
    {
        if (!w)
            return;

        ButtonSetTextColor(w, UIColor);
    };

 	protected void ButtonSetTextColor(Widget w, int color)
    {
        if (!w)
            return;

        TextWidget label = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_label"));
                    
        if (label)
        {
            label.SetColor(color);
        };
    };

	void OnShow()
	{
		super.OnShow();
		PPEffects.SetBlurMenu(0.3);
	};

	void OnHide()
	{
		super.OnHide();
		PPEffects.SetBlurMenu(0);
	};
};
