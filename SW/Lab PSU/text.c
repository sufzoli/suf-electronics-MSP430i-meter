/*
 * text.c
 *
 *  Created on: 2017. febr. 7.
 *      Author: zoli
 */

const unsigned char hex[] = "0123456789ABCDEF";

unsigned int hex2uint(volatile unsigned char value[])
{
    unsigned char i;
    unsigned int retvalue;
    retvalue = 0;
    for(i=0;value[i]>0;i++)
    {
        // shift left by 4
        retvalue <<= 4;
        // we accept only capital letters in the hex numbers and don't check if the number valid
        // if the charcode > 57 (9) decrease by 55 (A code 65 - 10 as the A value), if smaller or equal decrease by 48 (0 code)
        retvalue |= value[i] - ((value[i]>57)?55:48);
    }
    return retvalue;
}
