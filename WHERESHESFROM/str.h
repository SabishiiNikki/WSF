// Strings.
PROGMEM const char strTempLoad00[] = "WHERE SHE'S FROM";
PROGMEM const char strTempLoad01[] = "A: Start Game";
PROGMEM const char strTempLoad02[] = "B: Sound";
PROGMEM const char strTempLoad03[] = "Off";
PROGMEM const char strTempLoad04[] = "Normal";
PROGMEM const char strTempLoad05[] = "High";
PROGMEM const char strTempLoad06[] = "For help and credits, go to:";
PROGMEM const char strTempLoad07[] = "sabishiinikki.github.io/WSF";
PROGMEM const char strTempLoad08[] = "Retry Mission";
PROGMEM const char strTempLoad09[] = "Return to Title Screen";
PROGMEM const char strTempLoad10[] = "June 21, 1877";
PROGMEM const char strTempLoad11[] = "June 23, 1877";
PROGMEM const char strTempLoad12[] = "June 29, 1877";
PROGMEM const char strTempLoad13[] = "July 1, 1877";
PROGMEM const char strTempLoad14[] = "July 5, 1877";
PROGMEM const char strTempLoad15[] = "July 9, 1877";
PROGMEM const char strTempLoad16[] = "July 11, 1877";
PROGMEM const char strTempLoad17[] = "July 14, 1877";
PROGMEM const char strTempLoad18[] = "July 17, 1877";
PROGMEM const char strTempLoad19[] = "July 18, 1877";
PROGMEM const char strTempLoad20[] = "July 23, 1877";
PROGMEM const char strTempLoad21[] = "July 24, 1877";
PROGMEM const char strTempLoad22[] = "July 29, 1877";
PROGMEM const char strTempLoad23[] = "August 3, 1877";
PROGMEM const char strTempLoad24[] = "August 13, 1877";
PROGMEM const char strTempLoad25[] = "It's mighty risky out here.";
PROGMEM const char strTempLoad26[] = "These folks ought to learn.";
PROGMEM const char strTempLoad27[] = "Yeah, strength in numbers...";
PROGMEM const char strTempLoad28[] = "But an army don't always cut it.";
PROGMEM const char strTempLoad29[] = "All it takes is one strange gal.";
PROGMEM const char strTempLoad30[] = "Word starts gettin' around.";
PROGMEM const char strTempLoad31[] = "Lawmen, outlaws, common folk...";
PROGMEM const char strTempLoad32[] = "All of them put up their guard.";
PROGMEM const char strTempLoad33[] = "She's a quiet, ruthless killer.";
PROGMEM const char strTempLoad34[] = "They call her `Heatstroke` now.";
PROGMEM const char strTempLoad35[] = "A habit of showing at high noon.";
PROGMEM const char strTempLoad36[] = "Under the blisterin' summer sun.";
PROGMEM const char strTempLoad37[] = "All's what got her that name.";
PROGMEM const char strTempLoad38[] = "She's like an omen, that woman.";
PROGMEM const char strTempLoad39[] = "`Iron Gatling Jack` is as well.";
PROGMEM const char strTempLoad40[] = "I guess no one quite realizes";
PROGMEM const char strTempLoad41[] = "she ain't no normal lady.";
PROGMEM const char strTempLoad42[] = "You'd think it'd be obvious,";
PROGMEM const char strTempLoad43[] = "what with her habits and all...";
PROGMEM const char strTempLoad44[] = "That woman is Sunborn.";
PROGMEM const char strTempLoad45[] = "Thanks for playing.";
PROGMEM const char strTempLoad46[] = "`SabishiiNikki`";

// Pointer database.
PROGMEM char* const strDb[] = {strTempLoad00, strTempLoad01, strTempLoad02, strTempLoad03, strTempLoad04, strTempLoad05, strTempLoad06, strTempLoad07, strTempLoad08, strTempLoad09, strTempLoad10, strTempLoad11, strTempLoad12, strTempLoad13, strTempLoad14, strTempLoad15, strTempLoad16, strTempLoad17, strTempLoad18, strTempLoad19, strTempLoad20, strTempLoad21, strTempLoad22, strTempLoad23, strTempLoad24, strTempLoad25, strTempLoad26, strTempLoad27, strTempLoad28, strTempLoad29, strTempLoad30, strTempLoad31, strTempLoad32, strTempLoad33, strTempLoad34, strTempLoad35, strTempLoad36, strTempLoad37, strTempLoad38, strTempLoad39, strTempLoad40, strTempLoad41, strTempLoad42, strTempLoad43, strTempLoad44, strTempLoad45, strTempLoad46};

// Separation definitions.
#define STR_TITLE	0
#define STR_MAIN	1
#define STR_SOUND 3
#define STR_HELP  6
#define STR_DATE  10
#define STR_INFO  25
#define STR_END   40
#define STR_THANK 45

// Buffer.
byte strMaxLen = 50;
char strBuf[50];
