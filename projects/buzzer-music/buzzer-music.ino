// https://www.arduino.cc/en/tutorial/melody
// https://roboticsbackend.com/arduino-object-oriented-programming-oop/

class Melody
{
  public:
    String melodyName;
    int melodyLength;
    char* notes;
    int* beats;
    int tempo;
    
    Melody(String melodyName, int melodyLength, char* notes, int* beats, int tempo)
    {
      this->melodyName = melodyName;
      this->melodyLength = melodyLength;
      this->notes = notes;
      this->beats = beats;
      this->tempo = tempo;
    }
};

int speakerPin = 13;

// Register melodies
int ttlsLength = 15; // the number of notes
char ttlsNotes[] = "ccggaagffeeddc "; // a space represents a rest
int ttlsBeats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int ttlsTempo = 300;
Melody ttls = Melody("Twinkle Twinkle Little Star", ttlsLength, ttlsNotes, ttlsBeats, ttlsTempo);

void setup() 
{
  
  pinMode(speakerPin, OUTPUT);
}

void loop() 
{
  play(ttls);
}

void play(Melody m)
{
  for (int i = 0; i < m.melodyLength; i++) 
  {
    if (m.notes[i] == ' ') 
    {
      delay(m.beats[i] * m.tempo); // rest
    } else 
    {
      playNote(m.notes[i], m.beats[i] * m.tempo);
    }

    // pause between notes
    delay(m.tempo / 2); 
  }
}





void playTone(int tone, int duration) 
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
