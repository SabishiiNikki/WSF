void GameSetup() {
  // Level 1.
  if (varGameLevel == 0) {
    NewEnemy(0, 6000, WEAPON_KNUCK, WEAPON_KNUCK, 3, 60, 60, 180, true, 25, false, false, false);
  }

  // Level 2.
  else if (varGameLevel == 1) {
    NewEnemy(0, 6000, WEAPON_KNIFE, WEAPON_KNIFE, 4, 60, 60, 150, true, 50, false, false, false);
    NewEnemy(1, 4000, WEAPON_KNUCK, WEAPON_KNUCK, 3, 60, 60, 180, true, 25, false, false, false);
  }

  // Level 3.
  else if (varGameLevel == 2) {
    NewEnemy(0, 7000, WEAPON_KNIFE, WEAPON_KNIFE, 5, 45, 45, 150, true, 33, false, true, false);
    NewEnemy(1, 6000, WEAPON_KNUCK, WEAPON_KNUCK, 3, 60, 60, 180, true, 25, false, false, false);
    NewEnemy(2, 4000, WEAPON_KNUCK, WEAPON_KNUCK, 3, 60, 60, 180, true, 25, false, false, false);
    NewEnemy(3, 3000, WEAPON_KNUCK, WEAPON_KNUCK, 4, 60, 60, 180, true, 25, false, false, false);
  }

  // Level 4.
  else if (varGameLevel == 3) {
    NewEnemy(0, 6000, WEAPON_REVOL, WEAPON_KNUCK, 3, 45, 60, 150, true, 50, false, false, false);
    NewEnemy(1, 4000, WEAPON_KNIFE, WEAPON_KNIFE, 6, 45, 45, 150, true, 33, false, true, false);
  }
  
  // Level 5.
  else if (varGameLevel == 4) {
    NewEnemy(0, 6000, WEAPON_REVOL, WEAPON_KNUCK, 5, 30, 45, 120, false, 125, false, true, true);
  }

  // Level 6.
  else if (varGameLevel == 5) {
    NewEnemy(0, 6000, WEAPON_REVOL, WEAPON_KNIFE, 7, 30, 45, 150, true, 75, false, false, false);
    NewEnemy(1, 4000, WEAPON_REVOL, WEAPON_KNUCK, 3, 45, 60, 120, false, 75, false, true, false);
  }

  // Level 7.
  else if (varGameLevel == 6) {
    NewEnemy(0, 6000, WEAPON_REVOL, WEAPON_KNIFE, 5, 30, 45, 120, true, 75, false, true, false);
    NewEnemy(1, 3000, WEAPON_REVOL, WEAPON_KNIFE, 5, 30, 45, 120, true, 75, false, true, false);
  }

  // Level 8.
  else if (varGameLevel == 7) {
    NewEnemy(0, 6000, WEAPON_KNIFE, WEAPON_KNIFE, 10, 30, 30, 90, false, 100, false, true, false);
    NewEnemy(1, 3000, WEAPON_KNIFE, WEAPON_KNIFE, 10, 30, 30, 90, false, 100, false, true, false);
  }

  // Level 9.
  else if (varGameLevel == 8) {
    NewEnemy(0, 6000, WEAPON_KNUCK, WEAPON_KNUCK, 15, 15, 15, 90, false, 100, false, true, false);
    NewEnemy(1, 3000, WEAPON_REVOL, WEAPON_KNIFE, 7, 30, 45, 120, false, 50, false, false, false);
  }

  // Level 10.
  else if (varGameLevel == 9) {
    NewEnemy(0, 3000, WEAPON_SHOTG, WEAPON_KNIFE, 8, 20, 40, 90, false, 250, false, true, true);
  }

  // Level 11.
  else if (varGameLevel == 10) {
    NewEnemy(0, 5500, WEAPON_REVOL, WEAPON_KNIFE, 5, 15, 30, 90, false, 75, false, true, false);
    NewEnemy(1, 3500, WEAPON_REVOL, WEAPON_KNIFE, 5, 15, 30, 90, false, 75, false, true, false);
  }

  // Level 12.
  else if (varGameLevel == 11) {
    NewEnemy(0, 5500, WEAPON_SHOTG, WEAPON_KNUCK, 3, 15, 30, 90, false, 100, false, true, false);
    NewEnemy(1, 3500, WEAPON_SHOTG, WEAPON_KNUCK, 3, 15, 30, 90, false, 100, false, true, false);
  }

  // Level 13.
  else if (varGameLevel == 12) {
    NewEnemy(0, 6000, WEAPON_SHOTG, WEAPON_KNIFE, 15, 15, 30, 90, false, 125, false, true, false);
  }

  // Level 14.
  else if (varGameLevel == 13) {
    NewEnemy(0, 7000, WEAPON_KNIFE, WEAPON_KNIFE, 7, 15, 15, 90, false, 75, false, true, false);
    NewEnemy(1, 6000, WEAPON_KNIFE, WEAPON_KNIFE, 7, 15, 15, 90, false, 75, false, true, false);
    NewEnemy(2, 4000, WEAPON_KNIFE, WEAPON_KNIFE, 7, 15, 15, 90, false, 75, false, true, false);
    NewEnemy(3, 3000, WEAPON_KNIFE, WEAPON_KNIFE, 7, 15, 15, 90, false, 75, false, true, false);
  }

  // Level 15.
  else if (varGameLevel == 14) {
    NewEnemy(0, 6000, WEAPON_JGATL, WEAPON_JFIST, 5, 15, 30, 75, false, 500, true, true, true);
  }
}
