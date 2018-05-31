#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, STVREN, NOLVP, NODEBUG,
#use delay (clock = 16000000)
#include <lcd420.c>
#define DHT11_pin PIN_A0

unsigned char valores[5];
void DHT11_init();
unsigned char obtenerByte();
unsigned char obtenerDatos();
void configuracionLCD();
void simbolosLCD();

const unsigned char simbolos[8]=
{
    0x07, 0x05, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00
};

void main()
{
    unsigned char estado = 0;
    configuracionLCD();
    while(TRUE)
    {
        estado = obtenerDatos();
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

void DHT11_init()
{
    output_float(DHT11_pin);
    delay_ms(1000);
}

unsigned char obtenerByte()
{
    unsigned char lectura = 0;
    unsigned char valor = 0;
    
    for(lectura = 0; lectura < 8; lectura+= 1)
    {
        valor <<= 1;
        while(!input(DHT11_pin));
        delay_us(30);
        
        if(input(DHT11_pin))
        {
            valor |= 1;
        }
        while(input(DHT11_pin));
    }
    return valor;
}

unsigned char obtenerDatos()
{
    short entrada = 0;
    unsigned char lectura = 0;
    unsigned char checksum = 0;
    
    output_high(DHT11_pin);
    output_low(DHT11_pin);
    delay_ms(18);
    output_high(DHT11_pin);
    delay_us(26);
    
    entrada = input(DHT11_pin);
    if(!entrada)
    {
        return 1;
    }
    delay_us(80);
    entrada = input(DHT11_pin);
    if(!entrada)
    {
        return 2;
    }
    delay_us(80);
    
    for(lectura = 0; lectura < 4; lectura+= 1)
    {
        valores[lectura] = obtenerByte();
    }
    output_high(DHT11_pin);
    for(lectura = 0; lectura < 4; lectura+= 1)
    {
        checksum += valores[lectura];
    }
    if(checksum != valores[4])
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

void configuracionLCD()
{
    disable_interrupts(GLOBAL);
    //port_B_pullups(FALSE);
    setup_timer_0(T0_INTERNAL); //| T0_8_bit);
    set_timer0(0);
    DHT11_init();
    lcd_init();
    lcd_putc("\f");
    simbolosLCD();
}

void simbolosLCD()
{
    unsigned char envio = 0;
    lcd_send_byte(0, 0x40);
    for(envio = 0; envio < 8; envio++)
    {
        lcd_send_byte(1, simbolos[envio]);
    }
    lcd_send_byte(0, 0x80);
}