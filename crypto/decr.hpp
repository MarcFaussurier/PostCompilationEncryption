#pragma once

unsigned char    decr(unsigned char byte, unsigned i)
{
  int r = byte ^ 420 * i;
  return (( r + 7 - i));
}