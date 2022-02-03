modded class DayZIntroScene
{
	static ref DayZIntroScene intro;
	ref array<Object> AllSceneProps;
	
	void DayZIntroScene()
	{
		// Set this as the new static instance, remove previous if necessary
		if ( intro )	delete intro;
		intro = this;
		AllSceneProps = new array<Object>;
		
		// Get Map
		string mapname;
		GetGame().GetWorldName( mapname );
		mapname.ToLower();
		
		// Get Current Scene
		string pathAllScenes = "cfgCustomScenes " + g_Game.GetWorldName(); // was CFG cfgcharacterscenes 
		int numScenes = g_Game.ConfigGetChildrenCount( pathAllScenes );
		int sceneIndex = 0; // If you add more scenes in config, make this Math.RandomInt( 0, numScenes );
		string nameCurrentScene;
		g_Game.ConfigGetChildName( pathAllScenes, sceneIndex, nameCurrentScene );
		string pathCurrentScene = pathAllScenes + " " + nameCurrentScene;
		
		// Weather ( must have overcast, rain, and fog; windspeed and storm are optional
		float overcast = g_Game.ConfigGetFloat( pathCurrentScene + " overcast" );
		float rain = g_Game.ConfigGetFloat( pathCurrentScene + " rain" );
		float fog = g_Game.ConfigGetFloat( pathCurrentScene + " fog" );
		float windspeed = -1;
		if ( g_Game.ConfigIsExisting( pathCurrentScene + " windspeed" ) )
		{
			windspeed = g_Game.ConfigGetFloat( pathCurrentScene + " windspeed" );
		}
		auto storm = new TFloatArray;
		if ( g_Game.ConfigIsExisting( pathCurrentScene + " storm" ) )
		{
			g_Game.ConfigGetFloatArray( pathCurrentScene + " storm", storm );
		}
		m_Weather = g_Game.GetWeather();
		m_Weather.GetOvercast().SetLimits( overcast, overcast );
		m_Weather.GetRain().SetLimits( rain, rain );
		m_Weather.GetFog().SetLimits( fog, fog );
		m_Weather.GetOvercast().Set( overcast, 0, 0 );
		m_Weather.GetRain().Set( rain, 0, 0 );
		m_Weather.GetFog().Set( fog, 0, 0 );
		if ( windspeed != -1 )
		{
			m_Weather.SetWindSpeed( windspeed );
			m_Weather.SetWindMaximumSpeed( windspeed );
			m_Weather.SetWindFunctionParams( 1, 1, 1 );
		}
		if ( storm && storm.Count() == 3 )
		{
			m_Weather.SetStorm( storm[0], storm[1], storm[2] );
		}
		
		// Date
		auto date = new TIntArray;
		g_Game.ConfigGetIntArray( pathCurrentScene + " date", date );
		World world = g_Game.GetWorld();
		if ( world && date && date.Count() >= 5 )
		{
			world.SetDate( date[0], date[1], date[2], date[3], date[4] );
		}
		
		// Player
		m_CharacterPos = g_Game.ConfigGetVector( pathCurrentScene + " PlayerPosition" );
		m_CharacterRot = g_Game.ConfigGetVector( pathCurrentScene + " PlayerOrientation" );
		m_Character = new IntroSceneCharacter();
		m_Character.LoadCharacterData( m_CharacterPos, m_CharacterRot );
		
		// Camera
		GetGame().ObjectDelete( m_Camera );
		vector positionCamera = g_Game.ConfigGetVector( pathCurrentScene + " CameraPosition" );
		CastTo( m_Camera, g_Game.CreateObject( "staticcamera", positionCamera, true ) );
		float fov = g_Game.ConfigGetFloat(pathCurrentScene + " fov");
		if ( g_Game.ConfigIsExisting( pathCurrentScene + " CameraTarget" ) )
		{
			m_Target = g_Game.ConfigGetVector( pathCurrentScene + " CameraTarget" ); // May have to use SwapYZ, must test
		}
		else
		{
			m_Target = m_CharacterPos; // If target not specified, the camera will target the player
		}
		if ( m_Camera )
		{
			m_Camera.LookAt( m_Target );
			m_Camera.SetFOV( fov );
			m_Camera.SetFocus( 1.0, 0.0 );
			m_Camera.SetActive( true );
		}
		
		// Props
		if ( mapname == "namalsk" )
		{			
			// Objects 
			SpawnObject( "Land_fireplace_1", "5501.998535 125.092094 8139.871094", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "bldr_prop_Fireplace", "5502.066895 124.430479 8139.726563", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "bag_6B38_camo_mung", "5500.080078 124.802002 8142.089844", "-95.000000 -15.000000 0.000000" );
			SpawnObject( "oillamp_mung", "5500.103027 125.328079 8142.544922", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "dynamitestick_Mung", "5500.180176 124.940987 8141.750000", "-144.999985 -85.000008 -180.000000" );
			SpawnObject( "dynamitestick_Mung", "5500.180176 124.941002 8141.750000", "-65.499985 -85.000008 -179.999985" );
			SpawnObject( "OP_SleepingBagGreyPlacing", "5501.330078 124.955002 8143.350098", "82.099998 0.000000 0.000000" );
			SpawnObject( "FBF_AreaLight_Warm", "5562.998535 127.292094 8139.871094", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "baseballbatbarb_mung", "5500.560059 125.026016 8142.330078", "0.000000 9.999998 -45.000000" );
			SpawnObject( "FS_L85A2", "5500.293457 125.209999 8141.943848", "64.999992 15.000007 -109.999985" );
			SpawnObject( "Land_Ruin_HouseBig2_NoIvy_Half", "5473.580078 118.226997 8150.250000", "84.354477 6.000000 -0.100000" );
			SpawnObject( "Land_Ruin_HouseSmall1_NoIvy", "5476.870117 118.405998 8127.350098", "-10.571598 0.000000 -4.999998" );
			SpawnObject( "FS_DogZ_Telo", "5502.399902 124.948006 8143.689941", "-92.500000 0.500000 -84.999985" );
			SpawnObject( "FS_DogZ_Golova", "5502.784668 124.995003 8142.997070", "-0.500000 23.999996 -66.600006" );
			SpawnObject( "FS_DogZ_LAPA2", "5502.349609 125.338005 8139.900391", "-35.000000 -4.999998 -99.999985" );
			SpawnObject( "bldr_prop_WolfSteakMeat", "5502.454102 125.273293 8139.576660", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "bldr_prop_WolfSteakMeat", "5502.334961 125.273293 8139.508301", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "bldr_prop_WolfSteakMeat", "5502.331055 125.273003 8139.710449", "13.999998 0.000000 0.000000" );
			SpawnObject( "bldr_fireplace_grill", "5502.275391 125.286636 8139.703125", "0.000000 -0.000000 -0.000000" );
			// AI
			CreateCharacter( "5501.459961 124.866997 8138.970215", "49.999996 0.000000 0.000000", "SharpWoodenStick", DayZPlayerConstants.CMD_GESTUREFB_SITA, DayZPlayerConstants.STANCEMASK_CROUCH );
			CreateCharacter( "5501.55 124.818 8141.69", "90 0.000000 0.300000", "ASVAL", EmoteGelikGunOnShoulder.CMD_GESTUREFB_GelikGunOnShoulder, DayZPlayerConstants.STANCEMASK_ERECT );
			CreateCharacter( "5500.820078 125.055002 8142.750098", "95 0.000000 0.300000", "", DayZPlayerConstants.CMD_GESTUREFB_LYINGDOWN, DayZPlayerConstants.STANCEMASK_CROUCH );
			CreateCharacter( "5503.045898 124.799004 8143.384766", "-84.999985 0.000000 0.000000", "Fangeknife", DayZPlayerConstants.CMD_ACTIONFB_ANIMALSKINNING, DayZPlayerConstants.STANCEMASK_CROUCH );
		};
		if ( mapname == "banov" )
		{
			// Objects
			SpawnObject( "FS_NPC_OxranaVSS_Monolit", "9566.469727 271.398010 5851.839844", "45.999992 0.000000 0.000000" );
			SpawnObject( "bldr_prop_MediumTent", "9566.684570 271.419220 5841.118652", "10.029170 -0.000000 -0.000000" );
			SpawnObject( "bldr_prop_Fireplace", "9567.739258 271.372375 5847.802734", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "SV_IBarrel1", "9565.838867 272.014923 5851.797363", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "FBF_AreaLight_Warm", "9567.709961 271.521118 5847.771973", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "bldr_Mosin9130", "9565.820313 271.821991 5852.240234", "-14.099998 1.999999 79.999985" );
			SpawnObject( "Ammo_762x54Tracer", "9565.740234 272.587006 5852.009766", "0.000000 0.000000 0.000000" );
			SpawnObject( "Ammo_762x54Tracer", "9565.790039 272.579987 5851.990234", "35.000000 0.000000 0.000000" );
			SpawnObject( "DeadChicken_White", "9566.060547 271.509979 5852.182129", "-130.000000 54.999992 0.000000" );
			SpawnObject( "bldr_shelfs_small_crushed", "9565.026367 271.426636 5843.457520", "0.000000 -0.000000 -0.000000" );
			SpawnObject( "FS_GAS_balon", "9571.750000 271.394012 5850.049805", "-38.627296 -4.400000 -0.300000" );
			SpawnObject( "bldr_Cemetery_SmallCross", "9572.535156 271.767700 5848.689453", "138.428085 -0.000000 -0.000000" );
			SpawnObject( "bldr_Rubble_DirtPile_Small", "9571.933594 271.413513 5849.613281", "-126.849991 0.000000 3.000000" );
			SpawnObject( "SP_Radio_Banov", "9572.208984 270.577698 5849.928711", "0.000000 -0.000000 -0.000000" );
			// AI
			CreateCharacter( "9566.550781 271.343994 5847.661621", "95.000000 0.000000 0.000000", "SharpWoodenStick", DayZPlayerConstants.CMD_GESTUREFB_SITA, DayZPlayerConstants.STANCEMASK_CROUCH );
			CreateCharacter( "9568.822266 271.358490 5847.562012", "-79.999985 0.000000 0.000000", "", EmoteGelikNaKortax.CMD_GESTUREFB_GelikNaKortax, DayZPlayerConstants.STANCEMASK_CROUCH );
			CreateCharacter( "9572.373047 271.343964 5849.848145", "-117.184303 -0.000000 -0.000000", "CA_Guitar", CMD_GESTUREFB_GelikGuitarsit, DayZPlayerConstants.STANCEMASK_CROUCH );
		};
	};
	
	void SpawnObject( string classname, vector position, vector rotation )
	{
		AllSceneProps.Insert( GetGame().CreateObject( classname, position ) );
		AllSceneProps[AllSceneProps.Count() - 1].SetOrientation( rotation );
	};
	
	PlayerBase CreateCharacter( vector position, vector rotation, string itemInHands = "", int emote = -1, int stance = -1, string character = "" )
	{
		if ( !character )
			character = GetGame().CreateRandomPlayer();
		
		AllSceneProps.Insert( GetGame().CreateObject( character, position ) );
		PlayerBase player = PlayerBase.Cast( AllSceneProps[AllSceneProps.Count() - 1] );
		
		player.SetOrientation( rotation );
		
		player.GetInventory().CreateInInventory( GlassesGame.GetRandomElement() );
		player.GetInventory().CreateInInventory( GlovesGame.GetRandomElement() );
		player.GetInventory().CreateInInventory( ShirtsGame.GetRandomElement() );
		player.GetInventory().CreateInInventory( VestsGame.GetRandomElement() );
		player.GetInventory().CreateInInventory( PantsGame.GetRandomElement() );
		player.GetInventory().CreateInInventory( ShoesGame.GetRandomElement() );
		player.GetInventory().CreateInInventory( BeltGame.GetRandomElement() );
		player.GetInventory().CreateInInventory( BagsGame.GetRandomElement() );
		
		if ( itemInHands )
			player.GetHumanInventory().CreateInHands( itemInHands );
		
		if ( emote != -1 && stance != -1 )
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( StartAction, 500, true, player, emote, stance );
		
		return player;
	};
	
	PlayerBase StartAction( PlayerBase player, int emote = -1, int stance = -1 )
	{
		player.StartCommand_Action( emote , ActionBaseCB, stance );
		return player;
	};
};