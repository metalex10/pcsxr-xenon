/****************************************************************************
 * libwiigui Template
 * Tantric 2009
 * Modified by Ced2911, 2011
 *
 * input.cpp
 * Wii/GameCube controller management
 ***************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <input/input.h>
#include <usb/usbmain.h>
#include <xetypes.h>
//#include "menu.h"
#include "video.h"
#include "input.h"
#include "gui/gui.h"

#include "emu.h"
#include "button_mapping.h"
#define MAX_INPUTS 4

extern "C" WPADData wpad_xenon[4];
int rumbleRequest[4] = {0, 0, 0, 0};
GuiTrigger userInput[4];
static int rumbleCount[4] = {0, 0, 0, 0};

/****************************************************************************
 * UpdatePads
 *
 * Scans pad and wpad
 ***************************************************************************/
void UpdatePads() {
        XenonInputUpdate();
	
        for (int i = 3; i >= 0; i--) {
                userInput[i].pad.btns_d = PAD_ButtonsDown(i);
                userInput[i].pad.btns_u = PAD_ButtonsUp(i);
                userInput[i].pad.btns_h = PAD_ButtonsHeld(i);
                //        userInput[i].pad.stickX = PAD_StickX(i);
                //        userInput[i].pad.stickY = PAD_StickY(i);
                userInput[i].pad.substickX = PAD_SubStickX(i);
                userInput[i].pad.substickY = PAD_SubStickY(i);
                userInput[i].pad.triggerL = PAD_TriggerL(i);
                userInput[i].pad.triggerR = PAD_TriggerR(i);
        }
}

/****************************************************************************
 * SetupPads
 *
 * Sets up userInput triggers for use
 ***************************************************************************/
void SetupPads() {
	XenonInputInit();


	for (int i = 0; i < 4; i++) {
		userInput[i].chan = i;
		userInput[i].wpad = &wpad_xenon[i];
		userInput[i].wpad->exp.type = EXP_CLASSIC;
	}
}

bool MenuRequested() {
	for (int i = 0; i < 4; i++) {
		if (
			(userInput[i].pad.substickX < -70) ||
			(userInput[i].pad.btns_h & PAD_TRIGGER_L &&
			userInput[i].pad.btns_h & PAD_TRIGGER_R &&
			userInput[i].pad.btns_h & PAD_BUTTON_X &&
			userInput[i].pad.btns_h & PAD_BUTTON_Y
			) ||                        
			userInput[i].pad.btns_h & PAD_BUTTON_LOGO
			) {
			return true;
		}
	}
	return false;
}
