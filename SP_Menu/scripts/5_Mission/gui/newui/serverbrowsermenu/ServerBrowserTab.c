modded class ServerBrowserTab extends ScriptedWidgetEventHandler
{
    protected void ColorHighlight(Widget w)
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
};