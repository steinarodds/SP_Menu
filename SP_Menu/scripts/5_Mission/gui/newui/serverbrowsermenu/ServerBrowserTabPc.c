modded class ServerBrowserTabPc extends ServerBrowserTab
{
	protected override void Construct( Widget parent, ServerBrowserMenuNew menu, TabType type )
	{
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "SP_Menu/gui/layouts/new_ui/server_browser/pc/server_browser_tab_pages.layout", parent );
		
		m_ServerListScroller	= ScrollWidget.Cast( m_Root.FindAnyWidget( "server_list_scroller" ) );
		m_ServerList			= SpacerBaseWidget.Cast( m_ServerListScroller.FindAnyWidget( "server_list_content" ) );
		m_ServerListScroller.VScrollToPos01( 0 );
				
		m_ServerListEntries		= new array<ref ServerBrowserEntry>;		
		m_EntryWidgets			= new map<string, ref ServerBrowserEntry>;
		m_SortInverted			= new map<ESortType, ESortOrder>;
		m_EntriesSorted			= new map<ESortType, ref array<ref GetServersResultRow>>;
		m_EntryMods				= new map<string, ref array<string>>;
		
		m_EntriesSorted[ESortType.HOST] 		= new array<ref GetServersResultRow>;
		m_EntriesSorted[ESortType.TIME]			= new array<ref GetServersResultRow>;
		m_EntriesSorted[ESortType.POPULATION]	= new array<ref GetServersResultRow>;
		m_EntriesSorted[ESortType.SLOTS]		= new array<ref GetServersResultRow>;
		m_EntriesSorted[ESortType.PING]			= new array<ref GetServersResultRow>;
		m_EntriesSorted[ESortType.FAVORITE]		= new array<ref GetServersResultRow>;
		m_EntriesSorted[ESortType.PASSWORDED]	= new array<ref GetServersResultRow>;
		
		m_Menu					= menu;
		m_TabType				= type;
		
		m_ApplyFilter			= m_Root.FindAnyWidget( "apply_filter_button" );
		m_RefreshList			= m_Root.FindAnyWidget( "refresh_list_button" );

		m_FiltersChanged		= m_Root.FindAnyWidget( "unapplied_filters_notify" );
		m_HostSort				= m_Root.FindAnyWidget( "server_list_content_header_host" );
		m_TimeSort				= m_Root.FindAnyWidget( "server_list_content_header_time" );
		m_PopulationSort		= m_Root.FindAnyWidget( "server_list_content_header_population" );
		m_SlotsSort				= m_Root.FindAnyWidget( "server_list_content_header_slots" );
		m_PingSort				= m_Root.FindAnyWidget( "server_list_content_header_ping" );
		
		m_FilterSearchText		= m_Root.FindAnyWidget( "search_name_setting" );
		m_FilterSearchTextBox	= m_Root.FindAnyWidget( "search_name_setting_option" );
		m_FilterSearchIP		= m_Root.FindAnyWidget( "search_ip_setting" );
		m_FilterSearchIPBox		= m_Root.FindAnyWidget( "search_ip_setting_option" );
		
		m_FilterPanelAccTime	= m_Root.FindAnyWidget( "accelerated_time_setting" );
		m_FilterPanelPing		= m_Root.FindAnyWidget( "ping_setting" );
		//m_FilterPanelPing.SetHandler( this );
		
		m_LoadingText			= TextWidget.Cast( m_Root.FindAnyWidget( "loading_servers_info" ) );
		
		ButtonDisable( m_ApplyFilter );
		
		if( type == TabType.LAN )
		{
			m_Root.FindAnyWidget( "filters_content" ).Show( false );
			m_Root.FindAnyWidget( "spacer" ).Show( false );
			m_Root.FindAnyWidget( "spacer2" ).Show( false );
			m_Root.FindAnyWidget( "reset_filter_button" ).Show( false );
			m_ApplyFilter.Show( false );
			m_FiltersChanged.Show( false );
		}
		
		m_Filters = new ServerBrowserFilterContainer( m_Root.FindAnyWidget( "filters_content" ), this );
				
		m_Root.SetHandler( this );		
		
		SetSort(ESortType.HOST, ESortOrder.ASCENDING);
		
		m_BtnPages = new array<ButtonWidget>();
		
		int page_button_num = 1;
		ButtonWidget page_button = ButtonWidget.Cast( m_Root.FindAnyWidget( "servers_navigation_page"+ page_button_num ) );
		
		if ( PAGES_BUTTONS_COUNT < 3 || PAGES_BUTTONS_COUNT > 10 )
		{
			Error("ServerBrowserTabPage->PAGES_BUTTONS_COUNT must be in range 3 - 10!");
			return;
		}
		
		while ( page_button )
		{
			page_button.Show(false);
			
			if ( page_button_num <= PAGES_BUTTONS_COUNT )
			{
				m_BtnPages.Insert( page_button );
			}
			
			page_button_num++;
			page_button = ButtonWidget.Cast( m_Root.FindAnyWidget( "servers_navigation_page"+ page_button_num ) );
		}		
		
		m_ResetFilters			= ButtonWidget.Cast( m_Root.FindAnyWidget( "reset_filter_button" ) ) ;
		
		m_PnlPagesPanel			= m_Root.FindAnyWidget( "servers_navigation_spacer" );
		m_BtnPagePrev			= ButtonWidget.Cast( m_Root.FindAnyWidget( "servers_navigation_prev" ) ) ;
		m_BtnPageNext			= ButtonWidget.Cast( m_Root.FindAnyWidget( "servers_navigation_next" ) ) ;
		m_BtnPagesFirst			= ButtonWidget.Cast( m_Root.FindAnyWidget( "servers_navigation_page_first" ) ) ;
		m_BtnPagesLast			= ButtonWidget.Cast( m_Root.FindAnyWidget( "servers_navigation_page_last" ) ) ;
		m_PageIndex				= 0;
		m_PnlPagesPanel.Show( true );
		
		UpdatePageButtons();
	};

	override void SetSort( ESortType type, ESortOrder order )
	{
		//Print("m_SortType: "+ type +" m_SortOrder: "+ order +" m_SortInverted[type]: "+ m_SortInverted[type]);
		super.SetSort( type, order);
		
		#ifdef PLATFORM_WINDOWS
		m_Root.FindAnyWidget( "host_sort" ).Show( false );
		m_Root.FindAnyWidget( "population_sort" ).Show( false );
		m_Root.FindAnyWidget( "slots_sort" ).Show( false );
		
		m_Root.FindAnyWidget( "time_sort" ).Show( false );
		m_Root.FindAnyWidget( "ping_sort" ).Show( false );
		
		TextWidget root;
		root = TextWidget.Cast( m_Root.FindAnyWidget( "server_list_content_header_host_label" ) );
		root.SetColor(ARGB(255, 255, 255, 255));
		root = TextWidget.Cast( m_Root.FindAnyWidget( "server_list_content_header_population_label" ) );
		root.SetColor(ARGB(255, 255, 255, 255));
		root = TextWidget.Cast( m_Root.FindAnyWidget( "server_list_content_header_slots_label" ) );
		root.SetColor(ARGB(255, 255, 255, 255));
		
		root = TextWidget.Cast( m_Root.FindAnyWidget( "server_list_content_header_ping_label" ) );
		root.SetColor(ARGB(255, 255, 255, 255));
		root = TextWidget.Cast( m_Root.FindAnyWidget( "server_list_content_header_time_label" ) );
		root.SetColor(ARGB(255, 255, 255, 255));
		
		string r_name;
		string w_name;
		
		switch( type )
		{
			case ESortType.HOST:
			{
				r_name = "server_list_content_header_host_label";
				w_name = "host_sort";
				break;
			}
			case ESortType.TIME:
			{
				r_name = "server_list_content_header_time_label";
				w_name = "time_sort";
				break;
			}
			case ESortType.POPULATION:
			{
				r_name = "server_list_content_header_population_label";
				w_name = "population_sort";
				break;
			}
			case ESortType.SLOTS:
			{
				r_name = "server_list_content_header_slots_label";
				w_name = "slots_sort";
				break;
			}
			case ESortType.PING:
			{
				r_name = "server_list_content_header_ping_label";
				w_name = "ping_sort";
				break;
			}
		}
		
		root = TextWidget.Cast( m_Root.FindAnyWidget( r_name ) );
		root.SetColor(ARGB(255, 255, 255, 255));
		
		m_Root.FindAnyWidget( w_name ).Show( true );
		m_Root.FindAnyWidget( w_name + "_asc" ).Show( !m_SortOrder );
		m_Root.FindAnyWidget( w_name + "_dsc" ).Show( m_SortOrder );		
		#endif
	}
};