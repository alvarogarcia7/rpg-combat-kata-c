#include "prod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_character(character *character) {
    character->health = 1000;
    character->level = 1;
}

void character_receive_damage(character *character, damage_t damage){
    character->health -= damage;
}

bool character_is_dead(const character *character){
    return character->health == 0;
}
