/* $Id$
 *
 */

use uo;
use os;

include ":timedscripts:timedScripts";

/*
 * TargetEX(mobile, duration, flags)
 *
 * Purpose
 * Brings up a Target() cursor and closes it after so many seconds.
 *
 * Parameters
 * mobile:	Mobile to send the target cursor to.
 * duration:	How long in seconds to keep the target cursor available.
 * 		0 - Target can stay open until a new one is sent.
 * flags:	See uo.em TGTOPT_* flags
 *
 * Return Value
 * Returns the value from uo.em :: Target()
 *
 */
function TargetEX(mobile, duration:=0, flags := TGTOPT_CHECK_LOS+TGTOPT_NEUTRAL)
	if ( duration > 0 )
		if ( CInt(TS_GetTimerDuration(mobile, "TargetControl")) > 0 )
			// Existing timer... stop it (itll cancel the old target)
			TS_LowerDuration(mobile, "TargetControl", -1);
		endif

		TS_StartTimer(mobile, "TargetControl", duration);
	endif

	return Target(mobile, flags);

	if ( duration > 0 )
		if ( CInt(TS_GetTimerDuration(mobile, "TargetControl")) > 0 )
			TS_LowerDuration(mobile, "TargetControl", -1);
		endif
	endif

	return 1;
endfunction

/*
 * TargetCoordinatesEX(mobile, duration, flags)
 *
 * Purpose
 * Brings up a TargetCoordinates() cursor and closes it after so many seconds.
 *
 * Parameters
 * mobile:	Mobile to send the target cursor to.
 * duration:	How long in seconds to keep the target cursor available.
 * 		0 - Target can stay open until a new one is sent.
 * flags:	Supports the uo.em TGTOPT_NOCHECK_LOS and TGTOPT_CHECKLOS flags.
 *
 * Return Value
 * Returns the value from uo.em :: TargetCoordinates()
 *
 */
function TargetCoordinatesEX(mobile, duration:=0, flags := TGTOPT_NOCHECK_LOS)
	if ( duration > 0 )
		if ( CInt(TS_GetTimerDuration(mobile, "TargetControl")) > 0 )
			// Existing timer... stop it (itll cancel the old target)
			TS_LowerDuration(mobile, "TargetControl", -1);
		endif

		TS_StartTimer(mobile, "TargetControl", duration);
	endif

	var targ := TargetCoordinates(mobile);

	if ( duration > 0 )
		if ( CInt(TS_GetTimerDuration(mobile, "TargetControl")) > 0 )
			// If the timer is still running, stop it.
			TS_LowerDuration(mobile, "TargetControl", -1);
		endif
	endif

	if ( targ )
		if ( flags & TGTOPT_CHECK_LOS )
			if ( !CheckLosAt(mobile, targ.x, targ.y, targ.z) )
				SendSysMessage(mobile, "That is not within your line of sight.");
				return error{"errortext":="Mobile's selection was not within LOS."};
			endif
		endif
	endif

	return targ;
endfunction