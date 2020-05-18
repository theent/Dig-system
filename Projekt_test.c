
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

    int horizontalMove = adcRead(2); // Horizontaljoystick
    int verticalMove = adcRead(1);   //Verticaljoystick

    if (horizontalMove < JOYSTICK_NEUTRAL_HORIZONTAL - JOYSTICK_THRESHOLD)
  {
    val1 = 3;
  }

  else if (horizontalMove > JOYSTICK_NEUTRAL_HORIZONTAL + JOYSTICK_THRESHOLD)
  {
    val1 = 1;
  }

  else if (verticalMove < JOYSTICK_NEUTRAL_VERTICAL - JOYSTICK_THRESHOLD)
  {
    val1 = 4;
  }

  else if (verticalMove > JOYSTICK_NEUTRAL_VERTICAL + JOYSTICK_THRESHOLD)
  {
    val1 = 2;
  } else {
    return None;
  }

  



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



void draw() {
for (char cell = 0; cell < 8; cell++){
for (char x = 0; x < 128; x++){

waitForDisplay();
char displayX;

if (x < 64) {

waitForDisplay();
cs1high()

waitForDisplay();
cs2low();

waitForDisplay();
displayX = x;

} 
else {

waitForDisplay();
cs2high();

waitForDisplay();
cs1low();

waitForDisplay();
displayX = x - 64;

}

waitForDisplay();
setX(displayX);

waitForDisplay();
setCell(cell);



waitForDisplay();

rsHigh();
rwLow();

PORTB = virtual_display[cell][x];



eHigh();
eLow();


virtual_display[cell][x] = 0; // Reset virtual_display afterwards



}
}
}


void setCell(char cell)
{
  rsLow();
  rwLow();

  PORTB = 0b10111000 | cell; // setX del

  eHigh();
  eLow();
}




void setX(char x)
{
  rsLow();
  rwLow();

  PORTB = 0b01000000 | x;  // st Y del

  eHigh();
  eLow();
}

void waitForDisplay()
{
  PORTB &= 0x7F;
  DDRB = 0x7F;

  rsLow();
  rwHigh();

  while (PINB & 0x80)
    ;

  DDRB = 0xFF;
}


void setPixel(char x, char y,)

{

virtual_display[y / 8][x] |= (1 << (y % 8));

}