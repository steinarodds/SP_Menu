modded class LogoutMenu extends UIScriptedMenu
{	
    private ImageWidget m_Logotipo;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("SP_Menu/gui/layouts/day_z_logout_dialog.layout");
		
		m_LogoutTimeText = TextWidget.Cast( layoutRoot.FindAnyWidget("txtLogoutTime") );
		m_DescriptionText = TextWidget.Cast( layoutRoot.FindAnyWidget("txtDescription") );
		m_bLogoutNow = ButtonWidget.Cast( layoutRoot.FindAnyWidget("bLogoutNow") );
		m_bCancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget("bCancel") );

        m_Logotipo = ImageWidget.Cast(layoutRoot.FindAnyWidget("dayz_logo"));
        
        if (ShowLogo)
        {
            m_Logotipo.Show(true);
            m_Logotipo.LoadImageFile(0, logotipo);
        }
        else
        {
            m_Logotipo.Show(false);
        };

		m_bCancel.Show( true );
		m_bLogoutNow.Show( true );
		layoutRoot.FindAnyWidget("toolbar_bg").Show( false );
		
		UpdateInfo();
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player.GetEmoteManager() && !player.IsRestrained() && !player.IsUnconscious()) 
		{
			player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_SITA);
			player.GetEmoteManager().GetEmoteLauncher().SetForced(EmoteLauncher.FORCE_DIFFERENT);
		};
		
		return layoutRoot;
	};

	override bool OnMouseEnter(Widget w, int x, int y)
    {
        ColorHighlight (w);
        return true;
    };

    override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
    {
        ColorNormal (w);
        return true;
    };

	protected void ColorHighlight(Widget w)
    {
        if (!w)
            return;

        ButtonSetTextColor(w, UIColor);
    };

    protected void ColorNormal(Widget w)
    {
        if (!w)
            return;

        ButtonSetTextColor(w, ARGB(255, 255, 255, 255));
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

    override void SetTime(int time)
    {
        m_iTime = time;
        m_LogoutTimeText.SetText(m_iTime.ToString() + " #th_exiting");
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
};