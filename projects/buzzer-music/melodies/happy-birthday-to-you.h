
int hbtyNotes[] = { NOTE_C6, NOTE_C6, NOTE_D6, NOTE_C6, NOTE_F6, NOTE_E6,
                    NOTE_C6, NOTE_C6, NOTE_D6, NOTE_C6, NOTE_G6, NOTE_E6, // E7?
                    NOTE_C6, NOTE_C6, NOTE_C7, NOTE_A6, NOTE_F6, NOTE_E6, NOTE_D6,
                    NOTE_AS6, NOTE_AS6, NOTE_A6, NOTE_F6, NOTE_G6, NOTE_F6, 0 };
int hbtyBeats[] = { 1, 1, 1, 1, 1, 2,
                    1, 1, 1, 1, 1, 2,
                    1, 1, 1, 1, 1, 1, 2, 
                    1, 1, 1, 1, 1, 2, 4,
                    0 };
int hbtyTempo = 300;
Melody hbty = Melody("Happy Birthday To You", hbtyNotes, hbtyBeats, hbtyTempo);