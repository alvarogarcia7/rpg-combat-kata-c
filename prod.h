#include <stdint.h>
#include <stdbool.h>

#define damage_t uint16_t

typedef struct character {
    uint16_t health;
    uint8_t level;
} character;

void init_character(character *character);

void character_receive_damage(character *character, damage_t damage);

bool character_is_dead(const character *character);