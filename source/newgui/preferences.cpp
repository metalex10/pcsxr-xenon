/****************************************************************************
 * Snes9x Nintendo Wii/Gamecube Port
 *
 * Tantric 2008-2010
 *
 * preferences.cpp
 *
 * Preferences save/load to XML file
 ***************************************************************************/

#include <xetypes.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "emu.h"
#include "menu.h"
#include "fileop.h"
#include "filebrowser.h"
#include "input.h"
#include "button_mapping.h"

#include <rapidxml.hpp>
using namespace rapidxml;

struct SEMUSettings EMUSettings;

/****************************************************************************
 * Save Preferences
 ***************************************************************************/
static char prefpath[MAXPATHLEN] = { 0 };

bool
SavePrefs (bool silent)
{
	xml_document<> doc;

	// xml declaration
	xml_node<>* decl = doc.allocate_node(node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);
	
	// root node
	xml_node<>* root = doc.allocate_node(node_element, APPFOLDER);
	root->append_attribute(doc.allocate_attribute("version", APPVERSION));
	doc.append_node(root);
	
	// main node
	xml_node<>* emuconfig = doc.allocate_node(node_element, "configuration");	
	root->append_node(emuconfig);
	
	// other ...
	xml_node<>* language = doc.allocate_node(node_element, "language");	
	emuconfig->append_node(language);
	
	// other ...
	xml_node<>* cpu = doc.allocate_node(node_element, "cpu");	
	emuconfig->append_node(cpu);
	
	// other ...
	xml_node<>* gpu = doc.allocate_node(node_element, "gpu");	
	emuconfig->append_node(gpu);
	
	// other ...
	xml_node<>* hw_filter = doc.allocate_node(node_element, "hw_filter");	
	emuconfig->append_node(hw_filter);
		
	// other ...
	xml_node<>* sw_filter = doc.allocate_node(node_element, "sw_filter");	
	emuconfig->append_node(sw_filter);
	
	xml_node<>* use_experimental_dr = doc.allocate_node(node_element, "use_experimental_dr");	
	emuconfig->append_node(use_experimental_dr);
	
	if (!silent)
			InfoPrompt("Preferences saved");
	return true;
}

/****************************************************************************
 * Load Preferences from specified filepath
 ***************************************************************************/
bool
LoadPrefsFromMethod (char * path)
{
	bool retval = false;

	return retval;
}


static void DefaultSettings() {
	memset(&EMUSettings, 0, sizeof(SEMUSettings));
	EMUSettings.framelimit = 1;
	EMUSettings.sw_filter = 1; // XBR
	EMUSettings.hw_filter = 1; // 2xSai
}

/****************************************************************************
 * Load Preferences
 * Checks sources consecutively until we find a preference file
 ***************************************************************************/
static bool prefLoaded = false;

bool LoadPrefs()
{
	DefaultSettings();

	if(prefLoaded) // already attempted loading
		return true;

	bool prefFound = false;
	return prefFound;
}
