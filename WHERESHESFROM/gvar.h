// Definition.
#ifndef GVAR_H
#define GVAR_H

// Imports.
#include <Arduino.h>
#include <Arduboy2.h>
#include <ArduboyTones.h>

// Control objects.
Arduboy2Base ardu;
Sprites spr;
ArduboyTones snd(ardu.audio.enabled);

// Game state.
#define STATE_LOGO	0
#define STATE_TITLE	1
#define STATE_HELP  2
#define STATE_STORY 3
#define STATE_GAME  4
#define STATE_END   5
#define STATE_LOSE  6
#define STATE_THANK 7
#define STATE_TEST 100
byte gameState = STATE_TITLE;

// Thing.
#define MAX_EMBERS  20

// Misc. variables.
byte varTemp = 0;
short signed varTempShort = 0;
byte varGameAnimClock = 0;
byte varGameAnimClockSpec = 0;
byte varWaitTimer = 0;
byte varTransition = 0;
byte varTextLen = 0;
byte varTextLine = 0;
double varDeg = PI / 180;
bool varLoseSelect = true;

// Option variables.
byte varOptionVolume = 0;

// Game variables.
byte varGameLevel = 0;
byte varGameHour = 0;
byte varGameMinute = 0;
byte varGameSecond = 0;
byte varGameEnd = 0;
byte varGameEnemies = 0; // Just stored so we don't have to loop through the enemy array separately.
byte varGameQuickdraw = 0;
byte varGameClashTime = 0;
byte varGameClashEnemy = 0;
byte varGameClashDir = 0;
short signed varGameCamera = 0;
char varTimeDisplay[] = "12:00 PM";
byte varGameNext = 150;

// End.
#endif
