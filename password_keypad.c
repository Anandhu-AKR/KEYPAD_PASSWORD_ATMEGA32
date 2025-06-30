#include <avr/io.h>
#include <util/delay.h>

void command(char a);
void data(char a);
void display(const char *p);
char pass;
void forward();
void reverse();
void stop();

int main()
{ 
DDRC=0XFF;
DDRB=0X0F;
DDRD=0XFF;
DDRA=0XFF;


command(0X38);
command(0X80);
command(0X01);
command(0X06);
command(0X0F);

display("ENTER PASSWORD:");
_delay_ms(3000);



command(0X01);

char pass[2] = "123";  
    char input[2];  
    int index = 0;  
    int is_correct = 1;

while(1)
{
PORTB=0X0E;//FIRST ROW
if((PINB&0x10)==0)
{
input[index++] = '1';
data('1');

while((PINB&0x10)==0);
}
if((PINB&0x20)==0)
{
    input[index++] = '2';
data('2');

while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
    input[index++] = '3';
data('3');

while((PINB&0x40)==0);
}
if((PINB&0x80)==0)
{
data('+');
while((PINB&0x80)==0);
}
PORTB=0X0D;//SECOND ROW
if((PINB&0x10)==0)
{
data('4');
while((PINB&0x10)==0);
}
if((PINB&0X20)==0)
{
data('5');
while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
data('6');
while((PINB&0X40)==0);
}
if((PINB&0x80)==0)
{
data('-');
while((PINB&0x80)==0);
}
PORTB=0X0B;//THIRD ROW
if((PINB&0x10)==0)
{
data('7');
while((PINB&0x10)==0);
}
if((PINB&0x20)==0)
{
data('8');
while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
data('9');
while((PINB&0x40)==0);
}
if((PINB&0x80)==0)
{
data('*');
while((PINB&0x80)==0);
}
PORTB=0X07;//FOURTH ROW
if((PINB&0x10)==0)
{
command(0X01);
}
if((PINB&0x20)==0)
{
data('0');
while((PINB&0x20)==0);
}
if((PINB&0x40)==0)
{
data('=');
while((PINB&0x40)==0);
}
if((PINB&0x80)==0)
{
data('/');
while((PINB&0x80)==0);
}

if (index == 3  ) {
            
            for (int i = 0; i <=2; i++) {
                if (input[i] != pass[i]) {
                    is_correct = 0;  // Password incorrect
                    break;
                }
            }

            
            command(0x01);  
            command(0x80);  

            if (is_correct) {
                command(0X01);
                display("GRANTED");
                
                forward();
                _delay_ms(3000);
                stop();
                
            } 
            else{
                display("DENIED");
                _delay_ms(2000);
            }
            
            
            

            _delay_ms(2000);  
            command(0x01);  
            index = 0;  
            is_correct = 1;  
        }

}
    
    
    
}

void command (char a)
{
PORTC=0x02;
PORTD=a;
_delay_ms(100);
PORTC=0x00;
}
void data(char a)
{
PORTC=0x03;
PORTD=a;
_delay_ms(100);
PORTC=0x01;
}

void display(const char *p){
    while(*p != 0) {
        data(*p);
        p++;
    }
}

void forward(){
    PORTA = 0x1D;
}

void reverse(){
    PORTA = 0x2E;
}

void stop(){
    PORTA = 0x00;
}