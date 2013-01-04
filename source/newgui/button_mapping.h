/****************************************************************************
 * PCSXR Xenon
 *
 * button_mapping.h
 *
 * Controller button mapping
 ***************************************************************************/

#ifndef BTN_MAP_H
#define BTN_MAP_H

enum {
	CTRLR_NONE = -1,
	CTRLR_XBOX = 0,
	CTRLR_ARCADE,
	CTRLR_FIGHTPAD,
	CTRLR_MAX
};

const char ctrlrName[CTRLR_MAX][20] =
{ "Xbox 360 Controller", "FightStick", "FightPad"};

typedef struct _btn_map {
	u32 btn;					// button 'id'
	char* name;					// button name
} BtnMap;

typedef struct _ctrlr_map {
	char * name;		// controller name
	u16 type;			// controller type
	int num_btns;		// number of buttons on the controller
	BtnMap map[15];		// controller button map
} CtrlrMap;

extern CtrlrMap ctrlr_def[CTRLR_MAX];

#endif
