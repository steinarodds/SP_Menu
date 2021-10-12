modded class MissionGameplay
{
	private ref Widget LogoRootWidget;
	private ref ImageWidget LogoWidget;
	private ref FileSerializer DataFile;

	private bool LogoEnabled;
	private string OverlayDataPath = "$profile:LogoOverlay.bin";

	void MissionGameplay()
    {
        DataFile = new FileSerializer();
        if (!FileExist(OverlayDataPath))
        {
            LogoEnabled = true;
            SaveOverlayData();
            return;
        }

        LoadOverlayData();
    }

	void ~MissionGameplay()
	{
		delete LogoRootWidget;
		delete LogoWidget;
		delete DataFile;
	}

	override void OnMissionStart()
    {
        super.OnMissionStart();

		LogoRootWidget = GetGame().GetWorkspace().CreateWidgets("SP_Menu/gui/layouts/day_z_logotipo.layout");
		LogoWidget = ImageWidget.Cast(LogoRootWidget.FindAnyWidget("logoWidget"));
		//string lscreen = logotipo.GetRandomElement();
		LogoWidget.LoadImageFile(0, logotipo);
    }

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		if (!LogoRootWidget || !LogoWidget) return;

		if (GetGame().GetInput().LocalPress("ZB_ToggleLogo", true))
		{
			LogoEnabled = !LogoWidget.IsVisible();
			SaveOverlayData();
		}

		if (IsControlDisabled() || IsPaused() || m_Hud.IsHideHudPlayer() || !m_Hud.GetHudState() || !LogoEnabled || !GetGame().GetPlayer())
		{
			LogoWidget.Show(false);
			return;
		}

		LogoWidget.Show(true);
	}

	private void LoadOverlayData()
    {
        if (DataFile.Open(OverlayDataPath, FileMode.READ))
        {
            DataFile.Read(LogoEnabled);
            DataFile.Close();
        }
    }

    private void SaveOverlayData()
    {
        if (DataFile.Open(OverlayDataPath, FileMode.WRITE))
        {
            DataFile.Write(LogoEnabled);
            DataFile.Close();
        }
    }
}