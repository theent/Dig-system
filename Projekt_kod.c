
#define F_CPU 8000000UL

#include <avr/io.h>
#include <time.h>
#include <stdlib.h>
#include <util/delay.h>




#define JOYSTICK_NEUTRAL_HORIZONTAL 420 // Neutrala värdet för x-axel
#define JOYSTICK_NEUTRAL_VERTICAL 500   // Neutrala värdet för y-axel
#define JOYSTICK_THRESHOLD 150          // Gränsvärde för rörelse, dvs man måste röra joysticken en vis bit






char virtuel_spelplan[8][128];





main()
{
 // Init random-generator
 srand(time(NULL));

  DDRA = 0x00; //Alla pins i A blir till input

  DDRA &= ~(1 << PA3);
  DDRA &= ~(1 << PA4);
  DDRB = 0b11111111;
  DDRD = 0b11111111;


  while (true)
  {

    /* Värderna i spelplanen */
    int spelplan[2][4];

    /* ifall de är vända eller icke vända */
    bool spelplan2[2][4];

    /* Kordinaterna för spelplanen */
    int kordplanx[2][4];
    int kordplany[2][4];

  int tempkord1 = 0;

  for(int l = 0; l<2; l++) {
    tempkord1 = 0;
    for(int m = 0; m<4; m++) {
        kordplanx[l][m] = tempkord1 + 16;
        if(l == 2) {
          kordplany[l][m] = 32;
        } else {
          kordplany[l][m] = 16;
        }
    }

  }

  // Start kordinater
  int kordx, kordy = 16;

    int x, y = 0;


   

    int count = 0; //Räknar variabel för kort
    int slump1, slump2;
    int c = 0;

    int i, j, s, r;
    for (i = 0; i < 2; i++)
    {

      for (j = 0; j < 4; j++)
      {
        spelplan[i][j] = 0;
        spelplan2[i][j] = false;
      }
    }
   

    for (s = 0; s < 4; s++)
    {
      count++; 
      for (r = 0; r < 2; r++)
      {

        while (true)
        {

           /* Slumptal från 0-1 */
          slump1 = rand() % 2;
          /* Slumptal från 0-3 */
          slump2 = rand() % 4;

          if (spelplan[slump1][slump2] == 0)
          {

            spelplan[slump1][slump2] = count;

            break;
          }
        }
      }
    }



  // Ritar Spelplanen
    drawField()


// Visar korten för spelaren för memorering
    for (i = 0; i < 2; i++)
    {

      for (j = 0; j < 4; j++)
      {
        spelplan2[i][j] = true;
        kort_som_ska_ritas(spelplan[i][j], kordplanx[i][j],kordplany[i][j]);
        
      }
    }
  }



  _delay_ms(3000);


//Vänder korten upp & ner
  for (i = 0; i < 2; i++)
  {

    for (j = 0; j < 4; j++)
    {
      spelplan2[i][j] = false;
      removePixels(kordplanx[i][j],kordplany[i][j]);
      Draw();
    }
  }
}





// Init ADC
ADMUX |= (1 << REFS0);                                            // Set the reference of ADC
ADCSRA |= (1 << ADEN) | (1 < ADPS2) | (1 < ADPS1) | (1 << ADPS0); // Enable ADC, set prescaler to 128





int val1;


int val2;

// spelarens första och andra val 1
int cho1, cho2;

// temp värden
int x1, y1;





