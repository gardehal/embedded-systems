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