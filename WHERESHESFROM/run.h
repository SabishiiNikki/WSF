// Definition.
#ifndef RUN_H
#define RUN_H

// Running the game.
void Run() {
	// Global animation clock.
	if (varGameAnimClock > 1) varGameAnimClock--;
	else varGameAnimClock = 60;
  if (varGameAnimClockSpec > 1) varGameAnimClockSpec--;
  else varGameAnimClockSpec = 96;
	
	// General wait timer.
	if (varWaitTimer > 0) {varWaitTimer--;}

  // Transition.
  if (varTransition > 0) varTransition--;
  
	// State switching.
	else switch(gameState) {
		// Title screen.
		case STATE_TITLE:
      if (ardu.justPressed(A_BUTTON)) {
        gameState = STATE_HELP;
        varTextLen = 0;
        varTextLine = 0;
        varGameLevel = 0;
        varTransition = 15;
        snd.tones(SndPlayerHit);
      }
      if (ardu.justPressed(B_BUTTON)) {
        if (varOptionVolume < 2) varOptionVolume++;
        else varOptionVolume = 0;
        if (varOptionVolume == 0) ardu.audio.off();
        else if (varOptionVolume == 1) {ardu.audio.on(); snd.volumeMode(VOLUME_ALWAYS_NORMAL);}
        else if (varOptionVolume == 2) snd.volumeMode(VOLUME_ALWAYS_HIGH);
        snd.tones(SndVolume);
      }
			break;

    // Help.
    case STATE_HELP:
      if (ardu.justPressed(A_BUTTON) || ardu.justPressed(B_BUTTON)) {
        gameState = STATE_STORY;
        varTransition = 30;
        snd.tones(SndPlayerHit);
      }
      break;

    // Story.
    case STATE_STORY:
      varTemp = GetStrLen(STR_DATE + (uint8_t)varGameLevel + ((uint8_t)varTextLine * 15));
      if (ardu.justPressed(A_BUTTON) || ardu.justPressed(B_BUTTON)) {
        if (varTextLen < varTemp) {varTextLen = strMaxLen; varTextLine = 1;}
        else {
          gameState = STATE_GAME;
          varTextLen = 0;
          varTextLine = 0;
          varTransition = 30;
          GameReset();
          GameSetup();
        }
        snd.tones(SndPlayerHit);
      }
      else if (varTextLen < varTemp && varGameAnimClock%4 == 0) {
        varTextLen++;
        snd.tones(SndText);
      }
      else if (varTextLine == 0 && varTextLen >= varTemp) {
        varTextLine++;
        varTextLen = 0;
      }
      break;

    // Game.
    case STATE_GAME:
      //GameRun(); // I'm opting to actually have the run being handled in the draw due to the loops required.
      break;

    // Lose.
    case STATE_LOSE:
      if (ardu.justPressed(UP_BUTTON) || ardu.justPressed(DOWN_BUTTON)) {
        varLoseSelect = !varLoseSelect;
        snd.tones(SndText);
      }
      if (ardu.justPressed(A_BUTTON) || ardu.justPressed(B_BUTTON)) {
        snd.tones(SndPlayerHit);
        if (varLoseSelect) gameState = STATE_STORY;
        else gameState = STATE_TITLE;
        varTransition = 30;
      }
      break;

    // Ending.
    case STATE_END:
      varTemp = GetStrLen(STR_END + (uint8_t)varTextLine);
      if ((ardu.justPressed(A_BUTTON) || ardu.justPressed(B_BUTTON)) && varTextLine == 5) {
        gameState = STATE_THANK;
        varTransition = 30;
        snd.tones(SndPlayerHit);
      }
      else if (varTextLine < 5) {
        if (varTextLen < varTemp && varGameAnimClock % 4 == 0) {
          varTextLen++;
          snd.tones(SndText);
        }
        else if (varTextLen >= varTemp) {
          varTextLine++;
          varTextLen = 0;
        }
      }
      break;

    // Help.
    case STATE_THANK:
      if (ardu.justPressed(A_BUTTON) || ardu.justPressed(B_BUTTON)) {
        gameState = STATE_TITLE;
        varTransition = 30;
        snd.tones(SndPlayerHit);
      }
      break;
	}
	
	// End.
}

// End.
#endif
