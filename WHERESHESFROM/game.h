// Declarations.
#define PLAYER_SPEED  12
#define WEAPON_KNUCK  0
#define WEAPON_KNIFE  2
#define WEAPON_REVOL  4
#define WEAPON_SHOTG  5
#define WEAPON_SNIPE  6
#define WEAPON_JFIST  7
#define WEAPON_JGATL  9

// Heatstroke.
struct Player {
  public:
    short x;
    short signed y;
    short signed speedX;
    short signed speedY;
    byte animIndex;
    byte animFrame;
    byte animTime;
    bool able;
    bool solarForm;
    bool faceRight;
    bool control;
    bool attackHit;
    byte hitFreeze;
    byte dodgeExhaust;
    bool attackBack;
    byte clashCooldown;
};

// Heatstroke trails.
struct Trail {
  public:
    bool inGame;
    short signed x;
    short signed y;
    byte animFrame;
};

// Enemies.
struct Enemy {
  public:
    bool inGame;
    short x;
    short signed speedX;
    byte animIndex;
    byte animFrame;
    byte animTime;
    byte animWeapon;
    bool able;
    bool faceRight;
    byte weaponPrimary;
    byte weaponMelee; // If they don't use a knife then they use brass knuckles.
    byte deathTimer;
    byte speedRun;
    byte speedAttack; // Melee attack.
    byte speedShoot;
    byte speedClash; // Actually the clash timer length, so the higher it is the longer it waits for the player's input.
    bool weak; // If true, the enemy will be put into hitstun by any attack.
    byte hitFreeze;
    bool ironGatlingJack;
    short hp;
    byte attackCooldown;
    bool block;
    bool restoreBlock;
    byte reblock;
    bool dynamite;
    bool bomber;
    short maxHp;
    //byte helpCall;
};

// Dynamite.
struct Dynamite {
  public:
    bool inGame;
    short x;
    short y;
    short signed speedX;
    short signed speedY;
};

// Initializing object arrays.
Player varGamePlayer;
Enemy varGameEnemy[4];
Trail varGameTrail[MAX_EMBERS];
Dynamite varGameDyna;
byte varGameTrailIndex = 0;

// Adding a new enemy.
void NewEnemy(uint8_t fInd, short fX, byte fGun, byte fKnife, byte fSRun, byte fSAttack, byte fSShoot, byte fSClash, bool fWeak, short fHp, bool fJack, bool fBlock, bool fDynamite) {
  varGameEnemy[fInd].inGame = true;
  varGameEnemy[fInd].x = fX;
  varGameEnemy[fInd].speedX = 0;
  varGameEnemy[fInd].animIndex = 0;
  varGameEnemy[fInd].animFrame = 0;
  varGameEnemy[fInd].animTime = 0;
  varGameEnemy[fInd].animWeapon = 0;
  varGameEnemy[fInd].able = true;
  varGameEnemy[fInd].faceRight = (fX < 5000);
  varGameEnemy[fInd].weaponPrimary = fGun;
  varGameEnemy[fInd].weaponMelee = fKnife;
  varGameEnemy[fInd].deathTimer = 0;
  varGameEnemy[fInd].speedRun = fSRun;
  varGameEnemy[fInd].speedAttack = fSAttack;
  varGameEnemy[fInd].speedShoot = fSShoot;
  varGameEnemy[fInd].speedClash = fSClash;
  varGameEnemy[fInd].weak = fWeak;
  varGameEnemy[fInd].ironGatlingJack = fJack;
  varGameEnemy[fInd].hp = fHp;
  varGameEnemy[fInd].attackCooldown = 60;
  varGameEnemy[fInd].block = fBlock;
  varGameEnemy[fInd].restoreBlock = fBlock;
  varGameEnemy[fInd].reblock = 150;
  varGameEnemy[fInd].dynamite = fDynamite;
  varGameEnemy[fInd].bomber = false;
  varGameEnemy[fInd].maxHp = fHp;
}

