/*
 Plays any melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 01 Nov 2012
 by Vyacheslav Popov
 
 */

#define PIN_MELODY 8

// Guido music notation see http://wiki.ccarh.org/wiki/Guido_Music_Notation

char melody_game_end[] = "[c4/4 g3/8 g a/4 g _ b c4]";

char melody_star_wars1[] = "[g4/4 g g e/8 _/16 b/16 |g/4 e/8 _/16 b/16 g/2 |d5/4 d d e&/8 _/16 b&4/16 |g&/4 e/8 _/16 b/16 g/2]";
char melody_star_wars2[] = "[g5/4 g4/8 _/16 g g5/4 f#/8 _/16 f |e& d# e&/8 _ g#4 c#5/4 c/8 _/16 b&4 |b&/16 a b&/8 _ e g&/4 e/8 _/16 g |b&/4 g/8 _/16 b& d5/2]";                                      
char melody_star_wars3[] = "[g5/4 g4/8 _/16 g g5/4 f#/8 _/16 f |e& d# e&/8 _ g#4 c#5/4 c/8 _/16 b&4 |b&/16 a b&/8 _ e g&/4 e/8 _/16 b& |g/4 e/8 _/16 b& g/2]";
char melody_star_wars4[] = "[b&4/16 a b&/8 _ e g/4 e/8 _/16 b& |g&/4 e/8 _/16 b& g/2]";

// do-c re-d mi-e fa-f sol-g la-a si-b
float noteFrecuenceList[12] = {32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};

int noteOctave(float note, int octave)
{
   if (octave <= 1)
     return round(note);
   else
     return round(noteOctave(note * 2.0, octave - 1));
}

// Play a melody in the specify pin
void melodyPlay(char *melody)
{ 
  int noteDuration;
  int noteFrecuenceIndex;
  int octave;
  bool longFormat = false;  
  
  // iterate over the notes of the melody:
  for (int i = 0; i < strlen(melody); i++)
  {
    char c = melody[i];
       
    switch (c)
    {
      // Default values
      case '[':
        noteDuration = 0;
        noteFrecuenceIndex = -1;
        octave = 0;
        break;
      
      case 'c': // Note Do
        noteFrecuenceIndex = 0;
        break;
      case 'd': // Note Re
        noteFrecuenceIndex = 2;
        break;
      case 'e': // Note Mi
        noteFrecuenceIndex = 4;
        break;
      case 'f': // Note Fa
        noteFrecuenceIndex = 5;
        break;
      case 'g': // Note Sol
        noteFrecuenceIndex = 7;
        break;
      case 'a': // Note La
        noteFrecuenceIndex = 9;
        break;
      case 'b': // Note Si
        noteFrecuenceIndex = 11;
        break;
      
      case '_': // Silence
        noteFrecuenceIndex = -1;
        break;
      
      case '#': // Accidental Sharp
        noteFrecuenceIndex++;
        if (noteFrecuenceIndex > 11)
          noteFrecuenceIndex = 0;
        break;

      case '&': // Accidental Bemole
        noteFrecuenceIndex--;
        if (noteFrecuenceIndex < 0)
          noteFrecuenceIndex = 11;
        break;
      
      // Separator of duration
      case '/': 
        int j;
        char nextChar;
        char number[4];
        
        longFormat = true;
        
        j = i + 1;
        nextChar = melody[j];        

        do
        {
          number[j - i - 1] = nextChar;
          j++;
          nextChar = melody[j];
        }
        while (nextChar != ' ' && nextChar != ']');
        
        number[j - i - 1] = '\0';
        noteDuration = atoi(number);

  
        // to calculate the note octave
        number[0] = melody[i-1];
        number[1] = '\0';
        if (number[0] >= '0' && number[0] <= '9')
          octave = atoi(number);
        break;
        
      // Separators of note definition
      case ' ':
      case ']': 
        if (!longFormat)
        {
          // to calculate the note octave
          number[0] = melody[i-1];
          number[1] = '\0';
          if (number[0] >= '0' && number[0] <= '9')
            octave = atoi(number);  
        } 
        longFormat = false;
        
        // to calculate the note duration, take one second 
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int duration = 2000 / noteDuration;
        float noteFrecuence = noteFrecuenceIndex > -1 ? noteFrecuenceList[noteFrecuenceIndex] : 0;
        int note = noteOctave(noteFrecuence, octave);
        tone(PIN_MELODY, note, duration);
    
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = duration * 1.30;
        delay(pauseBetweenNotes);
        
        // stop the tone playing:
        noTone(PIN_MELODY);
          
        break;      
    }
  
 
  
  }
}

void setup() 
{
  // call to play my melody
  melodyPlay(melody_star_wars1);
  melodyPlay(melody_star_wars2);
  melodyPlay(melody_star_wars3);
  melodyPlay(melody_star_wars4);
  melodyPlay(melody_star_wars1);
  melodyPlay(melody_star_wars3);
  melodyPlay(melody_star_wars3);
}

void loop() 
{
  // no need to repeat the melody.
}
