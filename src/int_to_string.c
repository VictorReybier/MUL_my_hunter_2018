/*
** EPITECH PROJECT, 2018
** int to string
** File description:
** convert a int into a char
*/
#include <stdlib.h>

int my_putstr(char const *str);

char *int_to_string(int nb)
{
    int pow = 1;
    int nbcpy = nb;
    char *buffer = malloc(sizeof(char) * 4);
    int i = 0;
    while (nbcpy > 9) {
        pow = pow * 10;
        nbcpy = nbcpy / 10;
    }
    while (nb > 9) {
        buffer[i] = nb / pow + 48;
        nb = nb % pow;
        pow = pow / 10;
        i++;
    }
    buffer[i] = nb + 48;
    buffer[i + 1] = '\0';
    return (buffer);
}