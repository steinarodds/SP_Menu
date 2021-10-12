/**
* IntroSceneCharacter.c
*
* THEBRITTO
* https://steamcommunity.com/id/THEBRITTO/
* https://thebritto.com.br
* © 2021
*/

modded class IntroSceneCharacter extends Managed
{
	protected void CharacterLoad( int character_id, vector char_pos, vector char_rot )
	{
		if ( character_id == -1 )
		{
			Error("IntroSceneCharacter->CharacterLoad: character_id = "+ character_id +" Cant Load Character!!!");
			return;
		}
		
		CharacterUnload();
		
		SetCharacterID( character_id );
				
		m_CharacterObj = PlayerBase.Cast( m_CharacterDta.CreateCharacterPerson( character_id ) );
		
		if ( m_CharacterObj )
		{
			
			m_CharacterObj.PlaceOnSurface();
			m_CharacterObj.SetPosition(char_pos);
			m_CharacterObj.SetOrientation(char_rot);
			m_CharacterObj.StartCommand_Action(DayZPlayerConstants.CMD_GESTUREFB_SITA, EmoteCB, DayZPlayerConstants.STANCEMASK_ERECT);
		}	
	}
};