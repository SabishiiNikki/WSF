// Defining hit mods.
#define MOD_NONE  0
#define MOD_BREAK 1
#define MOD_CLASH 2
#define MOD_OVER  3
 
// Ending uncontrolled animation.
void PlayerReenable() {
  varGamePlayer.able = true;
  varGamePlayer.animTime = 0;
  varGamePlayer.animIndex = 0;
  varGamePlayer.solarForm = false;
}
 
// Setting speed based on facing direction.
short signed PlayerFaceSpeed(short signed fS) {
  if (!varGamePlayer.faceRight) return(-fS);
  else return(fS);
}
 
// Forcing animation upon an enemy.
void EnemyAnimation(int8_t fEnemy, byte fIndex, byte fTime, int16_t fSpeed) {
  varGameEnemy[fEnemy].animIndex = fIndex;
  varGameEnemy[fEnemy].animTime = fTime;
  varGameEnemy[fEnemy].speedX = FaceX(varGamePlayer.faceRight, fSpeed);
  varGameEnemy[fEnemy].able = false;
  varGameEnemy[fEnemy].faceRight = !varGamePlayer.faceRight;
}
 
// Dealing damage to enemies.
void DamageEnemy(int8_t fEnemy, short fDamage) {
  if (varGameEnemy[fEnemy].hp > fDamage) varGameEnemy[fEnemy].hp -= fDamage;
  else {
    varGameEnemy[fEnemy].hp = 0;
    varGameEnemy[fEnemy].animFrame = 2;
  }
}
 
// Quickdraw dodge.
void QuickdrawDodge() {
  for(uint8_t i = 0; i < 4; i++) {
    if (varGameQuickdraw == 0) {
      if (!varGameEnemy[i].able && (varGameEnemy[i].animIndex == 2 || varGameEnemy[i].animIndex == 3) && varGameEnemy[i].animTime <= 8 && varGamePlayer.faceRight == (varGamePlayer.x < varGameEnemy[i].x) && varGameEnemy[i].faceRight == (varGamePlayer.x >= varGameEnemy[i].x) && abs(varGameEnemy[i].x - varGamePlayer.x) <= 320) {
        varGameQuickdraw = 210; // 3 seconds of action time, half second compensation for the dodge animation.
        varGamePlayer.faceRight = varGameEnemy[i].faceRight;
        varGamePlayer.speedX = (((int16_t)varGameEnemy[i].x - (int16_t)FaceX(varGameEnemy[i].faceRight, 240)) - (int16_t)varGamePlayer.x) / 30;
        varGamePlayer.dodgeExhaust = 0;
        varGamePlayer.animTime = 30;
      }
    }
  }
}
 
