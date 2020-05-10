
#include "./melody.h"
#include "./notes.h"

// Melodies
#include "melodies/example.h"
// #include "melodies/all-star.h"

const int speakerPin = 13;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(speakerPin, OUTPUT);
  tone(speakerPin, 650, 100);
}

void serialEvent() 
{
    // tempo|note1@beat1|note2@beat2|note3@beat3|note4@beat4... tempo, beats, and notes are 4 char long ints
    // 0114|0466@0228|0466@0456|0415@0228|0370@0228
    String in = Serial.readString();
    int tempo = in.substring(0, 4).toInt();
    String consumeString = in.substring(5);
    int len = (in.length() + 1) / 10; // 0000|.. ends with 0000, add one to get a length that is divisible with 5
    int notes[len];
    int beats[len];

    for (int i = 0; i < len; i++)
    {
      notes[i] = consumeString.substring(0, 4).toInt();
      beats[i] = consumeString.substring(5, 9).toInt();
      consumeString = consumeString.substring(10);
    }

    delay(1000);
    int notes1[4] = {466, 466, 415, 370};
    int beats1[4] = {228, 456, 228, 228};
    
    play(4, 114, notes1, beats1);
}

void loop() 
{  
  // playMelody(ex);
  // delay(1000);
  // playMelody(ttls);
  // delay(1000);
  // playMelody(hbty);
  // delay(1000);
  // playMelody(jvedt);
  // delay(1000);
  // playMelody(tom);
  // delay(1000);
  // playMelody(as);
  // delay(1000);
}

void playMelody(Melody m)
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

  play(mLength, tempo, notes, beats);
}

void play(int len, int tempo, int* notes, int* beats)
{
  for (int i = 0; i < len; i++) 
  {
    // Rest/Pause
    if (notes[i] == 0) 
    {
      delay(beats[i] * tempo);
      continue;
    }

    tone(speakerPin, notes[i], beats[i] * tempo);

    // pause between notes
    delay(tempo / 2); 
  }
}
