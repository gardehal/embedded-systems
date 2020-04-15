
int asTrebNotes[] = { NOTE_C6, 0, // Signal start and synchronization
                      // Verse 1
                      NOTE_FS4, NOTE_CS5, NOTE_AS4, NOTE_AS4, NOTE_GS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_B4, NOTE_AS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_CS5, NOTE_AS4, NOTE_AS4, NOTE_GS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_CS4, 0, NOTE_FS4, 
                      NOTE_FS4, NOTE_CS5, NOTE_AS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_B4, NOTE_AS4, NOTE_AS4, NOTE_GS4, 
                      NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_CS5, NOTE_AS4, NOTE_AS4, 
                      NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_DS4,
                      // Pre chorus
                      0, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_CS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, NOTE_FS4, 
                      NOTE_AS4, NOTE_AS4, NOTE_CS5, NOTE_B4, NOTE_AS4, NOTE_FS4, 
                      NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_AS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_CS4, NOTE_FS4, NOTE_FS4, NOTE_FS4,
                      0, NOTE_AS4, NOTE_CS5, NOTE_AS4, NOTE_DS5, NOTE_AS4, 
                      NOTE_CS5, NOTE_AS4, NOTE_DS5, NOTE_AS4, NOTE_CS5, NOTE_B4, 
                      NOTE_AS4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_FS4, 
                      0, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, 
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_DS4, 
                      NOTE_DS4, 0,
                      // Chorus
                      0 };
int asTrebBeats[] = { 1, 8, // Signal start and synchronization
                      // Verse 1
                      4, 2, 2, 4, 2, 2, 
                      2, 4, 2, 2, 2, 2, 
                      4, 2, 2, 2, 4, 2,
                      2, 2, 4, 6, 4, 2,
                      2, 2, 2, 2, 2, 2,
                      2, 2, 4, 2, 2, 2,
                      2, 2, 2, 4, 2, 2,
                      4, 2, 2, 4, 6,
                      // Pre chorus
                      4, 3, 1, 2, 2, 1, 
                      1, 1, 1, 2, 2, 1, 
                      3, 2, 1, 1, 2, 1, 
                      1, 1, 1, 2, 1, 3, 
                      1, 1, 2, 2, 1, 1, 
                      2, 2, 3, 1, 2, 2, 
                      2, 1, 1, 2, 2, 2,
                      2, 1, 2, 1, 2, 1, 
                      2, 1, 2, 1, 2, 2,
                      2, 2, 2, 1, 2, 4,
                      1, 1, 1, 1, 2, 1, 
                      1, 2, 4, 2, 1, 1,
                      1, 1, 2, 1, 1, 2,
                      4, 4,
                      // Chorus
                      8, 0 };
int asTempo = 120;
Melody asTreb = Melody("All Star (Treble)", asTrebNotes, asTrebBeats, asTempo);

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