// Reset.
void GameReset() {
  // Camera.
  varGameCamera = 0;
  
  // Resetting Heatstroke.
  varGamePlayer.x = 5000;
  varGamePlayer.y = 0;
  varGamePlayer.speedX = 0;
  varGamePlayer.speedY = 0;
  varGamePlayer.animIndex = 0;
  varGamePlayer.animFrame = 0;
  varGamePlayer.animTime = 0;
  varGamePlayer.able = true;
  varGamePlayer.solarForm = false;
  varGamePlayer.faceRight = true;
  varGamePlayer.control = true;
  varGamePlayer.attackHit = false;
  varGamePlayer.hitFreeze = 0;
  varGamePlayer.dodgeExhaust = 0;
  varGamePlayer.attackBack = true;
  varGamePlayer.clashCooldown = 0;

  // Shutting off trails.
  for(uint8_t i = 0; i < MAX_EMBERS; i++) {
    varGameTrail[i].inGame = false;
  }

  // Shutting off enemies.
  for(uint8_t i = 0; i < 4; i++) {
    varGameEnemy[i].inGame = false;
  }

  // Shutting off dynamite.
  varGameDyna.inGame = false;

  // Time.
  varGameHour = 0;
  varGameMinute = 0;
  varGameSecond = 60;

  // Next timer.
  varGameNext = 150;
}



//////////////////////////
/////// POST SETUP ///////
//////////////////////////



///////////////////////
// GENERAL FUNCTIONS //
///////////////////////
// Slow to stop.
short signed SlowToStop(short signed fS) {
  if (fS > 0) return(fS - 1);
  else if (fS < 0) return(fS + 1);
  else return(fS);
}

// Create new solar trail.
void NewSolarTrail(short signed fX, short signed fY) {
  varGameTrail[(uint8_t)varGameTrailIndex].inGame = true;
  varGameTrail[(uint8_t)varGameTrailIndex].x = fX;
  varGameTrail[(uint8_t)varGameTrailIndex].y = fY;
  varGameTrail[(uint8_t)varGameTrailIndex].animFrame = 0;
  if (varGameTrailIndex < MAX_EMBERS - 1) varGameTrailIndex++;
  else varGameTrailIndex = 0;
}

// Makes way towards a speed.
short signed MoveToSpeed(short signed fS, short signed fMax) {
  if (fS > fMax) return(fS - 1);
  else if (fS < fMax) return(fS + 1);
  else return(fS);
}

// If all enemies have been killed.
bool StageClear() {
  varTemp = 0;
  for(uint8_t i = 0; i < 4; i++) {
    if (varGameEnemy[i].inGame && varGameEnemy[i].hp > 0) {
      varTemp++;
    }
  }
  return(varTemp == 0);
}

// Clash handling.
void ClashHandle() {
  // Inputs.
  if ((ardu.justPressed(UP_BUTTON) && varGameClashDir == 0) || (ardu.justPressed(RIGHT_BUTTON) && varGameClashDir == 1) || (ardu.justPressed(DOWN_BUTTON) && varGameClashDir == 2) || (ardu.justPressed(LEFT_BUTTON) && varGameClashDir == 3)) varGameClashDir++;

  // Won clash.
  if (varGameClashDir == 4) {
    varGamePlayer.attackHit = false;
    varGamePlayer.able = false;
    varGamePlayer.animTime = 0;
    varGamePlayer.animIndex = 4;
    varGamePlayer.solarForm = true;
    varGameEnemy[(uint8_t)varGameClashEnemy].animFrame = 2;
    varGameEnemy[(uint8_t)varGameClashEnemy].animIndex = 1;
    varGameEnemy[(uint8_t)varGameClashEnemy].animTime = 60;
    varGameEnemy[(uint8_t)varGameClashEnemy].able = false;
    varGameEnemy[(uint8_t)varGameClashEnemy].attackCooldown = 0;
    varGameEnemy[(uint8_t)varGameClashEnemy].reblock = 0;
    varGamePlayer.clashCooldown = 150;
    varGameClashTime = 0;
  }

  // Losing clash.
  else if (varGameClashTime > 1) varGameClashTime--;
  else {
    varGameEnemy[varTemp].animTime = 0;
    varGamePlayer.animIndex = 2;
    varGamePlayer.animTime = 60;
    varGamePlayer.able = false;
    varGamePlayer.clashCooldown = 150;
    varGameClashTime = 0;
  }

  // End.
}