while (kartkvar(spelplan2))
{

startDisplay();
PositionBlink(kordx, kordy);

  /* Input från spelare */
  val1 = movement();

  switch (val1)
  {
  case 1 /* Höger pil */:

    if (x < 3)
    {
      x++;
      kordx = kordx + 16;
    }
    else
    {
      x = 3;
      
    }

    break;

  case 2 /* Ner pil */:

    if (y < 1)
    {
      y++;
      kordy = kordy + 16;
    }
    else
    {
      y = 1;
    }

    break;

  case 3 /* vänster pil */:

    if (x > 0)
    {
      x--;
      kordx = kordx - 16;
    }
    else
    {
      x = 0;
      
    }

    break;

  case 4 /* Uppåt pil */:

    if (y > 0)
    {
      y--;
      kordy = kordy - 16;
    }
    else
    {
      y = 0;
    }

    break;

  case 5: /* val av kort */

  // Om spelaren ska välja första kortet
    if (val2 == 0)
    {

      cho1 = spelplan[y][x];
      spelplan[y][x] = true;
      kort_som_ska_ritas(spelplan[y][x], kordplanx[x][y],kordplany[x][y]);
      val2++;
      x1 = x;
      y1 = y;
    }

// Om spelaren ska välja sitt andra kort och jämföra
    else
    {

      cho2 = spelplan[y][x];
      spelplan[y][x] = true;
      kort_som_ska_ritas(spelplan[y][x], kordplanx[y][x],kordplany[y][x]);

      //Ifall korten inte är lika vänds de tillbaks
      if (!compare(cho1, cho2))
      {
        spelplan[y][x] = false;
        removePixels(kordplanx[x][y],kordplany[x][y]);

        spelplan[y1][x1] = false;
        removePixels(kordplanx[x][y],kordplany[x][y]);
        Draw();
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


while (true)
{
  if (PINA & (1 << PA3) == 1) //om resetknappen är nedtryckt{
    rsHigh();
  rwLow();
  PORTD |= 0b00000100; //Skickar en 1 på RESET ingången på skärmen via PD2
  break;
}
}
}



// Få resultat från ADC
uint16_t adcRead(uint8_t ch)
{
  // Gör at input är mellan 0-7
  ch &= 0b00000111;
  // Sätter MUX-channel (MUX2-0)
  ADMUX = (ADMUX & 0xF8) | ch;
  // Startar ADC
  ADCSRA |= (1 << ADSC);
  // väntar på att ADC ska bli klar
  while (ADCSRA & (1 << ADSC))
    ;
  return (ADC);
}






/* Kollar om det finns kort kvar */

bool kartkvar(bool a[][])
{

  int h, k;

  for (h = 0; h < 2; h++)
  {
    for (k = 0; k < 4, k++)
    {

      if (!a[h][k])
      {
        return true;
      }
    }
    return false;
  }
}







/* Jämför två kort om de är lika */

bool compare(int c, int d)
{

  if (c == d)
  {
    return true;
  }
  else
  {
    return false;
  }
}





// Ritar valda pixlar
void draw()
{
  for (char cell = 0; cell < 8; cell++)
  {
    for (char x = 0; x < 128; x++)
    {

      waitForDisplay();
      char displayX;

      if (x < 64)
      {

        waitForDisplay();
        cs1high()

            waitForDisplay();
        cs2low();

        waitForDisplay();
        displayX = x;
      }
      else
      {

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

      PORTB = virtuel_spelplan[cell][x];

      eHigh();
      eLow();

      virtuel_spelplan[cell][x] = 0; // Reset virtuel_spelplan
    }
  }
}





void setCell(char cell)
{
  rsLow();
  rwLow();

  PORTB = 0b10111000 | cell; // set X-Adress

  eHigh();
  eLow();
}





void setX(char x)
{
  rsLow();
  rwLow();

  PORTB = 0b01000000 | x; // set Y-Adress

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




//Reserverar en pixel för framtida ritning
void setPixel(char x, char y, )

  { 

  virtuel_spelplan[y / 8][x] |= (1 << (y % 8));

  }


// Tar väck pixlarna från spelkortet
void removePixels(char x, char y, )  { 

x = x - 5; //flyttar startpositionen till vänster hörna
y = y - 5; 


for(int i = x;i<11;i++){
	for(int j = y; j <11;j j ++){

	virtuel_spelplan[j / 8][i] &= (0 << (j % 8));


	}
}
  }






  // Läser vilken rörelse som spelaren gör

  int movement()
  {
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

    else if (PINA & (1 << PA4) == 1)
    {
      val3 = 5; // Enter knapp
      return val3;
    }

    else
    {
      return None;
    }
  }




  

 void rwHigh()		//Skickar en 1 på R/W ingången på skärmen via PD3
{
  PORTD |= 0b00001000;
}

void rwLow()
{
  PORTD &= 0b11110111;
}

void rsHigh()		//Skickar en 1 på D/I ingången på skärmen via PD4
{
  PORTD |= 0b00010000;
}

void rsLow()
{
  PORTD &= 0b11101111;
}

  void startDisplay(){

  PORTB = 0b00111111;

  cs1low();
  cs2low();

  resetHigh();
  rwLow();
  rsLow();
  eHigh();

  cs1high();
  cs2high();

  eLow();
  eHigh();
}

void eHigh()		//Skickar en 1 på E ingången på skärmen via PD5
{
  PORTD |= 0b00100000;
}

void eLow()
{
  PORTD &= 0b11011111;
}

void cs1high()		/tar hand om pixlar 0-64, PD1-CS1
{
  PORTD |= 0b00000001;
}

void cs1low()
{
  PORTD &= 0b11111110;
}

void cs2high()		//tar hand om pixlar 64-128, PD1-CS2
{
  PORTD |= 0b00000010;
}

void cs2low()
{
  PORTD &= 0b11111101;
}




/* HÄR BÖRJAR SPELKORTEN */


void bunny(char x, char y){

char x1 = x; //sparar temp värden för startpositionen dvs mitten
char y1 = y;

x = x - 5; //flyttar startpositionen till vänster hörna
y = y - 5; 

setPixel(x + 3, y + 0);
setPixel(x + 5, y + 0);
setPixel(x + 2, y + 1);
setPixel(x + 4, y + 1);
setPixel(x + 6, y + 1);
setPixel(x + 2, y + 2);
setPixel(x + 4, y + 2);
setPixel(x + 6, y + 2);
setPixel(x + 1, y + 4);
setPixel(x + 6, y + 4);
setPixel(x + 0, y + 5);
setPixel(x + 7, y + 5);
setPixel(x + 8, y + 5);
setPixel(x + 9, y + 5);
setPixel(x + 0, y + 6);
setPixel(x + 3, y + 6);
setPixel(x + 10, y + 6);
setPixel(x + 0, y + 7);
setPixel(x + 0, y + 8);
setPixel(x + 1, y + 9);
setPixel(x + 2, y + 9);
setPixel(x + 3, y + 9);
setPixel(x + 7, y + 9);
setPixel(x + 8, y + 9);
setPixel(x + 10, y + 9);
setPixel(x + 2, y + 10);
setPixel(x + 5, y + 10);
setPixel(x + 6, y + 10);
setPixel(x + 10, y + 10);


Draw();

x = x1;
y = y1;


}

void Ghost(char x, char y){
char x1 = x; //sparar temp värden
char y1 = y;
x = x - 5; //flyttar startpositionen till vänster hörna
y = y - 5;

setPixel(x + 2, y + 0);
setPixel(x + 3, y + 0);
setPixel(x + 4, y + 0);
setPixel(x + 5, y + 0);
setPixel(x + 6, y + 0);
setPixel(x + 7, y + 0);
setPixel(x + 8, y + 0);
setPixel(x + 1, y + 1);
setPixel(x + 9, y + 1);
setPixel(x + 0, y + 2);
setPixel(x + 10, y + 2);
setPixel(x + 0, y + 3);
setPixel(x + 2, y + 3);
setPixel(x + 8, y + 3);
setPixel(x + 10, y + 3);
setPixel(x + 0, y + 4);
setPixel(x + 2, y + 4);
setPixel(x + 3, y + 4);
setPixel(x + 7, y + 4);
setPixel(x + 8, y + 4);
setPixel(x + 10, y + 4);
setPixel(x + 0, y + 5);
setPixel(x + 2, y + 5);
setPixel(x + 3, y + 5);
setPixel(x + 4, y + 5);
setPixel(x + 6, y + 5);
setPixel(x + 7, y + 5);
setPixel(x + 8, y + 5);
setPixel(x + 10, y + 5);
setPixel(x + 0, y + 6);
setPixel(x + 10, y + 6);
setPixel(x + 0, y + 7);
setPixel(x + 10, y + 7);
setPixel(x + 0, y + 8);
setPixel(x + 3, y + 8);
setPixel(x + 7, y + 8);
setPixel(x + 10, y + 8);
setPixel(x + 1, y + 9);
setPixel(x + 2, y + 9);
setPixel(x + 4, y + 9);
setPixel(x + 5, y + 9);
setPixel(x + 6, y + 9);
setPixel(x + 8, y + 9);
setPixel(x + 9, y + 9);
setPixel(x + 1, y + 10);
setPixel(x + 2, y + 10);
setPixel(x + 4, y + 10);
setPixel(x + 5, y + 10);
setPixel(x + 6, y + 10);
setPixel(x + 8, y + 10);
setPixel(x + 9, y + 10);


Draw();
x = x1;
y = y1;

}

void Ghost(char x, char y){
char x1 = x; //sparar temp värden
char y1 = y;
x = x - 5; //flyttar startpositionen till vänster hörna
y = y - 5;

setPixel(x + 2, y + 0);
setPixel(x + 3, y + 0);
setPixel(x + 7, y + 0);
setPixel(x + 8, y + 0);
setPixel(x + 1, y + 1);
setPixel(x + 4, y + 1);
setPixel(x + 6, y + 1);
setPixel(x + 9, y + 1);
setPixel(x + 0, y + 2);
setPixel(x + 5, y + 2);
setPixel(x + 10, y + 2);
setPixel(x + 0, y + 3);
setPixel(x + 10, y + 3);
setPixel(x + 0, y + 4);
setPixel(x + 10, y + 4);
setPixel(x + 0, y + 5);
setPixel(x + 10, y + 5);
setPixel(x + 1, y + 6);
setPixel(x + 9, y + 6);
setPixel(x + 2, y + 7);
setPixel(x + 8, y + 7);
setPixel(x + 3, y + 8);
setPixel(x + 7, y + 8);
setPixel(x + 4, y + 9);
setPixel(x + 6, y + 9);
setPixel(x + 5, y + 10);



Draw();
x = x1;
y = y1;

}

  
void Heart(char x, char y){
char x1 = x; //sparar temp värden
char y1 = y;
x = x - 5; //flyttar startpositionen till vänster hörna
y = y - 5;

setPixel(x + 2, y + 0);
setPixel(x + 3, y + 0);
setPixel(x + 7, y + 0);
setPixel(x + 8, y + 0);
setPixel(x + 1, y + 1);
setPixel(x + 4, y + 1);
setPixel(x + 6, y + 1);
setPixel(x + 9, y + 1);
setPixel(x + 0, y + 2);
setPixel(x + 5, y + 2);
setPixel(x + 10, y + 2);
setPixel(x + 0, y + 3);
setPixel(x + 10, y + 3);
setPixel(x + 0, y + 4);
setPixel(x + 10, y + 4);
setPixel(x + 0, y + 5);
setPixel(x + 10, y + 5);
setPixel(x + 1, y + 6);
setPixel(x + 9, y + 6);
setPixel(x + 2, y + 7);
setPixel(x + 8, y + 7);
setPixel(x + 3, y + 8);
setPixel(x + 7, y + 8);
setPixel(x + 4, y + 9);
setPixel(x + 6, y + 9);
setPixel(x + 5, y + 10);



Draw();
x = x1;
y = y1;

}

void Smiley(char x, char y){

char x1 = x; //sparar temp värden för startpositionen dvs mitten
char y1 = y;

x = x - 5; //flyttar startpositionen till vänster hörna
y = y - 5; 

setPixel(x + 4, y + 0);
setPixel(x + 5, y + 0);
setPixel(x + 6, y + 0);
setPixel(x + 7, y + 0);
setPixel(x + 2, y + 1);
setPixel(x + 3, y + 1);
setPixel(x + 8, y + 1);
setPixel(x + 9, y + 1);
setPixel(x + 1, y + 2);
setPixel(x + 2, y + 2);
setPixel(x + 9, y + 2);
setPixel(x + 10, y + 2);
setPixel(x + 1, y + 3);
setPixel(x + 2, y + 3);
setPixel(x + 3, y + 3);
setPixel(x + 4, y + 3);
setPixel(x + 5, y + 3);
setPixel(x + 6, y + 3);
setPixel(x + 7, y + 3);
setPixel(x + 8, y + 3);
setPixel(x + 9, y + 3);
setPixel(x + 10, y + 3);
setPixel(x + 0, y + 4);
setPixel(x + 2, y + 4);
setPixel(x + 3, y + 4);
setPixel(x + 4, y + 4);
setPixel(x + 6, y + 4);
setPixel(x + 7, y + 4);
setPixel(x + 8, y + 4);
setPixel(x + 10, y + 4);
setPixel(x + 0, y + 5);
setPixel(x + 2, y + 5);
setPixel(x + 3, y + 5);
setPixel(x + 6, y + 5);
setPixel(x + 7, y + 5);
setPixel(x + 10, y + 5);
setPixel(x + 0, y + 6);
setPixel(x + 10, y + 6);
setPixel(x + 0, y + 7);
setPixel(x + 7, y + 7);
setPixel(x + 10, y + 7);
setPixel(x + 1, y + 8);
setPixel(x + 4, y + 8);
setPixel(x + 5, y + 8);
setPixel(x + 6, y + 8);
setPixel(x + 9, y + 8);
setPixel(x + 1, y + 9);
setPixel(x + 2, y + 9);
setPixel(x + 8, y + 9);
setPixel(x + 9, y + 9);
setPixel(x + 2, y + 10);
setPixel(x + 3, y + 10);
setPixel(x + 4, y + 10);
setPixel(x + 5, y + 10);
setPixel(x + 6, y + 10);
setPixel(x + 7, y + 10);
setPixel(x + 8, y + 10);



Draw();

x = x1;
y = y1;


}

void PositionBlink(char x, char y){		//Gör att en 5x5 fyrkant blinkar

char x1 = x; //sparar temp värden för startpositionen dvs mitten
char y1 = y;

x = x - 2; //flyttar startpositionen till vänster hörna
y = y - 2; 

for(int i=0;i<5;i++){		//rad
	for(int j=0;j<5;j++){	//kolumn

	setPixel(x + i, y + j);

	}
}

Draw();

x = x1;
y = y1;

_delay_ms(500);

removePixels(x, y);

}


void kort_som_ska_ritas(int count, int x, int y) {
switch (count)
​           {
            case count 1:
           Smiley(x, y):
            break;

            case count 2:
            Bunny(x, y);
           break;

           case count 3:
            Heart(x, y);
           break;


          case count 4:
            Ghost(x, y);
           break;


          default:
          // default statements
            }

}



void drawField(){
char display[64][128];
  for(char y = 0; y < 64; y++){
    for(char x = 0; x < 128; x++){
    
      if(y == 0){
      //rita en linje från (0,0) till (0,128)
      setPixel(x,y);

      }
      if(y == 31){
      //rita en linje från (0,31) till (128,31)
      setPixel(x,y);
      }
      if(y == 63){
      //rita en linje från (0,63) till (128,63)
      setPixel(x,y);
      }
      if(x == 0){
      //rita en linje från (0,0) till (0,64)
      setPixel(x,y);
      }
      if(x == 31){
      //rita en linje från (31,0) till (31,64)
      setPixel(x,y);
      }
      if(x == 63){
      //rita en linje från (63,0) till (63,64) 
      setPixel(x,y);
      }
      if(x == 95){
      //rita en linje från (95,0) till (95,64) 
      setPixel(x,y);
      }
      if(y == 127){
      //rita en linje från (127,0) till (127,64) 
      setPixel(x,y);
      }
      Draw();

    }
  }






}
