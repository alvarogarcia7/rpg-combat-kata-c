#include "prod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fizzBuzz(int number)
{
    if (15 == number)
    {
        return "FizzBuzz";
    }
    if (5 == number)
    {
        return "Buzz";
    }
    return "Fizz";
}