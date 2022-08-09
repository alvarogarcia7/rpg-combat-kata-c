#include <stdint.h>

typedef struct character {
    uint16_t health;
    uint8_t level;
} character;

void init_character(character *character);