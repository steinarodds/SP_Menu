modded class LoginQueueBase extends UIScriptedMenu
{
	private TextWidget m_RandomMessage;
	private TextWidget m_txtlabel;

	override Widget Init()
	{		
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("SP_Menu/gui/layouts/dialog_queue_position.layout");
		
		m_txtPosition = TextWidget.Cast(layoutRoot.FindAnyWidget("txtPosition"));
		m_txtlabel = TextWidget.Cast(layoutRoot.FindAnyWidget("txtlabel"));
		m_txtNote = TextWidget.Cast(layoutRoot.FindAnyWidget("txtNote"));
		m_btnLeave = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnLeave"));
		m_txtNote.Show(true);
		layoutRoot.FindAnyWidget("notification_root").Show(false);

		string lscreen = QueueGame.GetRandomElement();
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

		//Add Color to some text.
		m_txtlabel.SetColor(UIColorText);

		return layoutRoot;
	};
};