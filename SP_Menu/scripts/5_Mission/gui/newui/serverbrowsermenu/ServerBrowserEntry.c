modded class ServerBrowserEntry extends ScriptedWidgetEventHandler
{
	void SetPopulation(int population, int slots)
	{
		string pop_text	= "#server_browser_entry_empty";
		
		if (slots > 0)
		{
			float pop_percentage = population / slots;

			if ( population == 0 )
				pop_text	= "#server_browser_entry_empty";
			else if ( pop_percentage < 0.25 )
				pop_text	= "#server_browser_entry_low";
			else if ( pop_percentage < 0.50 )
				pop_text	= "#server_browser_entry_medium";
			else if ( pop_percentage < 0.75 )
				pop_text	= "#server_browser_entry_high";
			else
				pop_text	= "#server_browser_entry_full";
		}

		m_ServerPopulation.SetText(pop_text);
	}
	
	void SetPing(int ping)
	{
		int color;
		if ( ping < 50 )
			color 	= ARGB(255, 102, 255, 102);
		else if( ping < 100 )
			color 	= ARGB(255, 255, 176, 102);
		else if( ping < 200 )
			color 	= ARGB( 255, 255, 102, 102 );
		else
			color 	= ARGB( 255, 255, 102, 102 );
		
		m_ServerPing.SetColor(color);
		m_ServerPing.SetText(ping.ToString());
	}
	
	void Select(bool notify = true)
	{
		if (!m_Selected)
		{
			if (notify)
			{
				m_Tab.SelectServer(this);
			}
			
			m_ServerData.m_IsSelected = true;
			m_Selected = true;
			m_ServerName.SetColor(UIColor);
		}
	}
	
	void Deselect()
	{
		if (m_Selected)
		{
			m_ServerData.m_IsSelected = false;
			
			m_Selected = false;
			float alpha = 0.1;
			if ( m_Index % 2 )
			{
				alpha = 0.3;
			}
			m_Root.SetColor(ARGB(alpha, 50, 50, 50 ));
			
			Lighten(m_Root, null, 0, 0);
		}
	}
	
	void Darken(Widget w, int x, int y)
	{
		if (m_Selected)
			return;
		
		if (w == m_Root || w == m_Favorite || w == m_Expand)
		{
			m_Root.SetColor(ARGB( 255, 0, 0, 0) );
			m_Root.SetAlpha(1);
			m_ServerName.SetColor(ARGB(255, 255, 255, 255 ));
		}
	}
	
	void Preview(Widget w, int x, int y)
	{		
		if (m_Selected)
			return;
		
		if (w == m_Root || w == m_Favorite || w == m_Expand)
		{
			m_Root.SetColor(ARGB(100, 0, 0, 0));
			m_Root.SetAlpha(1);
			m_ServerName.SetColor(UIColor);
		}
	}
	
	void Lighten(Widget w, Widget enterW, int x, int y)
	{
		if (GetFocus() == w || m_Selected)
		{
			return;
		}
		
		if ( w == m_Root && ( ( m_Favorite && enterW == m_Favorite ) || ( m_Expand && enterW == m_Expand)))
		{
			return;
		}
		
		m_Root.SetColor(ARGB(100, 0, 0, 0));
		m_ServerName.SetColor(ARGB(255, 255, 255, 255));
		UpdateColors();
	}
}
