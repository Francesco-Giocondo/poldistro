//$Id: settings.inc 87 2006-05-23 19:04:43Z sroyalty $

/*===============================================================
* Current Version
* SETTINGS.INC - v1.0
* Updated 9/27/2005 2:54PM
*
* -- Revision v1.0 --
* Austin:
*  Created include file
===============================================================*/

use uo;
use os;
use cfgfile;

/*
 * SVR_GetSettingsCfgFile(engine_name)
 *
 * Purpose
 * Reads in :worldsaver:configs/settings.cfg
 *
 * Parameters
 *
 * Return value
 * A config file reference.
 *
 */
function SVR_GetSettingsCfgFile()
	var cfg := ReadConfigFile(":worldsaver:config/settings");

	if ( cfg.errortext )
		SysLog("Error::SVR_GetSettingsCfgFile() - Unable to open [:worldsaver:config/settings.cfg] ->"+cfg.errortext);
	endif

	return cfg;
endfunction

/*
 * SVR_GetSettingsCfgElem(elem_name, cfg_file)
 *
 * Purpose
 * Retrieves an elem from a config file. 
 *
 * Parameters
 * elem_name:	A string matching the elem name to be retrieved.
 * cfg_file:	Optional parameter - reference to a config already read in by SVR_GetSettingsCfgFile()
 *
 * Return value
 * A config file elem reference.
 *
 */
function SVR_GetSettingsCfgElem(elem_name, byref cfg_file:=0)
	if ( !cfg_file )
		cfg_file := SVR_GetSettingsCfgFile();
	endif
	
	var elem := cfg_file[elem_name];

	if ( elem.errortext )
		SysLog("Error::SVR_GetSettingsCfgElem() - Unable to find elem ["+elem_name+"] ->"+elem.errortext);
	endif

	return elem;
endfunction