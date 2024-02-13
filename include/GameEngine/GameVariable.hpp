/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** TypeEnum
*/

#ifndef TYPEENUM_HPP_
#define TYPEENUM_HPP_

#define SHOOT_SOUND "./assets/Sound/shoot.ogg"
#define BACKGROUND_GAME "./assets/Game/background_game.jpg"
#define BACKGROUND_MENU "./assets/Menu/background.jpg"
#define WAITING_SCREEN "./assets/Menu/waitingScreen.png"
#define FONT_FAMILY "./assets/Utilities/yagora.ttf"
#define SPACESHIP "./assets/Game/sprites/spaceship.gif"
#define SHADER "./assets/Utilities/shader.vert"
#define SHOOT "./assets/Game/sprites/shoot.gif"
#define SHOOT_2 "./assets/Game/sprites/shoot2.gif"
#define ENEMY_1 "./assets/Game/sprites/enemy1.gif"
#define ENEMY_2 "./assets/Game/sprites/enemy2.gif"
#define MUSIC_GAME "./assets/Sound/mainTheme.wav"
#define EXPLOSION_SOUND "./assets/Sound/explosion.wav"
#define BONUS_SOUND "./assets/Sound/bonus.wav"
#define BONUS_1 "./assets/Game/sprites/bonus.gif"
#define PLAYER_DEATH_SOUND "./assets/Sound/player_death.wav"
#define EXPLOSION_1 "./assets/Game/sprites/explosion.gif"

// #define _GAME "./assets/Sound/mainTheme.wav"

enum ObjectType:int {
  BUTTONS = 1,
  ICONS = 2,
  BACKGROUND = 3,
  TEXT = 4,
};

enum EntityType {
    PLAYER = 1,
    OBSTACLE = 2,
    BULLET = 3,
    ITEM = 4,
    MOB = 5,
    EXPLOSION = 6,
    WEAPON = 7,
    VOID = 0,
};

enum MenuType {
  PLAY = 1,
  SETTINGS = 2,
  EXIT = 3,
};

enum Control {
  UP = 1,
  DOWN = 2,
  LEFT = 3,
  RIGHT = 4,
  SPACE = 5,
  NONE = 0,
};

enum ShootType {
  BASIC = 1,
  BOMB = 2,
  LASER = 3,
  NO_SHOOT = 0,
};

enum TeamType {
  ALLY = 1,
  ENEMY = 2,
  NO_TEAM = 0,
};

#endif
