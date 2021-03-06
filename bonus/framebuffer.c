/*
** EPITECH PROJECT, 2019
** my_sreensaver_2019
** File description:
** framebuffer
*/

#include "framebuffer.h"

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *buffer = malloc(sizeof(framebuffer_t));

    if (buffer == NULL)
        return (NULL);
    buffer->width = width;
    buffer->height = height;
    buffer->pixels = malloc(sizeof(sfUint8) * (width * height * 4));
    if (buffer->pixels == NULL)
        return (NULL);
    for (unsigned int i = 0; i < (width * height * 4); i++)
        buffer->pixels[i] = 0;
    buffer->texture = sfTexture_create(buffer->width, buffer->height);
    buffer->sprite = sfSprite_create();
    if (buffer->texture == NULL || buffer->sprite == NULL)
        return NULL;
    return (buffer);
}

void framebuffer_destroy(framebuffer_t *buffer)
{
    if (buffer == NULL)
        return;
    free(buffer->pixels);
    sfSprite_destroy(buffer->sprite);
    sfTexture_destroy(buffer->texture);
    free(buffer);
}

void display_framebuffer(framebuffer_t *fb, sfRenderWindow *w)
{
    sfTexture *txr = fb->texture;

    sfTexture_updateFromPixels(txr, fb->pixels, fb->width, fb->height, 0, 0);
    sfSprite_setTexture(fb->sprite, fb->texture, sfFalse);
    sfRenderWindow_drawSprite(w, fb->sprite, NULL);
    sfRenderWindow_display(w);
}

int put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y,
sfColor *color)
{
    int indexpix = (y * (framebuffer->width * 4)) + (x * 4);

    if (x < framebuffer->width && y < framebuffer->height) {
        framebuffer->pixels[0 + indexpix] = color->r;
        framebuffer->pixels[1 + indexpix] = color->g;
        framebuffer->pixels[2 + indexpix] = color->b;
        framebuffer->pixels[3 + indexpix] = color->a;
    }
    return 0;
}
