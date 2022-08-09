#ifndef RPG_COMBAT_KATA_PROD_H
#define RPG_COMBAT_KATA_PROD_H

#include <stdint.h>
#include <stdbool.h>

#define damage_t uint16_t
#define heal_t uint16_t
#define level_up_t uint8_t

typedef struct character {
    uint16_t health;
    uint8_t level;
} character;

void character_init(character *character);

void character_receive_damage(character *character, damage_t damage);

void character_receive_healing(character *character, heal_t heal);

void character_level_up(character *character, level_up_t level_up);

bool character_is_dead(const character *character);

bool character_is_alive(const character *character);

void character_attack(const character *attacker, character *attackee);

#endif