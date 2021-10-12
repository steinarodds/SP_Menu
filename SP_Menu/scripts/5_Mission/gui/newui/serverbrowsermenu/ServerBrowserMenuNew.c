modded class ServerBrowserMenuNew extends UIScriptedMenu
{
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SP_Menu/gui/layouts/new_ui/server_browser/pc/server_browser.layout" );
		m_OfficialTab	= new ServerBrowserTabPc( layoutRoot.FindAnyWidget( "Tab_0" ), this, TabType.OFFICIAL );
		m_CommunityTab	= new ServerBrowserTabPc( layoutRoot.FindAnyWidget( "Tab_1" ), this, TabType.COMMUNITY );
		m_LANTab		= new ServerBrowserTabPc( layoutRoot.FindAnyWidget( "Tab_2" ), this, TabType.LAN );

		layoutRoot.FindAnyWidget( "Tabber" ).GetScript( m_Tabber );
		
		m_Play					= layoutRoot.FindAnyWidget( "play" );
		m_Back					= layoutRoot.FindAnyWidget( "back_button" );
		m_CustomizeCharacter	= layoutRoot.FindAnyWidget( "customize_character" );
		m_PlayerName			= TextWidget.Cast( layoutRoot.FindAnyWidget( "character_name_text" ) );
		m_Version				= TextWidget.Cast( layoutRoot.FindAnyWidget( "version" ) );
		
		Refresh();
		
		string version;
		GetGame().GetVersion( version );
		
		version = "#main_menu_version" + " " + version;
		m_Version.SetText( version );
		
		OnlineServices.m_ServersAsyncInvoker.Insert( OnLoadServersAsync );
		OnlineServices.m_ServerModLoadAsyncInvoker.Insert( OnLoadServerModsAsync );
		m_Tabber.m_OnTabSwitch.Insert( OnTabSwitch );
				
		m_OfficialTab.RefreshList();
		
		PPEffects.SetBlurMenu(0.3);
		return layoutRoot;
	};

	override void ColorHighlight( Widget w )
	{
		if( !w )
			return;
		
		//SetFocus( w );
		
		int color_pnl = ARGB(0, 0, 0, 0);
		int color_lbl = UIColor;
				
		ButtonSetColor(w, color_pnl);
		ButtonSetTextColor(w, color_lbl);
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