#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

// Array

#define arr_size(arr) (sizeof((arr)) / sizeof(((arr)[0])))

// Sean Barret Style Strechy Buffers

typedef struct strechy_buffer_t
{
    size_t len;
    size_t cap;
    uint8_t data[0];
} strechy_buffer_t;

#define sb_check_needs_grow(buff, n) (sb_len(buff) + (n) <= sb_cap(buff))
#define sb_maybe_grow(buff, n)       (sb_check_needs_grow(buff, n) ? 0 : ((buff) = __sb_grow((buff), sb_len(buff) + (n), sizeof(*(buff)))))

#define sb_push(buff, val)           (sb_maybe_grow(buff, 1), (buff)[sb_len(buff)] = (val), sb_meta_data(buff)->len++)
#define sb_free(buff)                ((buff) ? free(sb_meta_data(buff)) : 0)
#define sb_pop(buff)                 ((sb_meta_data(buff)->len > 0) ? sb_meta_data(buff)->len-- : 0)

#define sb_meta_data(buff)           ((strechy_buffer_t *)((uint8_t *)buff - offsetof(strechy_buffer_t, data)))
#define sb_len(buff)                 ((buff) ? sb_meta_data(buff)->len : 0)
#define sb_cap(buff)                 ((buff) ? sb_meta_data(buff)->cap : 0)

static inline void *__sb_grow(void *buff, size_t increment, size_t item_size)
{
    uint32_t double_cap = buff ? (2 * sb_cap(buff)) : 0;
    uint32_t min_needed = sb_cap(buff) + increment;
    uint32_t new_cap = (double_cap > min_needed) ? double_cap : min_needed;

    strechy_buffer_t *new_buff;
    if (buff)
    {
        new_buff = (strechy_buffer_t *)realloc(
            sb_meta_data(buff), item_size * new_cap + offsetof(strechy_buffer_t, data));
    }
    else
    {
        new_buff = (strechy_buffer_t *)malloc(
            item_size * new_cap + offsetof(strechy_buffer_t, data));
        new_buff->len = 0;
    }

    if (!new_buff)
    {
        perror("__sb_grow allocation failed");
        exit(1);
    }

    new_buff->cap = new_cap;
    return new_buff->data;
}

#endif // UTIL_H