// Hitting enemies.
void PlayerHit(int16_t fRange, uint16_t fDamage, byte fMod) {
  // Loop.
  for(uint8_t i = 0; i < 4; i++) {
    if (varGameEnemy[i].inGame && varGameEnemy[i].hp > 0) {
      if (HitboxInRange(varGamePlayer.x + FaceX(varGamePlayer.faceRight, 80), varGamePlayer.x + FaceX(varGamePlayer.faceRight, fRange * 10), varGameEnemy[i].x - 80, varGameEnemy[i].x + 80)) {
        if (!varGamePlayer.attackHit) varTemp = i;
        else if (abs(varGamePlayer.x - varGameEnemy[i].x) < abs(varGamePlayer.x - varGameEnemy[varTemp].x)) varTemp = i;
        varGamePlayer.attackHit = true;
      }
    }
  }
 
  // Reflecting dynamite.
  if (varGameDyna.inGame && /*FaceX(varGamePlayer.faceRight, abs(varGameDyna.speedX)) == -varGameDyna.speedX*/ varGameDyna.speedY > 0 && fMod == MOD_BREAK &&
    HitboxInRange(varGamePlayer.x + FaceX(varGamePlayer.faceRight, 80), varGamePlayer.x + FaceX(varGamePlayer.faceRight, fRange * 10), varGameDyna.x - 30, varGameDyna.x + 30) && varGameDyna.y >= 360) {
    snd.tones(SndEnemyBlock);
    varGameDyna.speedX = FaceX(varGamePlayer.faceRight, (abs(varGameDyna.speedX) * 8) / 10);
    varGameDyna.speedY = min(-varGameDyna.speedY, -10);
  }
 
  // Hit.
  if (varGamePlayer.attackHit) {
    // Clash win.
    if (fMod == MOD_OVER) {
      DamageEnemy(varTemp, fDamage);
      varGameEnemy[varTemp].animFrame = 2;
      varGameEnemy[varTemp].block = false;
      EnemyAnimation(varTemp, 1, (uint8_t)Mean(30, (int16_t)fDamage * 6), (uint8_t)Mean(30, (int16_t)fDamage * 5));
      snd.tones(SndPlayerHit);
    }
     
    // Clash.
    else if (fMod == MOD_CLASH && varGamePlayer.clashCooldown == 0 && varGamePlayer.faceRight == (varGamePlayer.x < varGameEnemy[varTemp].x) && varGamePlayer.faceRight != varGameEnemy[varTemp].faceRight && !varGameEnemy[varTemp].able && (varGameEnemy[varTemp].animIndex == 2 || varGameEnemy[varTemp].animIndex == 3) && varGameQuickdraw == 0 && fMod != MOD_OVER) {
      varGameClashTime = varGameEnemy[varTemp].speedClash;
      varGameClashEnemy = varTemp;
      varGameClashDir = 0;
      varGamePlayer.speedX = 0;
      varGameEnemy[varTemp].speedX = 0;
      snd.tones(SndEnemyBlock);
    }
     
    // Blocking.
    else if (varGameEnemy[varTemp].block && varGameQuickdraw == 0) {
      // Break block.
      if (fMod == MOD_BREAK) {
        varGameEnemy[varTemp].block = false;
        EnemyAnimation(varTemp, 1, 30, 25);
      }
 
      // Blocked.
      else {
        if (varGameEnemy[varTemp].able || (varGameEnemy[varTemp].animIndex != 2 && varGameEnemy[varTemp].animIndex != 3)) EnemyAnimation(varTemp, 0, 30, 20);
        varGamePlayer.able = false;
        varGamePlayer.animTime = Mean(30, (int16_t)varTemp);
        varGamePlayer.animIndex = 3;
        varGamePlayer.speedX = -FaceX(varGamePlayer.faceRight, 20);
      }
 
      // Sound.
      snd.tones(SndEnemyBlock);
    }
 
    // Normal hit.
    else {
      // Embers.
      for (uint8_t T = 0; T < (uint8_t)Mean((int16_t)fDamage, 5); T++) {
        varTempShort = (uint16_t)random(359);
        NewSolarTrail(((int16_t)varGameEnemy[varTemp].x / 10) + (int16_t)DirX(varTempShort, 12 + (uint8_t)random(8)), 44 + (int16_t)DirY(varTempShort, 12 + (uint8_t)random(8)));
      }
 
      // Damaging.
      DamageEnemy(varTemp, fDamage);
      if (varGameEnemy[varTemp].weak || varGameQuickdraw > 0 || fMod == MOD_OVER) {
        varGameEnemy[varTemp].animFrame = 2;
        EnemyAnimation(varTemp, 1, (uint8_t)Mean(30, (int16_t)fDamage * 6), (uint8_t)Mean(30, (int16_t)fDamage * 5));
      }
      snd.tones(SndPlayerHit);
    }
 
    // Enemy died.
    if (varGameEnemy[varTemp].hp == 0) {
      EnemyAnimation(varTemp, 1, 60, 30);
    }
 
    // Hit-freeze.
    if (varGameQuickdraw == 0) {
      varGamePlayer.hitFreeze = 3;
      varGameEnemy[varTemp].hitFreeze = varGamePlayer.hitFreeze;
    }
 
    // End.
  }
}
 
// Attack effects.
void AttackEffects(short signed fDir, byte fXLen, byte fYLen, signed short fXOff, signed short fYOff, signed short fSign) {
  NewSolarTrail((((int16_t)varGamePlayer.x + (int16_t)varGamePlayer.speedX) / 10) - (fSign * (int16_t)FaceX(varGamePlayer.faceRight, (uint16_t)(fXOff + DirX(fDir, fXLen)))), 46 + fYOff + (int16_t)DirY(fDir, fYLen));
}
 
