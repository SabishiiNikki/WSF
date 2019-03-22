// Getting gun range.
byte EnemyGetRange(byte fGun) {
  if (fGun == WEAPON_REVOL) return(56);
  else if (fGun == WEAPON_SHOTG) return(48);
  else if (fGun == WEAPON_JGATL) return(64);
  else if (fGun == WEAPON_JFIST) return(24);
  else return(20);
}

// Getting weapon damage. (for reference, the time limit is 420 seconds)
byte EnemyGetDamage(byte fWeapon) {
  if (fWeapon == WEAPON_KNUCK) return(20);
  else if (fWeapon == WEAPON_KNIFE) return(25);
  else if (fWeapon == WEAPON_REVOL) return(22);
  else if (fWeapon == WEAPON_SHOTG) return(40);
  else if (fWeapon == WEAPON_JGATL) return(10); // 8 shots
  else if (fWeapon == WEAPON_JFIST) return(50);
  else return(1);
}

// Setting face.
void EnemySetFace(uint8_t E) {
  varGameEnemy[E].faceRight = (varGamePlayer.x > varGameEnemy[E].x);
}

// Hitting the player.
void HitPlayer(uint8_t E, uint8_t fWeapon) {
  // Range.
  varTemp = EnemyGetRange(fWeapon) + 4;

  // Effects.
  if (varTemp >= 32) {
    snd.tones(SndEnemyShoot);
    for (uint8_t T = 0; T < 2; T++) {
      varTempShort = (uint16_t)random(359);
      NewSolarTrail(((int16_t)varGameEnemy[E].x / 10) + (int16_t)FaceX(varGameEnemy[E].faceRight, 24) + (int16_t)DirX(varTempShort, 4), 48 + (int16_t)DirY(varTempShort, 4));
    }
  }
  else snd.tones(SndPlayerSwing);

  // Solar form.
  if (!varGamePlayer.solarForm) {
    // Collision.
    if (abs((int16_t)varGamePlayer.x - (int16_t)varGameEnemy[E].x) <= ((int16_t)varTemp * 10) && varGameEnemy[E].faceRight == (varGameEnemy[E].x < varGamePlayer.x)) {
      // Damage.
      varTemp = EnemyGetDamage(fWeapon);
      varGameMinute += varTemp;
      while (varGameMinute >= 60) {
        varGameHour++;
        varGameMinute -= 60;
      }
      if (varGameHour >= 7) {
        varGameHour = 7;
        varGameMinute = 0;
      }

      // Disabling player.
      varGamePlayer.able = false;
      varGamePlayer.animTime = Mean(30, (int16_t)varTemp);
      varGamePlayer.animIndex = 2;
      varGamePlayer.faceRight = !varGameEnemy[E].faceRight;
      varGamePlayer.speedX = FaceX(varGameEnemy[E].faceRight, Mean(30, (int16_t)varTemp));
      
      // Effects.
      varGamePlayer.hitFreeze = 4;
      varGameEnemy[E].hitFreeze = varGamePlayer.hitFreeze;
      for (uint8_t T = 0; T < 5; T++) {
        varTempShort = (uint16_t)random(359);
        NewSolarTrail(((int16_t)varGamePlayer.x / 10) + (int16_t)DirX(varTempShort, 12 + (uint8_t)random(8)), 46 + (int16_t)DirY(varTempShort, 12 + (uint8_t)random(8)));
      }
      if (EnemyGetRange(fWeapon) < 32) snd.tones(SndPlayerHit);
      // End.
    }
  }
}

// Throwing dynamite.
void ThrowDynamite(uint8_t E) {
  varGameDyna.inGame = true;
  varGameDyna.x = varGameEnemy[E].x;
  varGameDyna.y = 400;
  varGameDyna.speedX = FaceX(varGameEnemy[E].faceRight, (int16_t)abs(varGameEnemy[E].x - varGamePlayer.x) / 58);
  varGameDyna.speedY = -25;
  snd.tones(SndPlayerSwing);
}

