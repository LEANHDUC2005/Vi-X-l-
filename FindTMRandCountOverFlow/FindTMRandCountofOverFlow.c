
#include <stdio.h>
#include <math.h>
#define MAX 100
const long long Fosc = 20000000;
int prescalerTIMER0[8] = {2, 4, 8, 16, 32 , 64, 128, 256};
int prescalerTIMER1[4] = {1, 2, 4, 8};
int prescalerTIMER2[3] = {1, 4, 16};
int postcalerTIMER2[3] = {1, 2, 16};

int choiceprescal(int* arr, int n)
{
    int choice;
    for(int i = 0; i < n; i++ )
    {
        printf("i: %d | %d \n",i , arr[i]);
    }
    printf("Choose your option[0-1]:");
    scanf("%d", &choice);
    return choice;
}


void TIMER0check(int tick_needed, int prescalerTIMER0[], int i)
{
    for( int TMR0 = 0; TMR0 < 256 ; TMR0++ )
    {
        long long tick_overload0 = ( 256 - TMR0 ) * prescalerTIMER0[i];

        if ( tick_needed % tick_overload0 < 1e-5 )
        {
            int x = (int)(tick_needed / tick_overload0);
            printf("x = %d  | TMR0 = %d | Lost: %lld \n", x, TMR0, tick_needed % tick_overload0);
        }

    }
}


void TIMER1check(int tick_needed, int prescalerTIMER1[], int i)
{
    for( int TMR1 = 0; TMR1 < 65536 ; TMR1++ )
    {
        long long tick_overload1 = ( 65536 - TMR1 ) * prescalerTIMER1[i];

        if ( tick_needed % tick_overload1 < 1e-5 )
        {
            int x = (int)(tick_needed / tick_overload1);
            printf("x = %d  | TMR1 = %d | Lost: %lld \n", x, TMR1, tick_needed % tick_overload1);
        }

    }
}


void TIMER2check(int tick_needed, int prescalerTIMER2[], int postcalerTIMER2[], int i, int j);



int main(void) {
    
    double delaywanted;
    int unit;
    int delaychoice;
    
    printf("Enter the timer of delay you wanted:");
    scanf("%lf", &delaywanted);

    printf("Enter your kind of DELAY:\n");
    printf("0. Half Delay: ON - OFF\n");
    printf("1. Full Delay: ON - OFF - ON\n");
    printf("[0-1]:");
    scanf("%d", &delaychoice);
    if ( delaychoice )
    {
        delaywanted = delaywanted / 2;
    }

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
    
    printf("Delay wanted : %lf\n", delaywanted);
    
    long long tick_needed = (long long)(delaywanted * Fosc / 4);
    
    int TMROPTION;
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
            int i = choiceprescal(prescalerTIMER0, 8);
            TIMER0check(tick_needed, prescalerTIMER0, i);
            break;
        }
        case 2:
        {
            int i = choiceprescal(prescalerTIMER1, 4);
            TIMER1check(tick_needed, prescalerTIMER1, i);
            break;
        }
        case 3:
        {
            //TIMER2check(tick_needed, pre);
            break;
        }
        default:
        {
            return 0;
        }
    }


    }
    while(1);
    return 0;
}