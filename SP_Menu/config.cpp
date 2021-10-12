class CfgPatches
{
	class SP_Menu
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","Trader"};
	};
};

class CfgMods
{
	class SP_Menu
	{
		dir = "";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "SP_Menu";
		credits = "";
		author = "";
		authorID = "0";
		version = "0.1";
		extra = 0;
		type = "mod";
		inputs = "SP_Menu/inputs/inputs.xml";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class widgetStyles
			{
				files[] = {"SP_Menu/gui/looknfeel/prefabs.styles"};
			};
			class imageSets
			{
				files[] = {"SP_Menu/gui/imagesets/imageset.imageset","SP_Menu/gui/imagesets/prefabs.imageset"};
			};
			class gameScriptModule
			{
				files[] = {"SP_Menu/scripts/3_Game"};
			};
			class worldScriptModule
			{
				files[] = {"SP_Menu/scripts/4_World"};
			};
			class missionScriptModule
			{
				files[] = {"SP_Menu/scripts/5_Mission"};
			};
		};
	};
};

class cfgCustomScenes
{
	class ChernarusPlus
	{
		class loc1
		{
			PlayerPosition[] 	= {5928.615234, 88.646721, 3307.680908};
            PlayerOrientation[] = {-70.999794, 0.000000, 0.000000};
            CameraPosition[] 	= {5921.136230, 90.551735, 3310.168945};
            fov=0.50;
			overcast = 1;
			rain = 1;
			fog = 1;
			windspeed = 1;
			date[] = {1997, 1, 15, 12, 00};
		};
	};
	class Deerisle
	{
		class loc1
		{
            PlayerPosition[] 	= {526.447144, 3.288893, 12292.446289};
            PlayerOrientation[] = {-102.999580, 0.000000, 0.000000};
            CameraPosition[] 	= {522.109619, 4.080920, 12291.453125};
            fov=0.75;
			overcast = 1;
			rain = 1;
			fog = 1;
			windspeed = 1;
			date[] = {1997, 1, 15, 12, 00};
		};	
	};
	class Chiemsee
	{
		class loc1
		{
            PlayerPosition[] 	= {9148.746094, 88.959999, 10193.042969};
            PlayerOrientation[] = {149, 0, 0};
            CameraPosition[] 	= {9153.825195, 90.3, 10186.232422};
            fov=0.35;
            overcast = 1;
			rain = 1;
			fog = 1;
			windspeed = 1;
			date[] = {1997, 12, 15, 22, 00};
		};	
	};
	class Namalsk
	{
		class loc1
		{
            PlayerPosition[] 	= {5502.299805, 124.899002, 8141.149902};
            PlayerOrientation[] = {86, 0.000000, 0.000000};
            CameraPosition[] 	= {5506.604492, 126.278406, 8141.439063};
            fov=1.0;
            overcast = 1.0;
			rain = 0.736;
			fog = 0.221;
			windspeed = 0.2;
			date[] = {2020, 2, 3, 16, 15};
		};
	};
	class TakistanPlus
	{
		class loc1
		{
            PlayerPosition[] 	= {5943.619629, 83.040001, 11859.925781};
            PlayerOrientation[] = {74.999985, 0, 0};
            CameraPosition[] 	= {594.687500, 84.540001, 11853.825195};   
            fov=0.50;
            overcast = 1;
			rain = 1;
			fog = 1;
			windspeed = 1;
			date[] = {1997, 1, 15, 12, 00};
		};
	};
};

class CfgSoundSets
{
	class Main_Music_Menu_SoundSet
	{
		soundShaders[] = {"Main_Music_Menu_SoundShader"};
		volumeFactor = 1;
		frequencyFactor = 1;
		spatial = 0;
	};
};	

class CfgSoundShaders
{
	class Main_Music_Menu_SoundShader
	{
		samples[] = {{"SP_Menu\gui\sounds\MainMenu.ogg", 1}};
		volume = 0.25;
	};
};