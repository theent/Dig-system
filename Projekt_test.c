
#define F_CPU 8000000UL

#include <avr/io.h>
#include <time.h>
#include <stdlib.h>
#include <util/delay.h>

#define JOYSTICK_NEUTRAL_HORIZONTAL 420     // Neutrala värdet för x-axel
#define JOYSTICK_NEUTRAL_VERTICAL 500       // Neutrala värdet för y-axel
#define JOYSTICK_THRESHOLD 150              // Gränsvärde för rörelse, dvs man måste röra joysticken en vis bit









// Get result from ADC
uint16_t adcRead(uint8_t ch)  
{
  // Make sure input is 0-7
  ch &= 0b00000111;
  // Set MUX-channel
  ADMUX = (ADMUX & 0xF8) | ch;
  // Start ADC
  ADCSRA |= (1 << ADSC);
  // Wait for ADC to complete
  while (ADCSRA & (1 << ADSC))
    ;
  return (ADC);
}












main() 
{
srand(time(NULL));

DDRA = 0x00; //Alla pins i A blir till input

DDRA &= ~(1<<PA3); 
DDRA &= ~(1<<PA4);


while(true) {



/* Värderna i spelplanen */
int spelplan[4][4];



/* ifall de är vända eller icke vända */
bool spelplan2[4][4];

int x,y = 0;






int i, j, s, r;
int slump1, slump2;
int c = 0;
for(i = 0; i<4; i++) {


    for(j = 0; j<4; j++) {
       spelplan[i][j] = 0;
       spelplan2[i][j] = false;

}

int count = 0;


for(s = 0; s<8; s++) {
    count++;
    for(r = 0; r<2; r++) {
        
        while(true) {
            
            /* Slumptal från 0-3 */
            slump1 = rand() % 4; 
            slump2 = rand() % 4;

            if(spelplan[slump1][slump2] == 0) {
                
                spelplan[slump1][slump2] = count;
                break;

            }


        }


    }


}


for(i = 0; i<4; i++) {


    for(j = 0; j<4; j++) {
       spelplan2[i][j] = true;

}
}


_delay_ms(3000);


for(i = 0; i<4; i++) {


    for(j = 0; j<4; j++) {
       spelplan2[i][j] = false;

}
}

 // Init ADC
  ADMUX |= (1 << REFS0);                                            // Set the reference of ADC
  ADCSRA |= (1 << ADEN) | (1 < ADPS2) | (1 < ADPS1) | (1 << ADPS0); // Enable ADC, set prescaler to 128


/* Input från spelare */
int val1;
int val2;
int cho1, cho2;
int x1, y1;


while(kartkvar(spelplan2)) {

  
    val1 = movement();


    switch (val1)
    {
    case 1 /* Höger pil */:
        
        if(x<3) {
            x++;
        } else {
            x = 3;
        }

        break;

        case 2 /* Ner pil */:
        
        if(y<3) {
            y++;
        } else {
            y = 3;
        }

        break;

        case 3 /* vänster pil */:
        
        if(x > 0) {
            x--;
        } else {
            x = 0;
        }

        break;


         case 4 /* Uppåt pil */:
        
        if(y > 0) {
            y--;
        } else {
            y = 0;
        }

        break;

        case 5: /* val av kort */
        
        if(val2 == 0) {

           cho1 = spelplan[x][y];
            spelplan2[x][y] = true;
            val2++;
            x1 = x;
            y1 = y;
        }

        else {
            
            cho2 = spelplan[x][y];
            spelplan2[x][y] = true;

            if(!compare(cho1, cho2)) {
                spelplan2[x][y] = false;
                spelplan2[x1][y1] = false;
            }

            val2 = 0;

        }

        break;
    
    default:
        break;
    }

    





}

}

}
while(true) {
    if(PINA & (1<<PA3) == 1) //om resetknappen är nedtryckt{
        rsHigh();
        rwLow();
	PORTD |= 0b00000100; //Skickar en 1 på RESET ingången på skärmen via PD2
            break;
    }
}


}


/* Kollar om det finns kort kvar */

bool kartkvar(bool a[][]) {


int h, k;

for( h = 0; h<4; h++) {
    for(k = 0; k<4, k++) {

        if(!a[h][k]) {
            return true;

        }


    }
    return false;


}


}

/* Jämför två kort om de är lika */

bool compare(int c, int d) {



if(c==d) {
    return true;

} else
{
    return false;
}





}





// Läser vilken rörelse som spelaren gör

int movement() {
    int val3 = 0;

    int horizontalMove = adcRead(2); // Horizontaljoystick
    int verticalMove = adcRead(1);   //Verticaljoystick

    if (horizontalMove < JOYSTICK_NEUTRAL_HORIZONTAL - JOYSTICK_THRESHOLD)
  {
    val3 = 3; // Vänster
    return val3;
  }

  else if (horizontalMove > JOYSTICK_NEUTRAL_HORIZONTAL + JOYSTICK_THRESHOLD)
  {
    val3 = 1; //Höger
    return val3;
  }

  else if (verticalMove < JOYSTICK_NEUTRAL_VERTICAL - JOYSTICK_THRESHOLD)
  {
    val3 = 4; //Uppåt
    return val3;
  }

  else if (verticalMove > JOYSTICK_NEUTRAL_VERTICAL + JOYSTICK_THRESHOLD)
  {
    val3 = 2; //Ner
    return val3;
  } 
  
  else if (PINA & (1<<PA4) == 1) {
      val3 = 5; // Enter knapp
      return val3;
  }

   else {
    return None;
  }




}

void rsHigh()
{
  PORTD |= 0b00010000;
}

void rwLow()
{
  PORTD &= 0b11110111;
}