// https://www.arduino.cc/en/tutorial/melody
// https://roboticsbackend.com/arduino-object-oriented-programming-oop/

#include "./melody.h"

int speakerPin = 13;

// Register melodies
char ttlsNotes[] = "ccggaagffeeddc "; // a space represents a rest
int ttlsBeats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int ttlsTempo = 300;
Melody ttls = Melody("Twinkle Twinkle Little Star", ttlsNotes, ttlsBeats, ttlsTempo);

char hbtyNotes[] = "ddedgf ddedag ddDbgfe CCbgag ";
int hbtyBeats[] = { 1, 1, 1, 1, 1, 2, 1, 
                  1, 1, 1, 1, 1, 2, 1, 
                  1, 1, 1, 1, 1, 1, 1, 1, 
                  1, 1, 1, 1, 1, 2, 4 };
int hbtyTempo = 300;
Melody hbty = Melody("Happy Birthday To You", hbtyNotes, hbtyBeats, hbtyTempo);

void setup() 
{
  Serial.begin(9600);
  
  pinMode(speakerPin, OUTPUT);
}

void loop() 
{
  //play(ttls);
  play(hbty);
}

void play(Melody m)
{
  String mName = m.getMelodyName();
  int mLength = m.getMelodyLength();
  char* notes = m.getNotes();
  int* beats = m.getBeats();
  int tempo = m.getTempo();

  Serial.print("Now playing: ");
  Serial.println(mName);
  
  for (int i = 0; i < mLength; i++) 
  {
    if (notes[i] == ' ') 
      delay(beats[i] * tempo); // rest
    else
      playNote(notes[i], beats[i] * tempo);

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

void playNote(char note, int duration) 
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 900 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) 
  {
    if (names[i] == note) 
    {
      playTone(tones[i], duration);
    }
  }
}