//////////////////
// GAME CONTROL //
//////////////////
void GameDraw() {
  // Setting camera.
  varGameCamera = (varGamePlayer.x / 10) - 64;

  // The environment blinks during Quickdraw.
  if (varGameQuickdraw == 0 /*|| varGameAnimClock % 4 > 1*/) {
    // Ground.
    for(int8_t i = -1; i < 17; i++) {
      spr.drawSelfMasked((i * 8) - ((int16_t)varGameCamera % 8), 56, SprGround, 0);
    }
  
    // Barrels.
    spr.drawSelfMasked(250 - (int16_t)varGameCamera - 26, 40, SprBarrel, 0);
    spr.drawSelfMasked(750 - (int16_t)varGameCamera + 10, 40, SprBarrel, 0);
  
    // Clouds.
    for(int8_t i = -1; i < 9; i++) {
      varTempShort = ((((int16_t)varGameMinute * 100) / 60) * 48) / 100;
      spr.drawSelfMasked((i * 24) - ((int16_t)varGameCamera % 48) - (uint16_t)varTempShort, 8 * (i % 2), SprCloud, 0);
    }
  }

  // The sun during Quickdraw.
  if (varGameQuickdraw > 0 && Even(varGameQuickdraw)) spr.drawPlusMask(0, 0, SprSun, 0);

  // Trails.
  for(uint8_t i = 0; i < MAX_EMBERS; i++) {
    if (varGameTrail[i].inGame) {
      spr.drawPlusMask((int16_t)varGameTrail[i].x - (int16_t)varGameCamera - 4, (int16_t)varGameTrail[i].y - 4, SprSolarEmber, (uint8_t)varGameTrail[i].animFrame);
      if (varGameAnimClock % 3 == 0) {
        if (varGameTrail[i].animFrame < 3) varGameTrail[i].animFrame++;
        else varGameTrail[i].inGame = false;
      }
    }
  }

  // Enemies.
  for(uint8_t i = 0; i < 4; i++) {
    if (varGameEnemy[i].inGame && (varGameEnemy[i].hp > 0 || ClockEven()) && !(!varGameEnemy[i].able && (varGameEnemy[i].animIndex == 2 || varGameEnemy[i].animIndex == 3) && ClockEven() && !TimeStop())) {
      // Regular.
      if (!varGameEnemy[i].ironGatlingJack) {
        // Right.
        if (varGameEnemy[i].faceRight) {
          spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera - 9, 32, SprEnemyR, (uint8_t)varGameEnemy[i].animFrame);
          if (varGameEnemy[i].animFrame < 2) spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera + 4, 40, SprWeaponR, (uint8_t)varGameEnemy[i].animWeapon);
        }

        // Left.
        else {
          spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera - 9, 32, SprEnemyL, (uint8_t)varGameEnemy[i].animFrame);
          if (varGameEnemy[i].animFrame < 2) spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera - 25, 40, SprWeaponL, (uint8_t)varGameEnemy[i].animWeapon);
        }
      }

      // Iron Gatling Jack.
      else {
        // Right.
        if (varGameEnemy[i].faceRight) {
          spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera - 12, 24, SprJackR, (uint8_t)varGameEnemy[i].animFrame);
          if (varGameEnemy[i].animFrame < 2) spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera + 8, 40, SprWeaponR, (uint8_t)varGameEnemy[i].animWeapon);
        }

        // Left.
        else {
          spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera - 12, 24, SprJackL, (uint8_t)varGameEnemy[i].animFrame);
          if (varGameEnemy[i].animFrame < 2) spr.drawPlusMask(((int16_t)varGameEnemy[i].x / 10) - (int16_t)varGameCamera - 30, 40, SprWeaponL, (uint8_t)varGameEnemy[i].animWeapon);
        }
      }
    }
  }

  // Heatstroke.
  if (varGameHour < 7 || ClockEven()) {
    if (varGamePlayer.solarForm) {
      if (ClockEven()) spr.drawPlusMask(57, 37, SprSolarFlare, 0);
    }
    else {
      if (varGamePlayer.faceRight) spr.drawPlusMask(54, 32 + ((int8_t)varGamePlayer.y / 10), SprPlayerR, (uint8_t)varGamePlayer.animFrame);
      else spr.drawPlusMask(54, 32 + ((int8_t)varGamePlayer.y / 10), SprPlayerL, (uint8_t)varGamePlayer.animFrame);
    }
  }

  // Dynamite.
  if (varGameDyna.inGame) {
    spr.drawPlusMask(((int16_t)varGameDyna.x / 10) - (int16_t)varGameCamera - 4, (int16_t)varGameDyna.y / 10, SprDynamite, (uint8_t)((varGameAnimClock - 1) / 15));
  }

  // Time counting.
  if (!TimeStop() && !StageClear()) {
    if (varGameSecond > 1) varGameSecond--;
    else if (varGameHour < 7) {
      varGameSecond = 60;
      if (varGameMinute < 59) varGameMinute++;
      else {
        varGameHour++;
        varGameMinute = 0;
      }
    }
  }

  // Time.
  if (!TimeStop() && varGameClashTime == 0) {
    // Setting time string.
    if (varGameHour == 0) {
      varTimeDisplay[0] = '1';
      varTimeDisplay[1] = '2';
    }
    else {
      varTimeDisplay[0] = ' ';
      varTimeDisplay[1] = (char)(48 + varGameHour);
    }
    if (varGameMinute < 10) {
      varTimeDisplay[3] = '0';
      varTimeDisplay[4] = (char)(48 + varGameMinute);
    }
    else {
      varTimeDisplay[3] = (char)(48 + (varGameMinute / 10));
      varTimeDisplay[4] = (char)(48 + (varGameMinute - ((varGameMinute / 10) * 10)));
    }

    // Drawing time.
    ardu.fillRect(0, 0, 34, 8, BLACK);
    if ((ClockEven() || varGameHour != 6)) {
      for(byte fi = 0; fi < strlen(varTimeDisplay); fi++) {
        spr.drawSelfMasked(1 + (fi * 4), 0, SprFont, (byte)GetChar(varTimeDisplay[(uint8_t)fi]));
      }
    }
  }

  // Clash.
  if (varGameClashTime > 0) {
    spr.drawPlusMask(52, 20, SprClash, (uint8_t)varGameClashDir);
    ClashHandle();
  }

  // Clash cooldown.
  if (varGamePlayer.clashCooldown > 0 && (varGamePlayer.clashCooldown > 30 || ClockEven())) {
    ardu.fillRect(120, 0, 8, 9, BLACK);
    spr.drawSelfMasked(121, 0, SprClashCooldown, 0);
  }

  // Boss health.
  if ((varGameLevel + 1) % 5 == 0) {
    ardu.fillRect(40, 0, 64, 9, BLACK);
    ardu.fillRect(51, 0, 52, 6, WHITE);
    ardu.fillRect(52, 1, 50, 4, BLACK);
    if (varGameEnemy[0].hp > 0) ardu.fillRect(53, 2, max((uint16_t)(((float)varGameEnemy[0].hp / (float)varGameEnemy[0].maxHp) * 48), 1), 2, WHITE);
    spr.drawSelfMasked(41, 0, SprSkull, 0);
  }

  // Quickdraw.
  if (varGameQuickdraw > 0) varGameQuickdraw--;

  // Game ended.
  if (StageClear() || varGameHour == 7) {
    varGameQuickdraw = 0;
    if (varGameNext > 0) varGameNext--;
    else {
      if (varGameHour == 7) {
        gameState = STATE_LOSE;
        varTransition = 30;
        varLoseSelect = true;
      }
      else if (varGameLevel < 14) {
        gameState = STATE_STORY;
        varTextLen = 0;
        varTextLine = 0;
        varTransition = 30;
        varGameLevel++;
        GameReset();
      }
      else {
        gameState = STATE_END;
        varTransition = 30;
      }
      // End.
    }
  }
}
