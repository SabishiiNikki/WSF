// Getting character ID.
byte GetChar(char fC) {
	if (fC >= 65 && fC <= 90) return(fC - 65);
	else if (fC >= 97 && fC <= 122) return(fC - 97);
	else if (fC >= 48 && fC <= 57) return(fC - 22);
	else if (fC == 46) return(36);
	else if (fC == 44) return(37);
	else if (fC == 39) return(38);
	else if (fC == 33) return(39);
	else if (fC == 63) return(40);
	else if (fC == 32 || fC == 95) return(41);
	else if (fC == 96) return(42);
	else if (fC == 132) return(43);
	else if (fC == 47) return(44);
  else if (fC == 58) return(45);
	else return(255);
}

// Getting string length.
/*byte GetLength(String fStr) {
	for(byte fi = 0; fi < 32; fi++) {
		if (fStr[(uint8_t)fi] == "\0") return(fi);
	}
	return(32);
}*/

// Getting minimum.
byte GetMin(byte fA, byte fB) {
  if (fA < fB) return(fA);
  else return(fB);
}

// Drawing text.
void DrawText(byte fX, byte fY, byte fStr, byte fLen) {
	for(byte fi = 0; fi < GetMin(strlen(strcpy_P(strBuf, (char*)pgm_read_word(&strDb[fStr]))), fLen); fi++) {
		spr.drawSelfMasked(fX + (fi * 4), fY, SprFont, (byte)GetChar(strcpy_P(strBuf, (char*)pgm_read_word(&strDb[fStr]))[(uint8_t)fi]));
	}
}

// Drawing centered text.
void DrawTextCenter(byte fX, byte fY, byte fStr, byte fLen) {
	DrawText(fX - (GetMin(strlen(strcpy_P(strBuf, (char*)pgm_read_word(&strDb[fStr]))), fLen) * 2), fY, fStr, fLen);
}

// Getting whether something is even or not.
bool Even(byte fX) {
	return(fX % 2 == 0);
}

// Turning LED off.
void LEDOff() {
	ardu.setRGBled(0, 0, 0);
}

// Setting LED.
void LEDOn(byte fCharge) {
	ardu.setRGBled((fCharge / 5), fCharge, fCharge);
}

// Getting string length.
byte GetStrLen(byte fStr) {
  return(strlen(strcpy_P(strBuf, (char*)pgm_read_word(&strDb[fStr]))));
}

// Clock even.
bool ClockEven() {
  return(varGameAnimClock % 2 == 0);
}

// A state where time shouldn't progress.
bool TimeStop() {
  return(varGameQuickdraw > 0 || varGameClashTime > 0);
}

// Directional X.
short signed DirX(short fDir, byte fLen) {
  return((int16_t)(cos((double)fDir * varDeg) * (double)fLen));
}

// Directional Y.
short signed DirY(short fDir, byte fLen) {
  return((int16_t)(-sin((double)fDir * varDeg) * (double)fLen));
}

// Face multiply.
short signed FaceX(bool fRight, short signed fX) {
  if (fRight) return((int16_t)fX);
  else return((int16_t)fX * (-1));
}

// Hitbox detection.
bool HitboxInRange(uint16_t fStart, uint16_t fEnd, uint16_t fLeft, uint16_t fRight) {
  // Positive.
  if (fStart < fEnd) return((fLeft >= fStart && fLeft <= fEnd) || (fRight >= fStart && fRight <= fEnd) || (fStart >= fLeft && fStart <= fRight) || (fEnd >= fLeft && fEnd <= fRight));

  // Negative.
  else return((fLeft <= fStart && fLeft >= fEnd) || (fRight <= fStart && fRight >= fEnd) || (fStart >= fLeft && fStart <= fRight) || (fEnd >= fLeft && fEnd <= fRight));
}

// Checks to see if the middle number really is the median.
bool CheckMedian(int16_t fA, int16_t fMid, int16_t fB) {
  return((fA <= fMid && fB >= fMid) || (fB <= fMid && fA >= fMid));
}

// Mean.
int16_t Mean(int16_t fA, int16_t fB) {
  return((fA + fB) / 2);
}

