modded class OptionSelectorBase extends ScriptedWidgetEventHandler
{
	override void ColorHighlight( Widget w )
	{
		if( !w )
			return;
				
		ButtonSetColor(w, UIColor);
	};
};