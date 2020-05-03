
#define F_CPU 8000000UL

#include <avr/io.h>
#include <time.h>
#include <stdlib.h>
#include <util/delay.h>

#define JOYSTICK_NEUTRAL_HORIZONTAL 420
#define JOYSTICK_NEUTRAL_VERTICAL 500
#define JOYSTICK_THRESHOLD 150



typedef enum Direction
{
  None,
  Left,
  Right,
  Up,
  Down
} Direction;





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







// Return the direction created by the given joystick
Direction getDirectionForJoystick(int horizontalPotensometer, int verticalPotensometer)
{
  int horizontalMove = adcRead(horizontalPotensometer);
  int verticalMove = adcRead(verticalPotensometer);

  if (horizontalMove < JOYSTICK_NEUTRAL_HORIZONTAL - JOYSTICK_THRESHOLD)
  {
    return Left;
  }

  if (horizontalMove > JOYSTICK_NEUTRAL_HORIZONTAL + JOYSTICK_THRESHOLD)
  {
    return Right;
  }

  if (verticalMove < JOYSTICK_NEUTRAL_VERTICAL - JOYSTICK_THRESHOLD)
  {
    return Up;
  }

  if (verticalMove > JOYSTICK_NEUTRAL_VERTICAL + JOYSTICK_THRESHOLD)
  {
    return Down;
  }

  return None;
};







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

_delay_ms(3000);


for(i = 0; i<4; i++) {


    for(j = 0; j<4; j++) {
       spelplan2[i][j] = false;

}





/* Input från spelare */
int val1;
int val2;
int cho1, cho2;
int x1, y1;

while(kartkvar(spelplan2)) {

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
