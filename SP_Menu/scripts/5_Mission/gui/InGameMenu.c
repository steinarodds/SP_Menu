modded class InGameMenu extends UIScriptedMenu
{
	protected Widget 			m_Painel;
	protected Widget 			m_Discord;
	protected Widget 			m_DeadScreen;

	protected TextWidget 		m_PlayersKilledValue;
	protected TextWidget 		m_TimeSurvivedValue;
	protected TextWidget 		m_InfectedKilledValue;
	protected TextWidget 		m_DistanceTraveledValue;
	protected TextWidget 		m_LongRangeShotValue;

	protected ImageWidget 		m_DeadScreenImage;
	float m_DeadScreenFadeInIncrement = 1.3 / 2.75;
	float m_DeadScreenFadeInLevel;
	float m_DeadScreenImageFadeInIncrement = 1.2 / 1.45;
	float m_DeadScreenImageFadeInLevel;
	float m_ShowAlpha;
	float m_TimerSlice;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("SP_Menu/gui/layouts/day_z_ingamemenu.layout");
				
		m_ContinueButton			= layoutRoot.FindAnyWidget( "continuebtn" );
		m_ExitButton				= layoutRoot.FindAnyWidget( "exitbtn" );
		m_RestartButton				= layoutRoot.FindAnyWidget( "restartbtn" );
		m_RespawnButton 			= layoutRoot.FindAnyWidget( "respawn_button" );
		m_RestartDeadRandomButton	= layoutRoot.FindAnyWidget( "respawn_button_random" );
		m_RestartDeadCustomButton	= layoutRoot.FindAnyWidget( "respawn_button_custom" );
		m_OptionsButton				= layoutRoot.FindAnyWidget( "optionsbtn" );
		m_ModdedWarning				= TextWidget.Cast( layoutRoot.FindAnyWidget( "ModdedWarning" ) );
		m_HintPanel					= new UiHintPanel(layoutRoot.FindAnyWidget( "hint_frame" ));
		m_ServerInfoPanel 			= layoutRoot.FindAnyWidget( "server_info" );
		m_ServerIP 					= TextWidget.Cast( layoutRoot.FindAnyWidget( "server_ip" ) );
		m_ServerPort 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "server_port" ) );
		m_ServerName 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "server_name" ) );
		m_FavoriteImage 			= layoutRoot.FindAnyWidget( "favorite_image" );
		m_UnfavoriteImage 			= layoutRoot.FindAnyWidget( "unfavorite_image" );
		m_CopyInfoButton 			= layoutRoot.FindAnyWidget( "copy_button" );

		m_Discord 					= layoutRoot.FindAnyWidget("discordbtn");
		m_Painel 					= layoutRoot.FindAnyWidget("painelbtn");

		#ifdef SERVERPANEL
			m_Painel.Show(true);
		#else
			m_Painel.Show(false);
		#endif
		
		if (GetGame().IsMultiplayer())
		{
			ButtonSetText(m_RestartButton, "#main_menu_respawn");
		}
		else
		{
			ButtonSetText(m_RestartButton, "#main_menu_restart");
		}		
		
		HudShow( false );
		SetGameVersion();
		SetServerInfoVisibility(SetServerInfo() && g_Game.GetProfileOption( EDayZProfilesOptions.SERVERINFO_DISPLAY ));
		m_ModdedWarning.Show( g_Game.ReportModded() );

		//Deathscreen
		m_DeadScreen = Widget.Cast(layoutRoot.FindAnyWidget("dead_screen"));
		m_DeadScreen.SetAlpha(0);
		m_DeadScreen.Show(false);
		m_DeadScreenImage = ImageWidget.Cast(m_DeadScreen.FindAnyWidget("dead_screen_image"));
		m_DeadScreenImage.LoadImageFile(0, ShowDeadScreenImage);
		m_DeadScreenImage.SetAlpha(0);

		m_TimeSurvivedValue = TextWidget.Cast(layoutRoot.FindAnyWidget("TimeSurvivedValue"));
		m_PlayersKilledValue = TextWidget.Cast(layoutRoot.FindAnyWidget("PlayersKilledValue"));
		m_InfectedKilledValue = TextWidget.Cast(layoutRoot.FindAnyWidget("InfectedKilledValue"));
		m_DistanceTraveledValue = TextWidget.Cast(layoutRoot.FindAnyWidget("DistanceTraveledValue"));
		m_LongRangeShotValue = TextWidget.Cast(layoutRoot.FindAnyWidget("LongRangeShotValue"));
		
		return layoutRoot;
	};

	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);

		if (w == m_Discord)
		{
			GetGame().OpenURL(DiscordLink);
			return true;
		}
		#ifdef SERVERPANEL
		else if (w == m_Painel)
		{
			EnterScriptedMenu(SERVER_PANEL);
			return true;
		}
		#endif
		return false;
	};

	override void Update(float timeslice)
	{
		UpdateInfo();

		if (m_ShowDeadScreen)
		{
			m_TimerSlice += timeslice;
			if (m_TimerSlice >= 0.01)
			{
				DeathFunction(timeslice);
				m_TimerSlice = 0;
			}
		}
		super.Update(timeslice);
	};

	void DeathFunction(float timeslice)
	{
		float new_deadscreen_val;

		if (m_DeadScreenImageFadeInLevel != 1)
		{
			m_DeadScreen.Show(true);
			new_deadscreen_val = m_DeadScreenFadeInLevel + m_DeadScreenFadeInIncrement * timeslice;
			if (new_deadscreen_val < 1)
				m_DeadScreenFadeInLevel = new_deadscreen_val;
			else
				m_DeadScreenFadeInLevel = 1;

			if (m_DeadScreenFadeInLevel > 0.5)
			{
				float new_logo_val = m_DeadScreenImageFadeInLevel + m_DeadScreenImageFadeInIncrement * timeslice;
				if (new_deadscreen_val < 1)
					m_DeadScreenImageFadeInLevel = new_logo_val;
				else
					m_DeadScreenImageFadeInLevel = 1;
			}
			m_DeadScreen.SetAlpha(m_DeadScreenFadeInLevel);
			m_DeadScreenImage.SetAlpha(m_DeadScreenImageFadeInLevel);
		};
	};

	protected void ColorHighlight(Widget w)
    {
        if (!w)
            return;

        ButtonSetTextColor(w, UIColor);
    };

	override void OnShow()
    {
        super.OnShow();
        PPEffects.SetBlurInventory(0.3);
    };

    override void OnHide()
    {
        super.OnHide();
        PPEffects.SetBlurInventory(0);
    };

    void UpdateInfo()
    {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

    	if (player)
		{
			float stat_value;
			string stat_text;
			
			m_TimeSurvivedValue.SetText(GetTimeString(player.StatGet(AnalyticsManagerServer.STAT_PLAYTIME)));
			m_PlayersKilledValue.SetText(GetValueString(player.StatGet(AnalyticsManagerServer.STAT_PLAYERS_KILLED)));
			m_InfectedKilledValue.SetText(GetValueString( player.StatGet(AnalyticsManagerServer.STAT_INFECTED_KILLED)));
			m_DistanceTraveledValue.SetText(GetDistanceString( player.StatGet(AnalyticsManagerServer.STAT_DISTANCE)));
			m_LongRangeShotValue.SetText(GetDistanceString( player.StatGet(AnalyticsManagerServer.STAT_LONGEST_SURVIVOR_HIT), true ));
		};
    };

	protected string GetTimeString( float total_time )
	{
		string day_symbol = " d";							//define symbols
		string hour_symbol = " h";
		string minute_symbol = " min";
		
		if ( total_time > 0 )
		{
			string time_string;		
			int time_seconds = total_time; 						//convert total time to int
			
			int days = time_seconds / 3600 / 24;
			int hours = time_seconds / 3600 % 24;
			int minutes = ( time_seconds % 3600 ) / 60;
			
			if ( days > 0 )
			{
				time_string += GetValueString( days ) + day_symbol;		//days
				time_string += " ";										//separator
			}
			
			if ( hours > 0 || days > 0 )
			{
				time_string += GetValueString( hours ) + hour_symbol;	//hours
				time_string += " ";										//separator
			}			

			if ( minutes >= 0 )
			{
				time_string += GetValueString( minutes ) + minute_symbol;	//minutes
			}			

			return time_string;
		}
		
		return "0" + " " + minute_symbol;
	};
	
	protected string GetDistanceString( float total_distance, bool meters_only = false )    
    {
        if( total_distance < 0 )
            return "0m";
    
        int distance_meters = total_distance;
        string distance_string;
        
        int kilometers = distance_meters / 1000;
        if ( kilometers > 0 && !meters_only )    
        {
            distance_string += GetValueString( kilometers ) + "km";            //kilometers
            distance_string += " ";                                            //separator
        }
        else    
        {
            distance_string += GetValueString( distance_meters ) + "m";        //meters
        }
        
        return distance_string;
    };
    
    protected string GetValueString( float total_value )    
    {
        if( total_value < 0 )
            return "0";
    
        int value = total_value;
        string out_string;
        
        if ( value >= 1000 )    
        {
            string value_string = value.ToString();
            
            int count;        
            int first_length = value_string.Length() % 3;        //calculate position of the first separator
            if ( first_length > 0 )    
            {
                count = 3 - first_length;
            }
            
            for ( int i = 0; i < value_string.Length(); ++i )    
            {
                out_string += value_string.Get( i );
                count ++;
                
                if ( count >= 3 )    
                {
                    out_string += " ";            //separator
                    count = 0;
                }
            }
        }
        else    
        {
            out_string = value.ToString();
        }
        return out_string;
    };
};