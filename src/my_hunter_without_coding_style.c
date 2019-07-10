/*
** EPITECH PROJECT, 2018
** my_hunter
** File description:
** shot the duck
*/
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>

int my_put_nbr(int nb);
int my_putchar(char c);
int my_putstr(char const *str);
char *int_to_string(int nb);


void my_hunter_info(void)
{
    my_putstr("USAGE\n        ./my_hunter\n\n");
    my_putstr("DESCRIPTION\n        Shoot the duck\n");
    my_putstr("        Click on the duck to increase your score\n");
    my_putstr("        If you miss 6 times, you loose\n\n");
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
        my_hunter_info();
        return (0);
    }
    int offset = 0;
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;

    sfClock *time = sfClock_create();
    sfClock *clock;
    clock = sfClock_create();

    sfTexture* texture_bg;
    sfSprite* sprite;


    sfTexture* texture_duck;
    sfSprite* duck;

    sfTexture* texture_bullet;
    sfSprite* bullet;

    sfTexture* texture_start;
    sfSprite* start;

    sfEvent event;

    sfFont *font;
    sfText *text;

    font = sfFont_createFromFile("sprite/police.TTF");
    text = sfText_create();

    sfFont *font2;
    sfText *text2;

    font2 = sfFont_createFromFile("sprite/police.TTF");
    text2 = sfText_create();

    sfFont *font3;
    sfText *text3;

    font3 = sfFont_createFromFile("sprite/police.TTF");
    text3 = sfText_create();

    sfFont *font4;
    sfText *text4;

    font4 = sfFont_createFromFile("sprite/police.TTF");
    text4 = sfText_create();

    window = sfRenderWindow_create(mode, "window", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);

    texture_bg = sfTexture_createFromFile("sprite/stage.png", NULL);
    texture_duck = sfTexture_createFromFile("sprite/duck.png", NULL);
    texture_bullet = sfTexture_createFromFile("sprite/bullet.png", NULL);
    texture_start = sfTexture_createFromFile("sprite/header-main.png", NULL);

    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture_bg, sfTrue);

    duck = sfSprite_create();
    sfSprite_setTexture(duck, texture_duck, sfTrue);
    sfSprite_setScale(duck, (sfVector2f){0.6, 0.6});
    sfSprite_setPosition(duck, (sfVector2f){-100, 50});

    bullet = sfSprite_create();
    sfSprite_setTexture(bullet, texture_bullet, sfTrue);
    sfSprite_setPosition(bullet, (sfVector2f){10, 0});
    sfSprite_setScale(bullet, (sfVector2f){0.06, 0.06});

    start = sfSprite_create();
    sfSprite_setTexture(start, texture_start, sfTrue);
    sfSprite_setPosition(start, (sfVector2f){115, 185});
    sfSprite_setScale(start, (sfVector2f){0.5, 0.5});

    int score = 0;
    int miss = 6;
    int i = 0;
    int k = 0;

    sfText_setString(text4, "START");
    sfText_setFont(text4, font4);
    sfText_setCharacterSize(text4, 100);
    sfText_setPosition(text4, (sfVector2f){150, 200});

    while (sfRenderWindow_isOpen(window)) {
        sfText_setString(text, "Score : ");
        sfText_setFont(text, font);
        sfText_setCharacterSize(text, 20);
        sfText_setPosition(text, (sfVector2f){600, 30});

        sfText_setString(text2, int_to_string(score));
        sfText_setFont(text2, font2);
        sfText_setCharacterSize(text2, 20);
        sfText_setPosition(text2, (sfVector2f){720, 30});

        sfText_setString(text3, "YOU LOSE");
        sfText_setFont(text3, font3);
        sfText_setCharacterSize(text3, 50);
        sfText_setPosition(text3, (sfVector2f){200, 200});

    	while (sfRenderWindow_pollEvent(window, &event)) {
            int mouse_x = event.mouseButton.x;
            int mouse_y = event.mouseButton.y;
            int duck_x = sfSprite_getPosition(duck).x;
            int duck_y = sfSprite_getPosition(duck).y;
            int duck_height = sfSprite_getGlobalBounds(duck).height;
            int duck_width = sfSprite_getGlobalBounds(duck).width;
            int start_x = sfText_getPosition(text4).x;
            int start_y = sfText_getPosition(text4).y;
            int start_height = sfText_getGlobalBounds(text4).height;
            int start_width = sfText_getGlobalBounds(text4).width;
            switch (event.type) {
                case sfEvtClosed :
                    sfRenderWindow_close(window);
                    break;
                case sfEvtMouseButtonPressed :
                    if (mouse_x > duck_x && mouse_x < duck_x + duck_width
                    && mouse_y > duck_y && mouse_y < duck_y + duck_width) {
                        float rdm = rand() % (500 - 50) + 50;
                        sfSprite_setPosition(duck, (sfVector2f){-110, rdm});
                        score++;
                    }
                    else
                        miss = miss - 1;
                    if (miss == 0) {
                        sfRenderWindow_drawText(window, text3, NULL);
                    }
                    if (mouse_x > start_x && mouse_x < start_x + start_width
                    && mouse_y > start_y && mouse_y < start_y + start_width) {
                        k++;
                        miss++;
                        sfSprite_setPosition(start, (sfVector2f){-1, -1000});
                        sfText_setPosition(text4, (sfVector2f){-1000, -1000});
                    }
                    break;
            }
        }

        sfRenderWindow_clear(window, sfBlack);

        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfRenderWindow_drawSprite(window, duck, NULL);
        sfRenderWindow_drawSprite(window, start, NULL);
        for (int i = 0; i < miss; i++) {
            sfRenderWindow_drawSprite(window, bullet, NULL);
            sfSprite_setPosition(bullet, (sfVector2f){10 + i * 50, 10});
        }
        sfRenderWindow_drawText(window, text4, NULL);
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_drawText(window, text2, NULL);
        if (miss == 0) {
            sfSprite_setPosition(duck, (sfVector2f){-110, -110});
            sfRenderWindow_drawText(window, text3, NULL);
            sfText_move(text, (sfVector2f){-1000, -100});
            sfText_move(text2, (sfVector2f){-1000, -1000});
            sfText_setPosition(text, (sfVector2f){260, 270});
            sfText_setPosition(text2, (sfVector2f){480, 270});
            sfText_setCharacterSize(text, 35);
            sfText_setCharacterSize(text2, 35);
            sfRenderWindow_drawText(window, text, NULL);
            sfRenderWindow_drawText(window, text2, NULL);
        }

        if (miss == -1) {
            sfRenderWindow_close(window);
            main(ac, av);
        }
        if (k == 1)
            if (sfTime_asMilliseconds(sfClock_getElapsedTime(time)) > 10) {
    	        sfClock_restart(time);
    	        sfSprite_move(duck, (sfVector2f){1 + score, 0});
        }
        if (offset >= 330)
            offset = 0;
        if (sfTime_asMilliseconds(sfClock_getElapsedTime(clock)) > 100) {
            sfClock_restart(clock);
            sfSprite_setTextureRect(duck, (sfIntRect){offset, 0, 110, 110});
            offset = offset + 110;
        }
        if (sfSprite_getPosition(duck).x > 800) {
            float rand_nbr = rand() % (500 + 1);
            sfSprite_setPosition(duck, (sfVector2f){-110, rand_nbr});
        }
        sfRenderWindow_display(window);
    }
}