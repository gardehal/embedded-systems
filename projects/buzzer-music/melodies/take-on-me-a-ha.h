
String tomName = "Take On Me - A-ha";
int tomNotes[] = { NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, 0, NOTE_B4, 
                   0, NOTE_E5, 0, NOTE_E5, 0, NOTE_E5, 
                   NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_A5, 
                   NOTE_A5, NOTE_E5, 0, NOTE_D5, 0, NOTE_FS5, 
                   0, NOTE_FS5, 0, NOTE_FS5, NOTE_E5, NOTE_E5, 
                   NOTE_FS5, NOTE_E5 };
int tomBeats[] = { 1, 1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1,
                   1, 1, 0 };
int tomTempo = 135;
Melody tom = Melody(tomName, tomNotes, tomBeats, tomTempo);