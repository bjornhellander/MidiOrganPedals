/*
 * ****************************************************************************************************************
 * This sketch uses the MIDI Shield to try out MIDI commands for changing MIDI program on a device.
 * ****************************************************************************************************************
 */
 
static const bool Log = false;
static const bool SendMidi = true;

static const byte MidiCmdNoteOff = 0x80;
static const byte MidiCmdNoteOn = 0x90;
static const byte MidiCmdControlChange = 0xB0;
static const byte MidiCmdProgramChange = 0xC0;

static const byte SoundBankSelectionMsb = 0;
static const byte SoundBankSelectionLsb = 32;
static const byte SoundBankMsb = 0;
static const byte SoundBankLsb = 112;

static const byte Program1 = 18;
static const byte Program2 = 21;

static const byte MidiChannel = 0; // 0-15
static const byte MidiVelocity = 80; // 0-127
static const byte MidiNote = 50; // 0-127

static const byte PlayButtonPin = 2; // Left-most button seen from the MIDS jacks side
static const byte Program1ButtonPin = 3; // Center button seen from the MIDS jacks side
static const byte Program2ButtonPin = 4; // Right-most button seen from the MIDS jacks side
static const byte PlayLedPin = 6;
static const byte ProgramLedPin = 7;


/*-----------------------------------------------------------------------------------------*/


static struct {
  int change;
  bool playIsPressed;
  bool program1IsPressed;
  bool program2IsPressed;
} state = {
  0,
  false,
  false,
  false
};


/*-----------------------------------------------------------------------------------------*/


static void sendCommand(byte cmd, byte data1)
{
  Serial.write(cmd);
  Serial.write(data1);
}


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


static void programChange(byte channel, byte program)
{
  sendCommand(MidiCmdProgramChange | channel, program);
}


static void controlChange(byte channel, byte controller, byte value)
{
  sendCommand(MidiCmdControlChange | channel, controller, value);
}


/*-----------------------------------------------------------------------------------------*/


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

  pinMode(PlayButtonPin, INPUT_PULLUP);
  pinMode(Program1ButtonPin, INPUT_PULLUP);
  pinMode(Program2ButtonPin, INPUT_PULLUP);
  pinMode(PlayLedPin, OUTPUT);
  pinMode(ProgramLedPin, OUTPUT);

  digitalWrite(PlayLedPin, HIGH);
  digitalWrite(ProgramLedPin, HIGH);
}


/*-----------------------------------------------------------------------------------------*/


static void processPlayButton()
{
  bool isPressed = digitalRead(PlayButtonPin) == LOW ? true : false;

  if (isPressed != state.playIsPressed)
  {
    state.playIsPressed = isPressed;
    
    int ledState = isPressed ? LOW : HIGH;
    digitalWrite(PlayLedPin, ledState);

    if (Log)
    {
      state.change++;
      Serial.print(state.change);
      Serial.print(": Changed Play state to ");
      Serial.println(isPressed);
    }

    if (SendMidi)
    {
      if (isPressed)
      {
        noteOn(MidiChannel, MidiNote, MidiVelocity);
      }
      else
      {
        noteOff(MidiChannel, MidiNote, MidiVelocity);
      }
    }
  }
}


static void processProgram1Button()
{
  bool isPressed = digitalRead(Program1ButtonPin) == LOW ? true : false;

  if (isPressed != state.program1IsPressed)
  {
    state.program1IsPressed = isPressed;
    
    int ledState = (state.program1IsPressed || state.program2IsPressed) ? LOW : HIGH;
    digitalWrite(ProgramLedPin, ledState);
    
    if (Log)
    {
      state.change++;
      Serial.print(state.change);
      Serial.print(": Changed Program1 state to ");
      Serial.println(isPressed);
    }
    
    if (isPressed)
    {
      if (SendMidi)
      {
        //controlChange(MidiChannel, SoundBankSelectionMsb, SoundBankMsb);
        //controlChange(MidiChannel, SoundBankSelectionLsb, SoundBankLsb);
        programChange(MidiChannel, Program1);
      }
    }
  }
}


static void processProgram2Button()
{
  bool isPressed = digitalRead(Program2ButtonPin) == LOW ? true : false;

  if (isPressed != state.program2IsPressed)
  {
    state.program2IsPressed = isPressed;

    int ledState = (state.program1IsPressed || state.program2IsPressed) ? LOW : HIGH;
    digitalWrite(ProgramLedPin, ledState);
    
    if (Log)
    {
      state.change++;
      Serial.print(state.change);
      Serial.print(": Changed Program2 state to ");
      Serial.println(isPressed);
    }
    
    if (isPressed)
    {
      if (SendMidi)
      {
        //controlChange(MidiChannel, SoundBankSelectionMsb, SoundBankMsb);
        //controlChange(MidiChannel, SoundBankSelectionLsb, SoundBankLsb);
        programChange(MidiChannel, Program2);
      }
    }
  }
}


void loop()
{
  processPlayButton();
  processProgram1Button();
  processProgram2Button();
}

