
#include "./melody.h"
#include "./notes.h"

// Melodies
//#include "./songs.h"

const int speakerPin = 13;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(speakerPin, OUTPUT);
  
  tone(speakerPin, 650, 1000);
  delay(500);
  noTone(speakerPin);
}

void serialEvent() 
{
  char t = (char)Serial.read();
  Serial.print(t);
  Serial.print((int)t);
  tone(speakerPin, t*10, 1000);
  delay(500);
  noTone(speakerPin);
}

void loop() 
{
  // play(ttls);
  // delay(1000);
  // play(hbty);
  // delay(1000);
  // play(jvedt);
  // delay(1000);
  // play(tom);
  // delay(1000);
  // play(as);
  // delay(1000);
}

void play(Melody m)
{
  String mName = m.getMelodyName();
  int mLength = m.getMelodyLength();
  int* notes = m.getNotes();
  int* beats = m.getBeats();
  int tempo = m.getTempo();
  
  Serial.print("\nNow playing: ");
  Serial.println(mName);
  Serial.print("Length: ");
  Serial.println(mLength);
  Serial.print("Tempo: ");
  Serial.println(tempo);

  for (int i = 0; i < mLength; i++) 
  {
    // Rest/Pause
    if (notes[i] == 0) 
    {
      delay(beats[i] * tempo);
      continue;
    }

    // Play tone, wait, stop tone
    tone(speakerPin, notes[i], beats[i] * tempo);
    delay(beats[i] * tempo);
    noTone(speakerPin);

    // pause between notes
    delay(tempo / 2); 
  }
}
