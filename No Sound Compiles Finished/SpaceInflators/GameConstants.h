#ifndef _GAMECONSTANTS_H_
#define _GAMECONSTANTS_H_

// IDs for the game objects

const int IID_PLAYER_SHIP      = 0;
const int IID_NACHLING         = 1;
const int IID_WEALTHY_NACHLING = 2;
const int IID_SMALLBOT         = 3;
const int IID_BULLET           = 4;
const int IID_TORPEDO          = 5;
const int IID_FREE_SHIP_GOODIE = 6;
const int IID_ENERGY_GOODIE    = 7;
const int IID_TORPEDO_GOODIE   = 8;
const int IID_STAR             = 9;

// sounds

const int SOUND_ENEMY_DIE              = 0;
const int SOUND_PLAYER_DIE             = 1;
const int SOUND_PLAYER_FIRE            = 2;
const int SOUND_ENEMY_FIRE             = 3;
const int SOUND_GOT_GOODIE             = 4;
const int SOUND_PLAYER_HIT             = 5;
const int SOUND_ENEMY_HIT              = 6;
const int SOUND_ENEMY_PLAYER_COLLISION = 7;
const int SOUND_PLAYER_TORPEDO         = 8;

// keys the user can hit

const int KEY_PRESS_LEFT  = 1000;
const int KEY_PRESS_RIGHT = 1001;
const int KEY_PRESS_UP    = 1002;
const int KEY_PRESS_DOWN  = 1003;
const int KEY_PRESS_SPACE = ' ';
const int KEY_PRESS_TAB   = '\t';

// board dimensions 

const int VIEW_WIDTH  = 30;
const int VIEW_HEIGHT = 40;

// status of each tick (did the player die?)

const int GWSTATUS_PLAYER_DIED   = 0;
const int GWSTATUS_CONTINUE_GAME = 1;

// test parameter constants

const int TEST_PARAM_ACTOR_INDEX      = 0;
const int NUM_TEST_PARAMS             = 1;

const int TEST_PARAM_NACHLING         = 1;
const int TEST_PARAM_WEALTHY_NACHLING = 2;
const int TEST_PARAM_SMALLBOT         = 3;
const int TEST_PARAM_GOODIE_ENERGY    = 4;
const int TEST_PARAM_GOODIE_TORPEDO   = 5;
const int TEST_PARAM_GOODIE_FREE_SHIP = 6;

#endif // _GAMECONSTANTS_H_
