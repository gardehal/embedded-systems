
int ttlsNotes[] = { NOTE_C6, NOTE_C6, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_A6, NOTE_G6, 
                    NOTE_F6, NOTE_F6, NOTE_E6, NOTE_E6, NOTE_D6, NOTE_D6, NOTE_C6, 0 }; // Zero ( 0 ) represents a rest
int ttlsBeats[] = { 1, 1, 1, 1, 1, 1, 2, 
                    1, 1, 1, 1, 1, 1, 2, 4,
                    0 };
int ttlsTempo = 300;
Melody ttls = Melody("Twinkle Twinkle Little Star", ttlsNotes, ttlsBeats, ttlsTempo);