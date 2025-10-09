
#include <stdio.h>
#include <math.h>
#define MAX 100
long long Fosc = 0;
// TIMER
int prescalerTIMER0[8] = {2, 4, 8, 16, 32 , 64, 128, 256};
int prescalerTIMER1[4] = {1, 2, 4, 8};
int prescalerTIMER2[3] = {1, 4, 16};
int postscalerTIMER2[3] = {1, 2, 16};
double delaywanted = 0;
long long tick_needed = 0;
// PWM
long long F_PWM = 0;
int Duty_Cycle = 0;
// Oscillator
long long osc_cycles_per_PWM = 0;



void Get_Fosc()
{
    printf("Enter the frequensy of your PIC:");
    scanf("%lld", &Fosc);

    printf("Fosc: %lld\n", Fosc);
}

void Get_F_PWM_and_Duty_Cycle()
{
    printf("Enter the frequensy of PWM:");
    scanf("%lld", &F_PWM);
    printf("Enter your Duty Cycle:");
    scanf("%d", &Duty_Cycle);

    printf("F_PWM: %lld | Duty_Cycle: %d\n", F_PWM, Duty_Cycle);
}

void Get_delay_wanted()
{
    printf("Enter the timer of delay you wanted:");
    scanf("%lf", &delaywanted);

    int delaychoice = 0;
    printf("Enter your kind of DELAY:\n");
    printf("0. Half Delay: ON - OFF\n");
    printf("1. Full Delay: ON - OFF - ON\n");
    printf("[0-1]:");
    scanf("%d", &delaychoice);
    if ( delaychoice )
    {
        delaywanted = delaywanted / 2;
    }

}

void Choose_Unit()
{
    int unit = 0;
    printf("Choose the unit of measurement:\n");
    printf("1.us\n");
    printf("2.ms\n");
    printf("3.s\n");
    printf("[1-3]:");
    scanf("%d", &unit);
    switch(unit)
    {
        case 1:
        {
            delaywanted = delaywanted * pow(10, -6); 
            break;
        }
        case 2:
        {

            delaywanted = delaywanted * pow(10, -3);
            break;
        } 
        case 3: break;
        default:
        {
            printf("Choose is invalid");
            break;
        } 
    }


}


int Chooce_Prescaler(int* arr, int n)
{
    int choice;
    for(int i = 0; i < n; i++ )
    {
        printf("i: %d | %d \n",i , arr[i]);
    }
    printf("Choose your option[0-%d]:", n - 1);
    scanf("%d", &choice);
    return choice;
}

int Chooce_Postscaler(int* arr, int n)
{
    int choice;
    for(int i = 0; i < n; i++ )
    {
        printf("i: %d | %d \n",i , arr[i]);
    }
    printf("Choose your option[0-%d]:", n - 1);
    scanf("%d", &choice);
    return choice;
}


void TIMER0_check(long long tick_needed, int prescalerTIMER0[], int i)
{
    for( int TMR0 = 0; TMR0 < 256 ; TMR0++ )
    {
        long long tick_overload0 = ( 256 - TMR0 ) * prescalerTIMER0[i];
        int x = (int)(tick_needed / tick_overload0);
        printf("x = %d  | TMR0 = %d | Lost: %lld \n", x, TMR0, tick_needed % tick_overload0);
    }
}


void TIMER1_check(long long tick_needed, int prescalerTIMER1[], int i)
{
    for( int TMR1 = 0; TMR1 < 65536 ; TMR1++ )
    {
        long long tick_overload1 = ( 65536 - TMR1 ) * prescalerTIMER1[i];
        int x = (int)(tick_needed / tick_overload1);
        printf("x = %d  | TMR1 = %d | Lost: %lld \n", x, TMR1, tick_needed % tick_overload1);
    }
}


void TIMER2_check(long long tick_needed, int prescalerTIMER2[], int postcalerTIMER2[], int i, int j)
{
    int PR2 = ( tick_needed / prescalerTIMER2[i] / postscalerTIMER2[i] ) - 1;
    printf("PR2: %d", PR2);
}

