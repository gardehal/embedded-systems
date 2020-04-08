// https://www.arduino.cc/en/tutorial/melody
// https://roboticsbackend.com/arduino-object-oriented-programming-oop/

class Melody
{
  private:
    String melodyName;
    int melodyLength;
    char* notes;
    int* beats;
    int tempo;
    
  public:
    Melody(String melodyName, char* notes, int* beats, int tempo)
    {
      this->melodyName = melodyName;
      this->melodyLength = strlen(notes);
      this->notes = notes;
      this->beats = beats;
      this->tempo = tempo;
    }

    void setMelodyName(String melodyName)
    {
      this->melodyName = melodyName;
    }

    String getMelodyName()
    {
      return this->melodyName;
    }

    void setMelodyLength(int melodyLength)
    {
      this->melodyLength = melodyLength;
    }

    int getMelodyLength()
    {
      return this->melodyLength;
    }

    void setNotes(char* notes)
    {
      this->notes = notes;
    }

    char* getNotes()
    {
      return this->notes;
    }

    void setBeats(int* beats)
    {
      this->beats = beats;
    }

    int* getBeats()
    {
      return this->beats;
    }

    void setTempo(int tempo)
    {
      this->tempo = tempo;
    }

    int getTempo()
    {
      return this->tempo;
    }
};
