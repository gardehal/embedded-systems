# Buzzer Music

A mix of songs or melodies that can be played on a passive buzzer.

I implemented a class ([melody.h](./melody.h)) which holds the melody information.
- String melodyName is the name of the melody or song.
- int melodyLength is the number of notes/beats in a melody. (would be easier to get this from int arrays, but can't infer as the arrays are pointers)
- int array notes that holds the values used by tone() function to make a certain tone. List of tones can be found in [tones.h](./tones.h).
- int array beats holds the length each tone should be played, where 1 is the shortest, and can be incremented as needed.
- int tempo is the speed the melody is played at, lower is faster.

Melodies, in order:
1. Twinkle Twinkle Little Star
1. Happy Birthday To You
1. Ja Vi Elsker Dette Landet (National Anthem of Norway)
1. Take On Me by Aha (National Anthem of Noray, international version)
1. All Star by Smash Mouth ([MP3-file](./audacity/all-star-mix.mp4))

No copyright infringement intended.

Since I only have one buzzer, melodies or songs with multiple notes played at the same time (ex. treble and bass, see All Star - Smash Mouth) must be played, recorded, and then synced in audio editing software. I noticed while combining the bass and treble for All Star that it didn't completely sync up though I should have added the notes and beats correctly.

- YouTube channel which has some easy to follow piano tutorials, used to make some of the melodies: https://www.youtube.com/channel/UCbaY6IEY0-pRHBU_qCswoNQ
- Base for melody class: https://www.arduino.cc/en/tutorial/melody
- Example I used to make a class: https://roboticsbackend.com/arduino-object-oriented-programming-oop/

[Code](./buzzer-music.ino)

[Video](./buzzer-music.mp4)

## Circuit Diagram

![Circuit Diagram](./buzzer-music.png)

## Add a song

1. Find either the sheet music or a tutorial (Piano tutorals can be made in a program called [Synthesia](https://synthesiagame.com), which will display the keys and length to hold down each key if sheet music is too hard to read).
1. Note down all the notes played in order. Notes can be found in [notes.h](./notes.h) and are prefixed with "NOTE_", followed by the letter of the note ("A", "B", etc.) and finally the octave number. For black keys, only sharp keys work, which need an "S" after the letter, before the number. Zeros ("0") can be used if there is a break where no notes should be played.
1. Write down the length each note should be held, use 1 for the shortest notes, then 2 for the second shortest, etc. Finish with a zero to mark the end of the beats array so the system can count the number of beats. 
1. By this step you should have one long list of refrences to note integer values, and one list of beats (how long the note is played for). These lists should be equally long EXCEPT the zero you added to the end of the beats list. Make these lists into int arrays (ex. `int notes[] = { NOTE_C4, NOTE_CS4, NOTE_D4 }` and `int beats[] = { 1, 2, 3, 0 };`).
1. Add the tempo (depends on the beats, tempo is likely to be somewhere between 100 and 300) and song name.
1. Finally use the function `play(Melody m)` function to play the song in either setup or loop. 

## TODO

Found a way to send data to arduino from computer though a Python library, plan is to use script to read .h song files and send bits of data to Arduino, this way there's no need to worry about storage.
- Flow: Start Arduino, python script, Serial Monitor tool must be closed?. Python finds file (id? name? index in folder?) send song title as displayable data and tempo as "hidden" data. Send array og single beat and note at a time tempo/speed controlled by Arduino? Might need a response function to ask for next data, otherwise functionality will be duplicated...   
- Python script for getting notes or music data
- Optional: implement functionality to play either from serial or .h (status quo)
- Document issues with sending data (incorrect usage, missing some timing still), solutions and general concept, usage, general knowledge for future projects. Also odd how delay between notes had to be changed, didn't seem to scale with tempo, beat or notes as well, put some arbatrary value. Old code may be useful, add tempo to it?
                for b in dataBeats:
                    sleepFor += int(b)
                
                # time.sleep(float(sleepFor) / 1000)
                