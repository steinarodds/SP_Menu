modded class DayZIntroScene
{
	protected Weather					m_Weather;

	void DayZIntroScene()
	{
		World world = g_Game.GetWorld();
		string root_path = "cfgCustomScenes " + g_Game.GetWorldName();
		int count = g_Game.ConfigGetChildrenCount(root_path);

		string childName;
		g_Game.ConfigGetChildName(root_path, 0, childName);
	
		string scene_path 	   = root_path + " " + childName;

		vector PlayerPosition = g_Game.ConfigGetVector(scene_path + " PlayerPosition");
		vector PlayerOrientation = g_Game.ConfigGetVector(scene_path + " PlayerOrientation");
		vector CameraPosition = g_Game.ConfigGetVector(scene_path + " CameraPosition");
		float  fov = g_Game.ConfigGetFloat(scene_path + " fov");

		if (world)
		{
			TIntArray date = new TIntArray;
			g_Game.ConfigGetIntArray(scene_path + " date", date);
			world.SetDate(date.Get(0), date.Get(1), date.Get(2), date.Get(3), date.Get(4));
		}

		GetGame().ObjectDelete(m_Camera);
		Class.CastTo(m_Camera, g_Game.CreateObject("staticcamera", CameraPosition, true));

		if (m_Camera)
		{
			m_Camera.SetFOV(fov);
			m_Camera.SetFocus(1.0, 0.0);
			m_Camera.SetActive(true);
		};

		SpawnCharacters();
		Objects();

		m_Character = new IntroSceneCharacter();
		m_Character.LoadCharacterData(PlayerPosition, PlayerOrientation);

		float overcast, rain, windspeed, fog;
		overcast = g_Game.ConfigGetFloat(scene_path + " overcast");
		rain = g_Game.ConfigGetFloat(scene_path + " rain");
		fog = g_Game.ConfigGetFloat(scene_path + " fog");
		m_Weather = g_Game.GetWeather();
		m_Weather.GetOvercast().SetLimits( overcast, overcast );
		m_Weather.GetRain().SetLimits( rain, rain );
		m_Weather.GetFog().SetLimits( fog, fog );
		
		m_Weather.GetOvercast().Set( overcast, overcast, 0);
		m_Weather.GetRain().Set( rain, rain, 0);
		m_Weather.GetFog().Set( fog, fog, 0);
	};

	void SpawnObject(string classname, vector position, vector rotation)
	{
		Object obj;
		obj = GetGame().CreateObject(classname, position);

		if(position)
			obj.SetPosition(position);

		if(rotation)
			obj.SetOrientation(rotation);

		obj.SetPosition(position);
		obj.SetOrientation(rotation);
	};

	void Objects()
	{
		string mapname = "";

		GetGame().GetWorldName(mapname);
		mapname.ToLower();

		if (mapname == "namalsk")
		{             
             SpawnObject("Land_fireplace_1", "5501.998535 125.092094 8139.871094", "0.000000 -0.000000 -0.000000");
             SpawnObject("bldr_prop_Fireplace", "5502.066895 124.430479 8139.726563", "0.000000 -0.000000 -0.000000");
             SpawnObject("bag_6B38_camo_mung", "5500.080078 124.802002 8142.089844", "-95.000000 -15.000000 0.000000");
             SpawnObject("oillamp_mung", "5500.103027 125.328079 8142.544922", "0.000000 -0.000000 -0.000000");
             SpawnObject("dynamitestick_Mung", "5500.180176 124.940987 8141.750000", "-144.999985 -85.000008 -180.000000");
             SpawnObject("dynamitestick_Mung", "5500.180176 124.941002 8141.750000", "-65.499985 -85.000008 -179.999985");
             SpawnObject("OP_SleepingBagGreyPlacing", "5501.330078 124.955002 8143.350098", "82.099998 0.000000 0.000000");
             SpawnObject("FBF_AreaLight_Warm", "5562.998535 127.292094 8139.871094", "0.000000 -0.000000 -0.000000");
             SpawnObject("baseballbatbarb_mung", "5500.560059 125.026016 8142.330078", "0.000000 9.999998 -45.000000");
             SpawnObject("FS_L85A2", "5500.293457 125.209999 8141.943848", "64.999992 15.000007 -109.999985");
             SpawnObject("Land_Ruin_HouseBig2_NoIvy_Half", "5473.580078 118.226997 8150.250000", "84.354477 6.000000 -0.100000");
             SpawnObject("Land_Ruin_HouseSmall1_NoIvy", "5476.870117 118.405998 8127.350098", "-10.571598 0.000000 -4.999998");
             SpawnObject("FS_DogZ_Telo", "5502.399902 124.948006 8143.689941", "-92.500000 0.500000 -84.999985");
             SpawnObject("FS_DogZ_Golova", "5502.784668 124.995003 8142.997070", "-0.500000 23.999996 -66.600006");
             SpawnObject("FS_DogZ_LAPA2", "5502.349609 125.338005 8139.900391", "-35.000000 -4.999998 -99.999985");
             SpawnObject("bldr_prop_WolfSteakMeat", "5502.454102 125.273293 8139.576660", "0.000000 -0.000000 -0.000000");
             SpawnObject("bldr_prop_WolfSteakMeat", "5502.334961 125.273293 8139.508301", "0.000000 -0.000000 -0.000000");
             SpawnObject("bldr_prop_WolfSteakMeat", "5502.331055 125.273003 8139.710449", "13.999998 0.000000 0.000000");
             SpawnObject("bldr_fireplace_grill", "5502.275391 125.286636 8139.703125", "0.000000 -0.000000 -0.000000");
        };   
        if (mapname == "Banov")
		{             
             SpawnObject("Land_fireplace_1", "9563.48 271.695 5848.32", "0.000000 -0.000000 -0.000000");
             SpawnObject("Land_fireplace_1", "9563.48 271.695 5848.32", "0.000000 -0.000000 -0.000000");
             SpawnObject("FBF_AreaLight_Warm", "9563.61 271.71 5848.25", "-86.689 -0.000000 -0.000000");
             SpawnObject("FireplaceIndoor", "9563.61 271.71 5848.25", "-86.689 -0.000000 -0.000000");
        };       
	};

	PlayerBase CreateCharacter(vector position, vector rotation, string itemInHands = "", int emote = -1, int stance = -1, string character = "")
	{
	   	if (character == "")
	   	{
	    	character  = GetGame().CreateRandomPlayer();
	   	}

	   	PlayerBase player = PlayerBase.Cast(GetGame().CreateObject(character, position));   
	   
	   	if(position)
	     	player.SetPosition(position);
	   	if(rotation)
	     	player.SetOrientation(rotation);

	   	player.SetPosition(position);
	   	player.SetOrientation(rotation);

	   	player.GetInventory().CreateInInventory(GlassesGame.GetRandomElement());
	   	player.GetInventory().CreateInInventory(GlovesGame.GetRandomElement());
	   	player.GetInventory().CreateInInventory(ShirtsGame.GetRandomElement());
	   	player.GetInventory().CreateInInventory(VestsGame.GetRandomElement());
	   	player.GetInventory().CreateInInventory(PantsGame.GetRandomElement());
	   	player.GetInventory().CreateInInventory(ShoesGame.GetRandomElement());
	   	player.GetInventory().CreateInInventory(BeltGame.GetRandomElement());
	   	player.GetInventory().CreateInInventory(BagsGame.GetRandomElement());

	   	if (itemInHands != "")
	   	{
			player.GetHumanInventory().CreateInHands(itemInHands);
	   	}

		if (emote != -1 && stance != -1)
      	{
         	GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(StartAction, 500, true, player, emote, stance);
      	};

	  	return player;
	};

    PlayerBase StartAction (PlayerBase player, int emote = -1, int stance = -1)
    {
        player.StartCommand_Action(emote , ActionBaseCB, stance);
        return player;
    };

	void SpawnCharacters()
	{
		string mapname = "";

		GetGame().GetWorldName(mapname); 
		mapname.ToLower();

		if (mapname == "namalsk")
		{
			CreateCharacter("5501.459961 124.866997 8138.970215", "49.999996 0.000000 0.000000",	"SharpWoodenStick", DayZPlayerConstants.CMD_GESTUREFB_SITA, DayZPlayerConstants.STANCEMASK_CROUCH);
			CreateCharacter("5501.55 124.818 8141.69", "90 0.000000 0.300000",	"ASVAL", EmoteGelikGunOnShoulder.CMD_GESTUREFB_GelikGunOnShoulder, DayZPlayerConstants.STANCEMASK_ERECT);
			CreateCharacter("5500.820078 125.055002 8142.750098", "95 0.000000 0.300000",	"", DayZPlayerConstants.CMD_GESTUREFB_LYINGDOWN, DayZPlayerConstants.STANCEMASK_CROUCH);
			CreateCharacter("5503.045898 124.799004 8143.384766", "-84.999985 0.000000 0.000000",	"Fangeknife", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, DayZPlayerConstants.STANCEMASK_CROUCH);
		};
				if (mapname == "Banov")
		{
			CreateCharacter("9564.52 271.377 5847.89", "-67.3848 0.000000 0.000000",	"SharpWoodenStick", DayZPlayerConstants.CMD_GESTUREFB_SITA, DayZPlayerConstants.STANCEMASK_CROUCH); // Next to fire from left
			CreateCharacter("5501.55 124.818 8141.69", "90 0.000000 0.300000",	"ASVAL", EmoteGelikGunOnShoulder.CMD_GESTUREFB_GelikGunOnShoulder, DayZPlayerConstants.STANCEMASK_ERECT);
			CreateCharacter("5500.820078 125.055002 8142.750098", "95 0.000000 0.300000",	"", DayZPlayerConstants.CMD_GESTUREFB_LYINGDOWN, DayZPlayerConstants.STANCEMASK_CROUCH);
			CreateCharacter("5503.045898 124.799004 8143.384766", "-84.999985 0.000000 0.000000",	"Fangeknife", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, DayZPlayerConstants.STANCEMASK_CROUCH);
		};
	};
};     