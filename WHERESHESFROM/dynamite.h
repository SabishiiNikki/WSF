#define DYNA_RADIUS 20
void ControlDynamite() {
  // Smoking.
  if (varGameAnimClock % 6 == 0) NewSolarTrail((int16_t)varGameDyna.x / 10, (int16_t)varGameDyna.y / 10);

  // Moving.
  varGameDyna.speedY++;
  varGameDyna.x += varGameDyna.speedX;
  varGameDyna.y += varGameDyna.speedY;

  // Exploding.
  if (varGameDyna.y >= 520) {
    // Position.
    varGameDyna.y = 520;

    // Damaging the player.
    if (!varGamePlayer.solarForm && (abs((int16_t)varGamePlayer.x - (int16_t)varGameDyna.x) / 10) <= DYNA_RADIUS) {
      // Damage.
      varGameMinute += 90;
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
      varGamePlayer.animTime = Mean(30, 30);
      varGamePlayer.animIndex = 2;
      varGamePlayer.faceRight = (varGameDyna.x >= varGamePlayer.x);
      varGamePlayer.speedX = -FaceX(varGamePlayer.faceRight, 30);
    }

    // Damaging enemies.
    for(uint8_t i = 0; i < 4; i++) {
      if ((abs((int16_t)varGameEnemy[i].x - (int16_t)varGameDyna.x) / 10) <= DYNA_RADIUS) {
        DamageEnemy(i, 45);
        varGameEnemy[i].animFrame = 2;
        varGameEnemy[i].animIndex = 1;
        varGameEnemy[i].animTime = 60;
        varGameEnemy[i].faceRight = (varGameDyna.x >= varGameEnemy[i].x);
        varGameEnemy[i].speedX = -FaceX(varGameEnemy[i].faceRight, 30);
        varGameEnemy[i].able = false;
        varGameEnemy[i].block = false;
      }
    }

    // Explosion effect.
    for (uint8_t D = 0; D < 10; D++) {
      varTemp = (DYNA_RADIUS - 8) + (uint8_t)random(8);
      NewSolarTrail((int16_t)(varGameDyna.x / 10) + (int16_t)DirX((uint16_t)D * 36, varTemp), 48 + (int16_t)DirY((uint16_t)D * 36, varTemp));
    }

    // Byte.
    varGameDyna.inGame = false;

    // Sound.
    snd.tones(SndEnemyShoot);

    // End.
  }
}
