#include "Roach_Events.h"
#include "roach.h"
#include "timers.h"


#define DEBOUNCE_TIMER 15 //select a timer to be the debounce timer
#define DEBOUNCE_PERIOD 30 //in milliseconds, the duration of the debounce period

#define LIGHT_THRESHOLD 450 //The threshold between light and darkness - you may need to change this!

Event CheckForAllEvents(void)
{
    Event returnEvent = NO_EVENT;
    
    returnEvent = CheckForTimerEvents();
    if (returnEvent != NO_EVENT) return returnEvent;
    
    returnEvent = CheckForBumperEvents();
    if (returnEvent != NO_EVENT) return returnEvent;
    
    returnEvent = CheckForLightEvents();
    if (returnEvent != NO_EVENT) return returnEvent;
    
    return NO_EVENT;
}

Event CheckForTimerEvents(void)
{
    static char previous_timer_state = TIMER_NOT_ACTIVE;
    char current_timer_state = TIMERS_IsTimerActive(0);
    
    if (previous_timer_state == TIMER_ACTIVE &&
        current_timer_state == TIMER_NOT_ACTIVE) {
        //then an event occurred!
        previous_timer_state = current_timer_state;
        return NAV_TIMER_EXPIRED;
        
    }
    
    //if we got this far, there was no event
    return NO_EVENT;
}

Event CheckForBumperEvents(void)
{
    static char previous_fl_bumper_state = BUMPER_NOT_TRIPPED;
    static char previous_fr_bumper_state = BUMPER_NOT_TRIPPED;
    
    //a rough but effective way to handle debouncing:
    if (TIMERS_IsTimerActive(DEBOUNCE_TIMER)) return NO_EVENT;
    
    //now check for events:
    char current_fl_bumper_state = Roach_ReadFrontLeftBumper();
    if (current_fl_bumper_state != previous_fl_bumper_state) {
        previous_fl_bumper_state = current_fl_bumper_state;
        //start debounce period:
        TIMERS_InitTimer(DEBOUNCE_TIMER, DEBOUNCE_PERIOD);
        if (previous_fl_bumper_state != 0) {
            return FRONT_LEFT_BUMP_PRESSED;
            
        } else return FRONT_LEFT_BUMP_RELEASED;
    }
    
    char current_fr_bumper_state = Roach_ReadFrontRightBumper();
    if (current_fr_bumper_state != previous_fr_bumper_state) {
        previous_fr_bumper_state = current_fr_bumper_state;
        //start debounce period:
        TIMERS_InitTimer(DEBOUNCE_TIMER, DEBOUNCE_PERIOD);
        if (current_fr_bumper_state != 0) {
            return FRONT_RIGHT_BUMP_PRESSED;
        } else return FRONT_RIGHT_BUMP_RELEASED;
    }
    
    //if we got this far, there was no event
    return NO_EVENT;
}

enum {
    DARK, LIGHT
};

Event CheckForLightEvents(void)
{
    static char previousLightState = LIGHT;
    
    char currentLightState;
    int current_light_reading = Roach_LightLevel();
    if (current_light_reading >= LIGHT_THRESHOLD) {
        currentLightState = DARK;
    } else currentLightState = LIGHT;
    if (currentLightState != previousLightState) {
        previousLightState = currentLightState;
        if (currentLightState == DARK) {
            return ENTERED_DARK;
        } else return ENTERED_LIGHT;
    }
    
    //if we got this far, there was no event
    return NO_EVENT;
}
