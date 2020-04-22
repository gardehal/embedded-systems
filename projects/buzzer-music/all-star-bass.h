

int asTempo = 114;

int asBassNotes[] = { NOTE_C6, 0, // Signal start and synchronization
                      // Verse 1
                      0, NOTE_FS2, NOTE_CS3, NOTE_GS2, NOTE_B2, 
                      NOTE_FS2, NOTE_CS3, NOTE_GS2, NOTE_B2, 
                      NOTE_FS2, NOTE_CS3, NOTE_GS2, NOTE_B2, 
                      NOTE_FS2, NOTE_CS3, NOTE_GS2, 0 };
int asBassBeats[] = { 1, 8, 
                      4, 8, 8, 8, 8,
                      8, 8, 8, 8, 
                      8, 8, 8, 8,
                      8, 8, 8, 
                      // Pre chorus
                      8 };
Melody asBass = Melody("All Star (Bass)", asBassNotes, asBassBeats, asTempo);