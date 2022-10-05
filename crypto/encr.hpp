#pragma once

unsigned char    encr(unsigned char byte, unsigned i)
{
     return (( byte   - 7 + i) ^ (420 * i));
}