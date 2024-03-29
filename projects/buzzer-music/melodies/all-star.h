
String asName = "All Star - Smash Mouth";
int asNotes[] = { NOTE_C6, 0, // Signal start and synchronization
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
                      NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, // sounds somewhat flat
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
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, 
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, 
                      0, NOTE_AS4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5, 
                      NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_FS4, NOTE_FS4, NOTE_GS4, 
                      NOTE_FS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_GS4, 
                      NOTE_AS4, NOTE_DS4, 0,
                      // Verse 2
                      NOTE_DS4, NOTE_DS4, NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_AS4, NOTE_AS4, NOTE_CS5, NOTE_B4, NOTE_AS4, NOTE_FS4, 
                      NOTE_GS4, NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_GS4, 
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_DS4, 
                      NOTE_DS4, NOTE_CS4, NOTE_CS4, NOTE_AS4, NOTE_CS5, NOTE_DS5, 
                      NOTE_CS5, NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_AS4, NOTE_AS4, NOTE_CS5, NOTE_CS5, NOTE_B4,
                      NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_DS4, NOTE_DS4, NOTE_DS4, 
                      NOTE_CS4, NOTE_DS5, NOTE_CS5, NOTE_CS5, NOTE_AS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_AS4, 
                      NOTE_GS4, NOTE_FS4, NOTE_GS4, NOTE_AS4, NOTE_DS4, NOTE_DS4, 
                      NOTE_DS4, 0,
                      // Chorus
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, 
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, 
                      0, NOTE_AS4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5, 
                      NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_FS4, NOTE_FS4, NOTE_GS4, 
                      NOTE_FS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_GS4, 
                      NOTE_AS4, NOTE_DS4, 0,
                      // Interlude
                      NOTE_CS6, NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_AS5, NOTE_B5, 
                      NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_DS5, NOTE_CS5, NOTE_CS5, 
                      NOTE_AS4, NOTE_GS4, NOTE_FS4, NOTE_AS4, NOTE_B4, NOTE_AS4, 
                      NOTE_GS4, NOTE_FS4, NOTE_DS4, NOTE_CS4, NOTE_CS5, NOTE_AS4, 
                      NOTE_GS4, NOTE_FS4, NOTE_AS4, NOTE_B4, NOTE_AS4, NOTE_GS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_CS4, NOTE_CS6, NOTE_AS5, NOTE_GS5, 
                      NOTE_FS5, NOTE_GS5, NOTE_AS5, NOTE_CS5, 0,
                      // Chorus
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, 
                      NOTE_AS4, NOTE_FS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, 
                      NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, 
                      0, NOTE_AS4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5, 
                      NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_FS4, NOTE_FS4, NOTE_GS4, 
                      NOTE_FS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_GS4, 
                      NOTE_AS4, NOTE_DS4, 0,
                      0 };
int asBeats[] = { 1, 8, // Signal start and synchronization
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
                      2, 4, 1, 1, 2, 4, 
                      1, 1, 2, 4, 4, 6,
                      2, 4, 1, 1, 2, 4, 
                      1, 1, 2, 4, 4, 4,
                      2, 4, 4, 2, 2, 2,
                      4, 2, 4, 2, 2, 2, 
                      2, 2, 4, 4, 4, 4,
                      2, 10, 1,
                      // Verse 2
                      1, 1, 2, 4, 1, 1, 
                      1, 1, 2, 1, 2, 1, 
                      1, 1, 2, 2, 2, 1, 
                      1, 2, 1, 1, 1, 1, 
                      1, 1, 1, 2, 2, 1, 
                      1, 3, 1, 1, 1, 1, 
                      2, 1, 1, 1, 1, 2, 
                      1, 2, 1, 2, 2, 3, 
                      1, 1, 1, 1, 1, 3, 
                      1, 1, 1, 1, 1, 2, 
                      1, 1, 1, 1, 2, 3, 
                      1, 2, 2, 4, 1, 2,
                      6, 1, 1, 1, 1, 1, 
                      1, 1, 1, 1, 1, 2, 
                      2, 6,
                      // Chorus
                      2, 4, 1, 1, 2, 4, 
                      1, 1, 2, 4, 4, 6,
                      2, 4, 1, 1, 2, 4, 
                      1, 1, 2, 4, 4, 4,
                      2, 4, 4, 2, 2, 2,
                      4, 2, 4, 2, 2, 2, 
                      2, 2, 4, 4, 4, 4,
                      2, 10, 1,
                      // Interlude
                      4, 4, 2, 4, 4, 2, 
                      4, 2, 2, 2, 2, 4, 
                      4, 2, 4, 4, 2, 4,
                      2, 2, 2, 2, 4, 4, 
                      2, 4, 4, 2, 4, 2, 
                      2, 2, 2, 4, 4, 2, 
                      4, 4, 2, 12, 1,
                      // Chorus
                      2, 4, 1, 1, 2, 4, 
                      1, 1, 2, 4, 4, 6,
                      2, 4, 1, 1, 2, 4, 
                      1, 1, 2, 4, 4, 4,
                      2, 4, 4, 2, 2, 2,
                      4, 2, 4, 2, 2, 2, 
                      2, 2, 4, 4, 4, 4,
                      2, 10, 1,
                      // Verse 3
                      // see all-star-treble-2.h
                      8, 0 };
int asTempo = 114;
Melody as = Melody(asName, asNotes, asBeats, asTempo);