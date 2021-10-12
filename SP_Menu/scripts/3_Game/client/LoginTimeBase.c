modded class LoginTimeBase extends UIScriptedMenu
{
	private TextWidget m_RandomMessage;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("SP_Menu/gui/layouts/dialog_login_time.layout");
		
		m_txtDescription = TextWidget.Cast( layoutRoot.FindAnyWidget("txtDescription") );
		m_txtLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("txtLabel") );
		m_btnLeave = ButtonWidget.Cast( layoutRoot.FindAnyWidget("btnLeave") );
		m_txtDescription.Show(true);
		layoutRoot.FindAnyWidget("notification_root").Show(false);

        string lscreen = LoginGame.GetRandomElement(); 
        ImageWidget background = ImageWidget.Cast( layoutRoot.FindAnyWidget("Background"));
        background.LoadImageFile(0, lscreen); 

        //Message Random
		if(ShowMessage)
		{
			m_RandomMessage = TextWidget.Cast(layoutRoot.FindAnyWidget("RandomText"));
			m_RandomMessage.SetText(RandomMessage.GetRandomElement());
			m_RandomMessage.SetColor(UIColorText);
			m_RandomMessage.Show(true);
		};

		m_txtLabel.SetColor(UIColorText);

		return layoutRoot;
	};
};