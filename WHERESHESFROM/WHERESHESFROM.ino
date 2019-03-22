/* 
 * Where She's From
 * Version 1.0
 * developed by "SabishiiNikki"
 * 2019
 * In the event you actually go through this code, please forgive my poor organization. It's my first Arduboy game, and C isn't exactly the cleanest language to deal with.
 */

// Imports.
#include "str.h"
#include "gvar.h"
#include "spr.h"
#include "snd.h"
#include "func.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "dynamite.h"
#include "setup.h"
#include "draw.h"
#include "run.h"

// Setup.
void setup() {
  ardu.begin();
  ardu.setFrameRate(60);
  ardu.audio.on();
  ardu.audio.off();
  ardu.initRandomSeed();
}

// Loop.
void loop() {
  if (ardu.nextFrame()) {
    ardu.pollButtons();
    Run();
    Draw();
  }
}
