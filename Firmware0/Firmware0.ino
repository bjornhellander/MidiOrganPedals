static const bool Log = false;
static const bool SendMidi = true;

static const byte MidiChannel = 0; // 0-15
static const byte MidiVelocity = 80; // 0-127
static const byte MidiCmdNoteOff = 0x80;
static const byte MidiCmdNoteOn = 0x90;
static const byte MidiLowestNote = 29; // A in some octave

static const byte LedPin = 13;


/*-----------------------------------------------------------------------------------------*/


static struct {
  int8_t InputPin;
  bool IsEnabled;
  bool IsPressed;
} pedals[] = {
  { 12, true },
  { 10, true },
  { 11, true },
  {  9, true },
  {  8, true },

  {  3, true },
  {  6, true },
  {  4, true },
  {  5, true },
  {  2, true },
  { A5, true },

  { A0, true },
  { A1, true },
  { A2, true },
  { A3, true },
  { A4, true },
  {  7, true },
  
  { -1 }
};

static bool ledOn;

static int change = 0;


/*-----------------------------------------------------------------------------------------*/


static void initPedalPin(byte i)
{
  int8_t pedalPin = pedals[i].InputPin;
  pinMode(pedalPin, INPUT_PULLUP);
  pedals[i].IsPressed = false;
}


static void initLed()
{
  pinMode(LedPin, OUTPUT);
  ledOn = true;
}


void setup()
{
  if (Log)
  {
    Serial.begin(9600);
    Serial.println("Starting...");
  }
  
  if (SendMidi)
  {
    Serial.begin(31250);
  }

  for (byte i = 0; pedals[i].InputPin >= 0; i++) {
    initPedalPin(i);
  }
  
  initLed();
}


/*-----------------------------------------------------------------------------------------*/


static void sendCommand(byte cmd, byte data1, byte data2)
{
  Serial.write(cmd);
  Serial.write(data1);
  Serial.write(data2);
}


static void noteOn(byte channel, byte note, byte velocity)
{
  sendCommand(MidiCmdNoteOn | channel, note, velocity);
}


static void noteOff(byte channel, byte note, byte velocity)
{
  sendCommand(MidiCmdNoteOff | channel, note, velocity);
}


static void processPedal(byte i)
{
  if (!pedals[i].IsEnabled) {
    return;
  }
  
  int8_t pedalPin = pedals[i].InputPin;
  bool isPressed = digitalRead(pedalPin) == HIGH ? true : false;

  if (isPressed != pedals[i].IsPressed)
  {
    pedals[i].IsPressed = isPressed;
    byte note = MidiLowestNote + i;
    
    if (Log)
    {
      change++;
      Serial.print(change);
      Serial.print(": Changed state of pin ");
      Serial.print(pedalPin);
      Serial.print(" to ");
      Serial.println(isPressed);
    }
    
    if (Log)
    {
      Serial.print("Corresponds to note ");
      Serial.println(note);
    }
    
    if (SendMidi)
    {
      if (isPressed)
      {
        noteOn(MidiChannel, note, MidiVelocity);
      }
      else
      {
        noteOff(MidiChannel, note, MidiVelocity);
      }
    }
    
    ledOn = !ledOn;
    int ledState = ledOn ? LOW : HIGH;
    if (Log)
    {
      Serial.print("Setting LED to  ");
      Serial.print(ledState);
      Serial.println();
    }
    digitalWrite(LedPin, ledState);
  }
}


void loop()
{
  for (byte i = 0; pedals[i].InputPin >= 0; i++) {
    processPedal(i);
  }
}

