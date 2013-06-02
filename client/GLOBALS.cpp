
#include "GLOBALS.h"

using namespace constants;
using namespace irr;


std::map<std::string,irr::EKEY_CODE> KEYMAP;

/* 
 * Certaines variables ne peuvent pas être initialisées au moment 
 * de leur déclaration, elles sont donc initialisées ici.
 */
void initialiseGlobals()
{
	
	KEYMAP["a"] = KEY_KEY_A;
	KEYMAP["b"] = KEY_KEY_B;
	KEYMAP["c"] = KEY_KEY_C;
	KEYMAP["d"] = KEY_KEY_D;
	KEYMAP["e"] = KEY_KEY_E;
	KEYMAP["f"] = KEY_KEY_F;
	KEYMAP["g"] = KEY_KEY_G;
	KEYMAP["h"] = KEY_KEY_H;
	KEYMAP["i"] = KEY_KEY_I;
	KEYMAP["j"] = KEY_KEY_J;
	KEYMAP["k"] = KEY_KEY_K;
	KEYMAP["l"] = KEY_KEY_L;
	KEYMAP["m"] = KEY_KEY_M;
	KEYMAP["n"] = KEY_KEY_N;
	KEYMAP["o"] = KEY_KEY_O;
	KEYMAP["p"] = KEY_KEY_P;
	KEYMAP["q"] = KEY_KEY_Q;
	KEYMAP["r"] = KEY_KEY_R;
	KEYMAP["s"] = KEY_KEY_S;
	KEYMAP["t"] = KEY_KEY_T;
	KEYMAP["u"] = KEY_KEY_U;
	KEYMAP["v"] = KEY_KEY_V;
	KEYMAP["w"] = KEY_KEY_W;
	KEYMAP["x"] = KEY_KEY_X;
	KEYMAP["y"] = KEY_KEY_Y;
	KEYMAP["z"] = KEY_KEY_Z;


	KEYMAP["arrow_up"] = KEY_UP;
	KEYMAP["arrow_down"] = KEY_DOWN;
	KEYMAP["arrow_left"] = KEY_LEFT;
	KEYMAP["arrow_right"] = KEY_RIGHT;	

	KEYMAP["1"] = KEY_KEY_1;
	KEYMAP["2"] = KEY_KEY_2;
	KEYMAP["3"] = KEY_KEY_3;
	KEYMAP["4"] = KEY_KEY_4;
	KEYMAP["5"] = KEY_KEY_5;
	KEYMAP["6"] = KEY_KEY_6;
	KEYMAP["7"] = KEY_KEY_7;
	KEYMAP["8"] = KEY_KEY_8;
	KEYMAP["9"] = KEY_KEY_9;
	KEYMAP["0"] = KEY_KEY_0;

	KEYMAP["num_0"] = KEY_NUMPAD0;
	KEYMAP["num_1"] = KEY_NUMPAD1;
	KEYMAP["num_2"] = KEY_NUMPAD2;
	KEYMAP["num_3"] = KEY_NUMPAD3;
	KEYMAP["num_4"] = KEY_NUMPAD4;
	KEYMAP["num_5"] = KEY_NUMPAD5;
	KEYMAP["num_6"] = KEY_NUMPAD6;
	KEYMAP["num_7"] = KEY_NUMPAD7;
	KEYMAP["num_8"] = KEY_NUMPAD8;
	KEYMAP["num_9"] = KEY_NUMPAD9;

	KEYMAP["F1"] = KEY_F1;
	KEYMAP["F2"] = KEY_F2;
	KEYMAP["F3"] = KEY_F3;
	KEYMAP["F4"] = KEY_F4;
	KEYMAP["F5"] = KEY_F5;
	KEYMAP["F6"] = KEY_F6;
	KEYMAP["F7"] = KEY_F7;
	KEYMAP["F8"] = KEY_F8;
	KEYMAP["F9"] = KEY_F9;
	KEYMAP["F10"] = KEY_F10;
	KEYMAP["F11"] = KEY_F11;
	KEYMAP["F12"] = KEY_F12;

	KEYMAP["back"] = KEY_BACK;
	KEYMAP["enter"] = KEY_RETURN;
	KEYMAP["escape"] = KEY_ESCAPE;
	KEYMAP["space"] = KEY_SPACE;
	KEYMAP["shift_r"] = KEY_RSHIFT;
	KEYMAP["shift_l"] = KEY_LSHIFT;
	KEYMAP["ctrl_r"] = KEY_RCONTROL;
	KEYMAP["ctrl_l"] = KEY_LCONTROL;
	KEYMAP["alt_r"] = KEY_RMENU;
	KEYMAP["alt_l"] = KEY_LMENU;

	//Retourné par translateToEkeyCode(string str) si str n'est pas dans KEYMAP
	KEYMAP["INVALID_KEY"] = KEY_KEY_CODES_COUNT;
}