// Control.
void ControlPlayer() {
  // Clash cooldown.
  if (varGamePlayer.clashCooldown > 0 && ClockEven()) varGamePlayer.clashCooldown--;
   
  // Hit freeze.
  if (varGamePlayer.hitFreeze > 0) varGamePlayer.hitFreeze--;
   
  // Controlling.
  else {
    // Time's up.
    if (varGameHour == 7) {
      varGamePlayer.able = false;
      varGamePlayer.animTime = 60;
      varGamePlayer.animIndex = 2;
      varGamePlayer.animFrame = 4;
      varGamePlayer.solarForm = false;
      varTempShort = (uint16_t)random(90) + 45;
      if (varGameAnimClock % 3 == 0) NewSolarTrail(((int16_t)varGamePlayer.x / 10) + (int16_t)DirX(varTempShort, 10), 44 + (int16_t)DirY(varTempShort, 10));
    }
     
    /*
     * INPUT HANDLING
     */
    if (varGamePlayer.able) {
      // Control off.
      if (!varGamePlayer.control) varGamePlayer.speedX = SlowToStop(varGamePlayer.speedX);
   
      // Control on.
      if (varGamePlayer.control && varGameClashTime == 0) {
        // Stopping.
        if (ardu.pressed(LEFT_BUTTON) == ardu.pressed(RIGHT_BUTTON)) varGamePlayer.speedX = SlowToStop(varGamePlayer.speedX);
         
        // Running.
        else if (ardu.pressed(LEFT_BUTTON)) {
          varGamePlayer.speedX = MoveToSpeed(varGamePlayer.speedX, -PLAYER_SPEED);
          if (varGamePlayer.animIndex == 0) varGamePlayer.faceRight = false;
        }
        else if (ardu.pressed(RIGHT_BUTTON)) {
          varGamePlayer.speedX = MoveToSpeed(varGamePlayer.speedX, PLAYER_SPEED);
          if (varGamePlayer.animIndex == 0) varGamePlayer.faceRight = true;
        }
 
        // Solar dodge.
        if (ardu.justPressed(A_BUTTON) && varGamePlayer.animIndex == 0 && varGameQuickdraw == 0) {
          // Base dodge.
          varGamePlayer.able = false;
          varGamePlayer.animTime = 30;
          varGamePlayer.animIndex = 1;
          varGamePlayer.speedX = PlayerFaceSpeed(30);
          varGamePlayer.solarForm = true;
          QuickdrawDodge();
        }
 
        // Attack.
        else if (ardu.justPressed(B_BUTTON) && varGamePlayer.animIndex == 0) {
          // Reset time.
          varGamePlayer.animTime = 0;
          varGamePlayer.attackHit = false;
 
          // Starting attack.
          if (ardu.pressed(UP_BUTTON) == ardu.pressed(DOWN_BUTTON)) {
            varGamePlayer.animIndex = 1;
            varGamePlayer.attackBack = !varGamePlayer.attackBack;
          }
          else if (ardu.pressed(UP_BUTTON)) varGamePlayer.animIndex = 2;
          else if (ardu.pressed(DOWN_BUTTON)) varGamePlayer.animIndex = 3;
 
          // Sound.
          snd.tones(SndPlayerSwing);
        }
 
        // End control.
      }
    }
   
    // Boundaries.
    if (varGamePlayer.x + varGamePlayer.speedX < 2500) {
      varGamePlayer.x = 2500;
      varGamePlayer.speedX = 0;
    }
    else if (varGamePlayer.x + varGamePlayer.speedX > 7500) {
      varGamePlayer.x = 7500;
      varGamePlayer.speedX = 0;
    }
   
    /*
     * ANIMATION HANDLING
     */
    // Solar form embers.
    varTempShort = (uint16_t)random(359);
    if (varGamePlayer.solarForm && varGameAnimClock % 3 == 0) NewSolarTrail(((int16_t)varGamePlayer.x / 10) + (int16_t)DirX(varTempShort, 6), 44 + (int16_t)DirY(varTempShort, 6));
 
    // Specific animations.
    if (varGamePlayer.able) {
      // Dodge exhaust.
      if (varGamePlayer.dodgeExhaust > 0) varGamePlayer.dodgeExhaust--;
       
      // Standing.
      if (varGamePlayer.speedX == 0) {
        varGamePlayer.animFrame = 0;
      }
   
      // Running.
      else {
        varTemp = ((varGameAnimClockSpec - ((varGameAnimClockSpec / 48) * 48)) - 1) / 12;
        if (varTemp % 2 == 0) {
          //if (varGamePlayer.animFrame == 2 || varGamePlayer.animFrame == 3) snd.tones(SndStep);
          varGamePlayer.animFrame = 1;
        }
        else if (varTemp == 1) varGamePlayer.animFrame = 2;
        else if (varTemp == 3) varGamePlayer.animFrame = 3;
      }
 
      // Attacking.
      if (varGamePlayer.animIndex > 0) {
        // Embers.
        if (varGamePlayer.animIndex == 1) {
          if (!varGamePlayer.attackBack) varTempShort = 90 + (varGamePlayer.animTime * 2);
          else varTempShort = 270 - (varGamePlayer.animTime * 2);
          AttackEffects(varTempShort, 28, 4, 0, 0, 1);
          if (!varGamePlayer.attackHit && CheckMedian(135, varTempShort, 225)) PlayerHit(28, 3, MOD_NONE);
        }
        else if (varGamePlayer.animIndex == 2) {
          varTempShort = 105 + (varGamePlayer.animTime * 3.85);
          AttackEffects(varTempShort, 21, 12, 7, 0, -1);
          if (!varGamePlayer.attackHit && CheckMedian(315, varTempShort, 405)) PlayerHit(28, 4, MOD_BREAK);
        }
        else if (varGamePlayer.animIndex == 3) {
          varTempShort = 495 - (varGamePlayer.animTime * 3.5);
          AttackEffects(varTempShort, 14, 18, 7, -4, -1);
          if (!varGamePlayer.attackHit && CheckMedian(315, varTempShort, 405)) PlayerHit(21, 7, MOD_CLASH);
        }
         
        // Ending.
        if (varGamePlayer.animTime >= 90) {
          varGamePlayer.animIndex = 0;
          varGamePlayer.animTime = 0;
        }
 
        // Progressing.
        else if (varGameClashTime == 0) {
          if (varGamePlayer.animIndex == 1) varGamePlayer.animTime += 9;
          else if (varGamePlayer.animIndex == 2) varGamePlayer.animTime += 5;
          else varGamePlayer.animTime += 4;
        }
      }
    }
    else {
      // Solar dodge.
      if (varGamePlayer.animIndex == 1) {
        if (varGamePlayer.animTime > 0) varGamePlayer.animTime--;
        else {
          varGamePlayer.speedX = 0;
          if (varGamePlayer.dodgeExhaust > 0) {
            varGamePlayer.animIndex = 2;
            varGamePlayer.animTime = varGamePlayer.dodgeExhaust;
            varGamePlayer.solarForm = false;
          }
          else PlayerReenable();
          varGamePlayer.dodgeExhaust = (60 + varGamePlayer.dodgeExhaust) / 2;
        }
      }
       
      // Hurt.
      else if (varGamePlayer.animIndex == 2) {
        varGamePlayer.animFrame = 4;
        if (varGamePlayer.animTime > 0) varGamePlayer.animTime--;
        else PlayerReenable();
      }
 
      // Blocked.
      else if (varGamePlayer.animIndex == 3) {
        if (varGameAnimClock % 3 == 0) NewSolarTrail(((int16_t)varGamePlayer.x / 10) + (int16_t)FaceX(varGamePlayer.faceRight, 8), 56);
        varGamePlayer.animFrame = 0;
        if (varGamePlayer.animTime > 0) varGamePlayer.animTime--;
        else PlayerReenable();
      }
 
      // Clash break.
      else if (varGamePlayer.animIndex == 4) {
        // Attack.
        varTempShort = 45 + (varGamePlayer.animTime * 4);
        AttackEffects(varTempShort, min(21, (uint8_t)min(255, varGamePlayer.animTime)), min(28, (uint8_t)min(255, varGamePlayer.animTime)), 0, -1, 1);
        AttackEffects(varTempShort + 180, min(10, (uint8_t)min(255, varGamePlayer.animTime)), min(14, (uint8_t)min(255, varGamePlayer.animTime)), 0, -1, 1);
        if (!varGamePlayer.attackHit) PlayerHit(21, 12, MOD_OVER);
 
        // Animation.
        if (varGamePlayer.animTime < 90) varGamePlayer.animTime += 3;
        else PlayerReenable();
      }
 
      // Stopping.
      if (varGameQuickdraw == 0 || varGamePlayer.animIndex != 1) varGamePlayer.speedX = SlowToStop(varGamePlayer.speedX);
    }
   
    /*
     * MOVEMENT HANDLING
     */
    varGamePlayer.x += varGamePlayer.speedX;
    varGamePlayer.y += varGamePlayer.speedY;
  }
  // End Heatstroke control.
}