void TIMER2_PWM_check(long long osc_cycles_per_PWM, int prescalerTIMER2[], int i)
{
    // ( PR2 + 1 ) : Timer2 counts per cycle
    // ( PR2 + 1 ) * 4 : Oscillator cycles per TIMER2 cycles
    // Fosc / F_PWM : Oscillator cycles per PWM cycles
    int osc_cycles_per_TIMER2_cycles = osc_cycles_per_PWM / prescalerTIMER2[i];
    int PR2 = round(osc_cycles_per_TIMER2_cycles / 4) - 1;

    // DutyCycle =  ( ( CCPRxL : DCxB ) / ( PR2 + 1 ) * 4 ) * 100 %
    int Duty_pulse_size = round(osc_cycles_per_TIMER2_cycles * Duty_Cycle / 100);
    printf("PR2: %d | CCPR1L:CCP1CON<5:4>: %d", PR2, Duty_pulse_size);

}

void Get_TIMER_Option()
{
    int TMROPTION = 0;
    do {
    printf("Choose the option of TIMER:\n");
    printf("1. TIMER0\n");
    printf("2. TIMER1\n");
    printf("3. TIMER2\n");
    printf("[1-3]:");
    scanf("%d", &TMROPTION );
    switch(TMROPTION)
      {
        case 1:
        {
            printf("Choose prescaler on TIMER0:\n");
            int i = Chooce_Prescaler(prescalerTIMER0, 8);
            TIMER0_check(tick_needed, prescalerTIMER0, i);
            break;
        }
        case 2:
        {
            printf("Choose prescaler on TIMER1:\n");
            int i = Chooce_Prescaler(prescalerTIMER1, 4);
            TIMER1_check(tick_needed, prescalerTIMER1, i);
            break;
        }
        case 3:
        {
            printf("Choose prescaler on TIMER2:\n");
            int i = Chooce_Prescaler(prescalerTIMER2, 3);
            int j = Chooce_Postscaler(postscalerTIMER2, 3);

            TIMER2_check(tick_needed, prescalerTIMER2, postscalerTIMER2, i, j);
            break;
        }
        case 0:
        {
            return;
        }
        default:
        {
            printf("Invalid Choice\n");
            break;
        }
      }
    }
    while(1); 
}

int main(void) {
    // Choose Fosc
    Get_Fosc();

    int mode = -1;
    printf("Choose your mode:\n");
    printf("1.TIMER\n");
    printf("2.PWM\n");
    printf("[0-1]:");
    scanf("%d",&mode);
    switch(mode)
    {
        case 1:
        {
            // Write the delay you want
            Get_delay_wanted();
    
            // Choose the unit
            Choose_Unit();

            // Result of delay
            printf("Delay wanted : %lf\n", delaywanted);

            // Calculate tick_needed
            tick_needed = (long long)round(delaywanted * Fosc / 4);
            printf("Time of tick_needed : %lld\n", tick_needed);
    
            // Choose TIMER Option
            Get_TIMER_Option();
        }
        break;
        case 2:
        {
            // Write FPWM you want
            // Write your Duty Cycle
            Get_F_PWM_and_Duty_Cycle();

            // Calculate tick_needed
            osc_cycles_per_PWM = round( Fosc /  F_PWM  );
            printf("Oscillator cycles PWM needed: %lld\n", osc_cycles_per_PWM);
            
            printf("Choose prescaler on TIMER2:\n");
            int i = Chooce_Prescaler(prescalerTIMER2, 3);
            // Calculate PR2 and CCPR1L:CCP1CON<5:4>
            TIMER2_PWM_check(osc_cycles_per_PWM, prescalerTIMER2, i);

        }
        break;
        case 0:
        {
            return 0;
        }

        default:
        {
            printf("Invalid mode\n");
            break;
        }
    
    }

    return 0;
}