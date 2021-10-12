modded class OptionSelectorSlider extends OptionSelectorBase
{
	void OptionSelectorSlider( Widget parent, float value, ScriptedWidgetEventHandler parent_menu, bool disabled, float min, float max )
	{
		m_Slider.SetColor(UIColor);
	};

	override bool OnMouseEnter( Widget w, int x, int y )
	{
		if( m_ParentClass )
		{
			OnFocus( w, x, y );
			m_ParentClass.OnFocus( m_Root.GetParent(), -1, m_SelectorType );
			m_ParentClass.OnMouseEnter( m_Root.GetParent().GetParent(), x, y );
			m_Slider.SetColor(UIColor);
		};
		
		return true;
	};

	override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{
		if( m_ParentClass )
		{
			m_ParentClass.OnMouseLeave( m_Root.GetParent().GetParent(), enterW, x, y );
			m_Slider.SetColor(UIColor);
			OnFocusLost( w, x, y );
			SetFocus( null );
		};
			
		return true;
	};
};