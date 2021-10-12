modded class OptionSelectorEditbox extends OptionSelectorBase
{
	override void ColorHighlight( Widget w )
	{
		if( !w )
			return;
		
		if ( m_EditBox )
		{
			SetFocus( m_EditBox );
			m_EditBox.SetColor(UIColor);
		};

		super.ColorHighlight( w );
	};
};