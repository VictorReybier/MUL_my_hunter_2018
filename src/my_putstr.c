/*
** EPITECH PROJECT, 2018
** my_putstr.c
** File description:
** Display the characters of a string
*/
int my_putchar(char c);

int my_putstr(char const *str)
{ 
    if (*str == '\0')
        return (0);
    my_putchar(*str);
    return (my_putstr(str + 1));
}
