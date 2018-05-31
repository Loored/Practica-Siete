#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, STVREN, NOLVP, NODEBUG,
#use delay (clock = 16000000)
#include <lcd420.c>
#define DHT11_pin PIN_A0

unsigned char values[5];
void DHT11_init();
unsigned char get_byte();
unsigned char get_data();
void setup();
void lcd_symbols();

void DHT11_init()
{
    output_float(DHT11_pin);
    delay_ms(1000);
}

void main()
{
    unsigned char estado = 0;
    setup();
    while(TRUE)
    {
        estado = get_data();
        switch(estado)
        {
            case 1:
            {
                
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            default:
            {
                
                break;
            }
        }
        delay_ms(1000);
    };
}
