// 'C' source line config statements
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 20000000UL
// Mã 7 ?o?n Anode chung (gfedcba)
const unsigned char ma7doan [10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int ma_tr, ma_ch, ma_dv;
// Gi?i mã s? ra 3 màn 7 ?o?n
void giaima_3so_xvn(uint8_t x) 
{
    ma_dv = ma7doan[x % 10];
    ma_ch = ma7doan[(x / 10) % 10];
    ma_tr = ma7doan[(x / 100) % 10];
    // T?t hàng tr?m và ch?c n?u b?ng 0
    if ((x / 100) == 0) ma_tr = 0xFF;
    if ((x / 10) == 0) ma_ch = 0xFF;
}
// Hi?n th? 3 ch? s?
void hienthi_3so_3port() {
    PORTD = ma_dv;
    PORTC = ma_ch;
    PORTB = ma_tr;
}
void main(void) {
// --- C?u hình PORT ---
    TRISB = 0x00; // Hàng tr?m
    TRISC = 0x00; // Hàng ch?c
    TRISD = 0x00; // Hàng ??n v?
    PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0xFF;
// --- C?u hình Timer0 ngo?i vi ---
    OPTION_REGbits.T0CS = 1; // Clock t? chân T0CKI (RA4)
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 1; // Không dùng prescaler
    TMR0 = 0;
    while(1) 
    {
        giaima_3so_xvn(TMR0); // Timer0 = 0->255
        hienthi_3so_3port();
    }
}