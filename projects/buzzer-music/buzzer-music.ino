// https://www.arduino.cc/en/tutorial/melody
// https://roboticsbackend.com/arduino-object-oriented-programming-oop/

#include "./melody.h"
#include "./notes.h"

int speakerPin = 13;

// Register melodies
int ttlsNotes[] = { NOTE_C6, NOTE_C6, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_A6, NOTE_G6, 
                    NOTE_F6, NOTE_F6, NOTE_E6, NOTE_E6, NOTE_D6, NOTE_D6, NOTE_C6, 0 }; // Zero ( 0 ) represents a rest
int ttlsBeats[] = { 1, 1, 1, 1, 1, 1, 2, 
                    1, 1, 1, 1, 1, 1, 2, 4 };
int ttlsTempo = 300;
Melody ttls = Melody("Twinkle Twinkle Little Star", 15,  ttlsNotes, ttlsBeats, ttlsTempo);

int hbtyNotes[] = { NOTE_C6, NOTE_C6, NOTE_D6, NOTE_C6, NOTE_F6, NOTE_E6,
                    NOTE_C6, NOTE_C6, NOTE_D6, NOTE_C6, NOTE_G6, NOTE_E6, // E7?
                    NOTE_C6, NOTE_C6, NOTE_C7, NOTE_A6, NOTE_F6, NOTE_E6, NOTE_D6,
                    NOTE_AS6, NOTE_AS6, NOTE_A6, NOTE_F6, NOTE_G6, NOTE_F6, 0 };
//char hbtyNotes[] = "ddedgf ddedag ddDbgfe CCbgag ";
int hbtyBeats[] = { 1, 1, 1, 1, 1, 2,
                    1, 1, 1, 1, 1, 2,
                    1, 1, 1, 1, 1, 1, 2, 
                    1, 1, 1, 1, 1, 2, 4 };
int hbtyTempo = 300;
Melody hbty = Melody("Happy Birthday To You", 26, hbtyNotes, hbtyBeats, hbtyTempo);


void setup() 
{
  Serial.begin(9600);
  
  pinMode(speakerPin, OUTPUT);
}

void loop() 
{
  play(ttls);
  play(hbty);
}

void play(Melody m)
{
  String mName = m.getMelodyName();
  int mLength = m.getMelodyLength();
  int* notes = m.getNotes();
  int* beats = m.getBeats();
  int tempo = m.getTempo();
  
  Serial.print("Now playing: ");
  Serial.println(mName);

  for (int i = 0; i < mLength; i++) 
  {
    // Rest/Pause
    if (notes[i] == 0) 
    {
      delay(beats[i] * tempo);
      continue;
    }

    // Play tone, wait, stop tone
    tone(speakerPin, notes[i], 1000 / beats[i]);
    delay(beats[i] * tempo);
    noTone(speakerPin);

    // pause between notes
    delay(tempo / 2); 
  }
} 

void playTone(int tone, int duration) 
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
