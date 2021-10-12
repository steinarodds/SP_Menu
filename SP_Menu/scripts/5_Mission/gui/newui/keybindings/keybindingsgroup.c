modded class KeybindingsGroup extends ScriptedWidgetEventHandler
{
	string GetLayoutName()
	{
		return "SP_Menu/gui/layouts/new_ui/options/keybindings_selectors/keybinding_group.layout";
	};

	override bool OnMouseEnter(Widget w, int x, int y)
	{
	    ColorHighlight (w);
	    return true;
	}

	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
	    ColorNormal (w);
	    return true;
	}

	protected void ColorHighlight(Widget w)
	{
	    if (!w)
	        return;

	    ButtonSetColor(w, ARGB(0, 0, 0, 0));
	    ButtonSetTextColor(w, UIColorText);
	};

	protected void ColorNormal(Widget w)
	{
	    if (!w)
	        return;

	    ButtonSetColor(w, ARGB(0, 0, 0, 0));
	    ButtonSetTextColor(w, ARGB(255, 255, 255, 255));
	};

	protected void ButtonSetColor(Widget w, int color)
	{
	    if (!w)
	        return;
	            
	    Widget panel = w.FindWidget(w.GetName() + "_panel");

	    if (panel)
	    {
	        panel.SetColor(color);
	    };
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
};