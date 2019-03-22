// Definition.
#ifndef DRAW_H
#define DRAW_H

// Drawing.
void Draw() {
	// Clearing.
	ardu.clear();
	
	// State switching.
  if (varTransition == 0) {
  	switch(gameState) {
  		// Title screen.
  		case STATE_TITLE:
        spr.drawSelfMasked(9, 0, SprTitle, 0);
        spr.drawSelfMasked(77, 16, SprPortrait, 0);
        DrawText(0, 24, 1, strMaxLen);
        DrawText(0, 40, 2, strMaxLen);
        DrawText(12, 48, 3 + (uint8_t)varOptionVolume, strMaxLen);
  			break;

      // Help.
      case STATE_HELP:
        DrawTextCenter(64, 20, 6, strMaxLen);
        DrawTextCenter(64, 36, 7, strMaxLen);
        break;

      // Story.
      case STATE_STORY:
        DrawTextCenter(64, 20, 10 + (uint8_t)varGameLevel, varTextLen + ((uint8_t)varTextLine * strMaxLen));
        if (varTextLine > 0) DrawTextCenter(64, 36, 25 + (uint8_t)varGameLevel, varTextLen);
        break;

      // Gameplay.
      case STATE_GAME:
        if (varGameClashTime == 0) ControlPlayer();
        for(uint8_t i = 0; i < 4; i++) {
          if (varGameEnemy[i].inGame) ControlEnemy(i);
        }
        if (varGameDyna.inGame && varGameAnimClock % 2 == 0 && !TimeStop()) ControlDynamite();
        GameDraw();
        break;

      // Help.
      case STATE_LOSE:
        if (!varLoseSelect || ClockEven()) DrawTextCenter(64, 20, 8, strMaxLen);
        if (varLoseSelect || ClockEven()) DrawTextCenter(64, 36, 9, strMaxLen);
        break;

      // Ending.
      case STATE_END:
        DrawTextCenter(64, 4, 40, varTextLen + ((uint8_t)varTextLine * strMaxLen));
        if (varTextLine > 0) DrawTextCenter(64, 12, 41, varTextLen + (((uint8_t)varTextLine - 1) * strMaxLen));
        if (varTextLine > 1) DrawTextCenter(64, 28, 42, varTextLen + (((uint8_t)varTextLine - 2) * strMaxLen));
        if (varTextLine > 2) DrawTextCenter(64, 36, 43, varTextLen + (((uint8_t)varTextLine - 3) * strMaxLen));
        if (varTextLine > 3) DrawTextCenter(64, 52, 44, varTextLen + (((uint8_t)varTextLine - 4) * strMaxLen));
        break;

      // Thanks.
      case STATE_THANK:
        DrawTextCenter(64, 20, 45, strMaxLen);
        DrawTextCenter(64, 36, 46, strMaxLen);
        break;
  	}
  }
	
	// Finalizing.
	ardu.display();
}

// End.
#endif
