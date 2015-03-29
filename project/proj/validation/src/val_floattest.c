#include <string.h>
#include "uartstdio.h"
#include "sleep.h"
#include <stdlib.h>
#include "sysCalls.h"
#include <limits.h>
#include <math.h>

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    //reverse the order
    int len = strlen(s);
    for (i = 0; i < len/2; ++i){
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    } 
}

void ftoa(float Value, char* Buffer)
 {
     union
     {
         float f;
     
         struct
         {
             unsigned int    mantissa_lo : 16;
             unsigned int    mantissa_hi : 7;    
             unsigned int     exponent : 8;
             unsigned int     sign : 1;
         };
     } helper;
     
     unsigned long mantissa;
     signed char exponent;
     unsigned int int_part;
     char frac_part[3];
     int i, count = 0;
     
     helper.f = Value;
     //mantissa is LS 23 bits
     mantissa = helper.mantissa_lo;
     mantissa += ((unsigned long) helper.mantissa_hi << 16);
     //add the 24th bit to get 1.mmmm^eeee format
     mantissa += 0x00800000;
     //exponent is biased by 127
     exponent = (signed char) helper.exponent - 127;
     
     //too big to shove into 8 chars
     if (exponent > 18)
     {
         Buffer[0] = 'I';
         Buffer[1] = 'n';
         Buffer[2] = 'f';
         Buffer[3] = '\0';
         return;
     }
     
     //too small to resolve (resolution of 1/8)
     if (exponent < -3)
     {
         Buffer[0] = '0';
         Buffer[1] = '\0';
         return;
     }
     
     count = 0;
     
     //add negative sign (if applicable)
     if (helper.sign)
     {
         Buffer[0] = '-';
         count++;
     }
     
     //get the integer part
     int_part = mantissa >> (23 - exponent);    
     //convert to string
     itoa(int_part, &Buffer[count]);
     
     //find the end of the integer
     for (i = 0; i < 8; i++)
         if (Buffer[i] == '\0')
         {
             count = i;
             break;
         }        
 
     //not enough room in the buffer for the frac part    
     if (count > 5)
         return;
     
     //add the decimal point    
     Buffer[count++] = '.';
     
     //use switch to resolve the fractional part
     switch (0x7 & (mantissa  >> (20 - exponent)))
     {
         case 0:
             frac_part[0] = '0';
             frac_part[1] = '0';
             frac_part[2] = '0';
             break;
         case 1:
             frac_part[0] = '1';
             frac_part[1] = '2';
             frac_part[2] = '5';            
             break;
         case 2:
             frac_part[0] = '2';
             frac_part[1] = '5';
             frac_part[2] = '0';            
             break;
         case 3:
             frac_part[0] = '3';
             frac_part[1] = '7';
             frac_part[2] = '5';            
             break;
         case 4:
             frac_part[0] = '5';
             frac_part[1] = '0';
             frac_part[2] = '0';            
             break;
         case 5:
             frac_part[0] = '6';
             frac_part[1] = '2';
             frac_part[2] = '5';            
             break;
         case 6:
             frac_part[0] = '7';
             frac_part[1] = '5';
             frac_part[2] = '0';            
             break;
         case 7:
             frac_part[0] = '8';
             frac_part[1] = '7';
             frac_part[2] = '5';                    
             break;
     }
     
     //add the fractional part to the output string
     for (i = 0; i < 3; i++)
         if (count < 7)
             Buffer[count++] = frac_part[i];
     
     //make sure the output is terminated
     Buffer[count] = '\0';
 }

void testFloatOutputSmall(void){
    UARTprintf("Testing float output small...\r\n");
    char fPtr[100];
    char* fptr = fPtr;
    float f = 0.155;
    while(1){
        ftoa(f, fptr); 
        UARTprintf("[small]Float value of f: %s\r\n", fptr);
        f /= 0.22;
        ftoa(f, fptr); 
        UARTprintf("[small]Float value of f: %s\r\n", &fPtr);
        sleepMS(100);
        f *= 0.22;
        ftoa(f, fptr); 
        UARTprintf("[small]Float value of f: %s\r\n", &fPtr);
    }
}

void testFloatOutputBig(void){
    UARTprintf("Testing float output big...\r\n");
    char fPtr[100];
    char* fptr = fPtr;
    float f = 155.0;
    while(1){
        ftoa(f, fptr); 
        UARTprintf("[big]Float value of f: %s\r\n", fptr);
        f /= 0.22;
        ftoa(f, fptr); 
        sleepMS(100);
        UARTprintf("[big]Float value of f: %s\r\n", &fPtr);
        f *= 0.22;
        ftoa(f, fptr); 
        UARTprintf("[big]Float value of f: %s\r\n", &fPtr);
    }
}

#define UNUSED(x) (void)(x)

void findPrimeNumbers(void* amount){
    const unsigned maxCount = (unsigned) amount;
    if (maxCount != 0){
        unsigned curCount = 1; 
        UARTprintf("2");
        for (unsigned i = 3; i < UINT_MAX; i += 2){
            float sqrtIf = sqrtf(i);
            unsigned sqrtIu = (unsigned)sqrtIf;
            int isPrime = 1;
            for (unsigned j = 3; j <= sqrtIu; ++j){
                float out = (float)i / j;
                unsigned output = i / j;
                //get the diff
                if (out - output < 0.000244140625){
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime){
                curCount++;
                UARTprintf(", %u", i);
            }  
            if (curCount == maxCount) break;
        }

        UARTprintf(".\r\nDone!\r\n");
    }
    while(1) sleepS(1000);
}

void testFloatMain(void){
    //if (createProcess(512, "testFloatSmall", testFloatOutputSmall, NULL, 20) != 0){
    //    UARTprintf("My child did not spawn :(\r\n");
    //}
    //if (createProcess(512, "testFloatBig", findPrimeNumbers, (void*)203280221, 1) != 0){
    if (createProcess(512, "testFloatBig", findPrimeNumbers, (void*)5000, 1) != 0){
        UARTprintf("My child did not spawn :(\r\n");
    }
    while(1){
        sleepS(10);
    }
}
