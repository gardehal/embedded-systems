
int ttlsNotes[] = { NOTE_C6, NOTE_C6, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_A6, NOTE_G6, 
                    NOTE_F6, NOTE_F6, NOTE_E6, NOTE_E6, NOTE_D6, NOTE_D6, NOTE_C6, 0 }; // Zero ( 0 ) represents a rest
int ttlsBeats[] = { 1, 1, 1, 1, 1, 1, 2, 
                    1, 1, 1, 1, 1, 1, 2, 4,
                    0 };
int ttlsTempo = 300;
Melody ttls = Melody("Twinkle Twinkle Little Star", ttlsNotes, ttlsBeats, ttlsTempo);

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

int jvedtNotes[] = { NOTE_F4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_C4, NOTE_D4, 
                     NOTE_DS4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_DS4, NOTE_D4, 0 };
int jvedtBeats[] = { 3, 1, 2, 2, 2, 2, 2, 
                     2, 3, 1, 2, 2, 4, 4,
                     0 };
int jvedtTempo = 300;
Melody jvedt = Melody("Ja Vi Elsker Dette Landet (National Anthem of Norway)", jvedtNotes, jvedtBeats, jvedtTempo);

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
Melody tom = Melody("Take On Me", tomNotes, tomBeats, tomTempo);