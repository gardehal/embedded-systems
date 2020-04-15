// https://www.arduino.cc/en/tutorial/melody
// https://roboticsbackend.com/arduino-object-oriented-programming-oop/

class Melody
{
  private:
    String melodyName;
    int melodyLength;
    int* notes;
    int* beats;
    int tempo;
    
  public:
    Melody(String melodyName, int* notes, int* beats, int tempo)
    {
      this->melodyName = melodyName;

      int len = 0;
      for(len; true; len++)
        if(beats[len] == 0)
          break;
      
      this->melodyLength = len;
      
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

    void setNotes(int* notes)
    {
      this->notes = notes;
    }

    int* getNotes()
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
