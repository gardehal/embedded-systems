
String jvedtName = "Ja Vi Elsker Dette Landet (National Anthem of Norway)";
int jvedtNotes[] = { NOTE_F4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_C4, NOTE_D4, 
                     NOTE_DS4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_DS4, NOTE_D4, 0 };
int jvedtBeats[] = { 3, 1, 2, 2, 2, 2, 2, 
                     2, 3, 1, 2, 2, 4, 4,
                     0 };
int jvedtTempo = 300;
Melody jvedt = Melody(jvedtName, jvedtNotes, jvedtBeats, jvedtTempo);