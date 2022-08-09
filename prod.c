#include "prod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEALTH 1000
#define INITIAL_LEVEL 1

void character_init(character *character) {
    character->health = MAX_HEALTH;
    character->level = INITIAL_LEVEL;
}

void character_receive_damage(character *character, damage_t damage){
    uint16_t new_health = character->health - damage;
    if (damage > character->health){
        new_health = 0;
    }
    character->health = new_health;
}

bool character_is_dead(const character *character){
    return character->health == 0;
}

bool character_is_alive(const character *character){
    return !character_is_dead(character);
}

void character_receive_healing(character *character, heal_t heal) {
    uint16_t remaining_health_to_maximum = MAX_HEALTH - character->health;
    uint16_t result = character->health + heal;
    if (heal > remaining_health_to_maximum){
        result = MAX_HEALTH;
    }
    character->health = result;
}