// Control.
void ControlEnemy(uint8_t E) {
  // No timestop.
  if (!TimeStop() && varGameHour < 7) {
    // Hitfreeze.
    if (varGameEnemy[E].hitFreeze > 0) varGameEnemy[E].hitFreeze--;

    // Normal control.
    else {
      // Reblock.
      if (!varGameEnemy[E].block && varGameEnemy[E].reblock > 0) varGameEnemy[E].reblock--;
      else {
        varGameEnemy[E].block = true;
        varGameEnemy[E].reblock = 120;
      }
      
      /*
       * AI HANDLING
       */
      // Attack cooldown.
      if (varGameEnemy[E].attackCooldown > 0) varGameEnemy[E].attackCooldown--;
      
      // Able.
      if (varGameEnemy[E].able) {
        // Calculating current goal X.
        varTemp = EnemyGetRange(varGameEnemy[E].weaponPrimary);
        varTempShort = ((int16_t)varGamePlayer.x + (FaceX((varGamePlayer.x < varGameEnemy[E].x), (int16_t)varTemp - 4) * 10)) - (int16_t)varGameEnemy[E].x;
      
        // Moving in.
        if (abs(varTempShort) > 30) {
          varGameEnemy[E].faceRight = (varTempShort > 0);
          varGameEnemy[E].speedX = MoveToSpeed(varGameEnemy[E].speedX, FaceX(varGameEnemy[E].faceRight, varGameEnemy[E].speedRun));
        }
      
        // Stopping.
        else {
          varGameEnemy[E].speedX = SlowToStop(varGameEnemy[E].speedX);
          EnemySetFace(E);
        }

        // Jack reinforcement.
        /*if (varGameEnemy[E].ironGatlingJack && !varGameEnemy[1].inGame && varGameAnimClock == 60) {
          NewEnemy(1, (uint16_t)(5000 + FaceX((varGamePlayer.x < 5000), 2000)), WEAPON_KNIFE, WEAPON_KNIFE, 10, 30, 60, 120, false, 50, false, true, false);
        }*/

        // Throwing dynamite.
        if ((abs(varGameEnemy[E].x - varGamePlayer.x) / 10) >= (uint16_t)varTemp + 8 && !varGameDyna.inGame && varGameAnimClock == 60 && varGameEnemy[E].dynamite) {
          varGameEnemy[E].animIndex = 0;
          varGameEnemy[E].animTime = 60;
          varGameEnemy[E].able = false;
          EnemySetFace(E);
          ThrowDynamite(E);
        }

        // Attacking.
        else if (varGameEnemy[E].attackCooldown == 0) {
          // Hitting.
          if (abs((varGameEnemy[E].x - varGamePlayer.x) / 10) <= EnemyGetRange(varGameEnemy[E].weaponMelee)) {
            varGameEnemy[E].animIndex = 2;
            varGameEnemy[E].animTime = varGameEnemy[E].speedShoot;
            varGameEnemy[E].able = false;
            EnemySetFace(E);
          }

          // Shooting.
          else if ((uint8_t)(abs(varGameEnemy[E].x - varGamePlayer.x) / 10) <= varTemp) {
            varGameEnemy[E].animIndex = 3;
            varGameEnemy[E].animTime = varGameEnemy[E].speedShoot;
            varGameEnemy[E].able = false;
            EnemySetFace(E);
          }
        }

        // End.
      }
    
      /*
       * ANIMATION HANDLING
       */
      varGameEnemy[E].animWeapon = varGameEnemy[E].weaponPrimary;
      if (varGameEnemy[E].able) {
        if (varGameEnemy[E].speedX != 0 && Even(varGameAnimClock / 30)) varGameEnemy[E].animFrame = 1;
        else varGameEnemy[E].animFrame = 0;
      }
      else {
        // Stopping.
        varGameEnemy[E].speedX = SlowToStop(varGameEnemy[E].speedX);

        // Blocked.
        if (varGameEnemy[E].animIndex == 0) {
          varGameEnemy[E].animFrame = 0;
  
          // Ending.
          if (varGameEnemy[E].animTime > 0) varGameEnemy[E].animTime--;
          else varGameEnemy[E].able = true;
        }
  
        // Stunned.
        else if (varGameEnemy[E].animIndex == 1) {
          varGameEnemy[E].animFrame = 2;
          if (varGameEnemy[E].hp == 0) varGameNext = 150;

          // Animation.
          if (varGameEnemy[E].animTime > 0) varGameEnemy[E].animTime--;

          // Ending.
          else {
            if (varGameEnemy[E].hp == 0) varGameEnemy[E].inGame = false;
            else varGameEnemy[E].able = true;
          }
        }

        // Telegraphing melee.
        else if (varGameEnemy[E].animIndex == 2) {
          varGameEnemy[E].animWeapon = varGameEnemy[E].weaponMelee;
          varGameEnemy[E].animFrame = 0;
          if (varGameEnemy[E].animTime > 0) varGameEnemy[E].animTime--;
          else {
            varGameEnemy[E].animIndex = 4;
            varGameEnemy[E].animTime = 30;
            varGameEnemy[E].speedX = FaceX(varGameEnemy[E].faceRight, 10);
            HitPlayer(E, varGameEnemy[E].weaponMelee);
          }
        }
        
        // Telegraphing shot.
        else if (varGameEnemy[E].animIndex == 3) {
          varGameEnemy[E].animFrame = 1;
          if (varGameEnemy[E].animTime > 0) varGameEnemy[E].animTime--;
          else {
            varGameEnemy[E].animIndex = 5;
            if (varGameEnemy[E].weaponPrimary == WEAPON_JGATL) varGameEnemy[E].animTime = 39;
            else varGameEnemy[E].animTime = 30;
            HitPlayer(E, varGameEnemy[E].weaponPrimary);
          }
        }

        // Swinging.
        else if (varGameEnemy[E].animIndex == 4) {
          varGameEnemy[E].animWeapon = varGameEnemy[E].weaponMelee + 1;
          varGameEnemy[E].animFrame = 1;
          if (varGameEnemy[E].animTime > 0) varGameEnemy[E].animTime--;
          else {
            varGameEnemy[E].able = true;
            varGameEnemy[E].attackCooldown = (uint8_t)((int16_t)varGameEnemy[E].speedAttack * 2, 120);
            varGameEnemy[E].block = varGameEnemy[E].restoreBlock;
          }
        }
        
        // Shooting.
        else if (varGameEnemy[E].animIndex == 5) {
          // Gatling gun.
          if (Even(varGameEnemy[E].animTime) && varGameEnemy[E].animTime >= 24 && varGameEnemy[E].weaponPrimary == WEAPON_JGATL) HitPlayer(E, varGameEnemy[E].weaponPrimary);
          
          // Animation.
          varGameEnemy[E].animFrame = 1;
          if (varGameEnemy[E].animTime > 0) varGameEnemy[E].animTime--;
          else {
            varGameEnemy[E].able = true;
            varGameEnemy[E].attackCooldown = (uint8_t)((int16_t)varGameEnemy[E].speedShoot * 2, 120);
            varGameEnemy[E].block = varGameEnemy[E].restoreBlock;
          }
        }

        // End.
      }
      
      /*
       * MOVEMENT HANDLING
       */
      // Boundaries.
      if (varGameEnemy[E].x + varGameEnemy[E].speedX < 2500) {
        varGameEnemy[E].x = 2500;
        varGameEnemy[E].speedX = 0;
      }
      else if (varGameEnemy[E].x + varGameEnemy[E].speedX > 7500) {
        varGameEnemy[E].x = 7500;
        varGameEnemy[E].speedX = 0;
      }
      varGameEnemy[E].x += varGameEnemy[E].speedX;
    }
  }
}
