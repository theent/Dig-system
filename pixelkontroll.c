

void setPixel(char x, char y, int scale)

{
x *= scale;
y *= scale;

for (int i = 0; i < scale; i++)
{
for (int j = 0; j < scale; j++)
{
// ABS to compensates for upside-down display :)
char yDisplay = abs((y + i) - 63);
char xDisplay = abs((x + j) - 127);



virtual_display[yDisplay / 8][xDisplay] |= (1 << (yDisplay % 8));
}

}

}



void draw()
{


for (char cell = 0; cell < 8; cell++){

for (char x = 0; x < 128; x++){

waitForDisplay();

char displayX;

if (x < 64) {

waitForDisplay();

cs1high();

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




  
char display[8][128];

void bunny(char x, char y){

x = x - 5; 
y = y - 5; 






}


