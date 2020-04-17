#include <stdio.h>

#include "Roach_Events.h"
#include "roach.h"
#include "Roach_State_Machine.h"
#include "timers.h"

//a list of states that this SM uses:

enum {
    Moving_Forward,
    Reversing,
    Turning_Randomly,
    Hiding,
};

int current_state;

/* This function initializes the roach state machine.
 * At a minimum, this requires setting the first state.
 * Also, execute any actions associated with initializing the SM
 * (that is, the actions on the arrow from the black dot in the SM diagram)*/
void Initialize_RoachStateMachine(void)
{
    current_state = Moving_Forward;
    Roach_LeftMtrSpeed(80);
    Roach_RightMtrSpeed(80);
    
    //seed rand:
    srand(Roach_LightLevel());
    printf("%d\r\n", Roach_LightLevel());
};



static char isTurning;
void turn90(Event event)
{
    char previous_state = TIMER_NOT_ACTIVE;
    TIMERS_InitTimer(2,100);
    isTurning = 1;
    while(1)
    {
        if (event == FRONT_LEFT_BUMP_PRESSED)
        {
            Roach_LeftMtrSpeed(80);
            Roach_RightMtrSpeed(-80);
        }
        else if (event == FRONT_RIGHT_BUMP_PRESSED)
        {
            Roach_LeftMtrSpeed(-80);
            Roach_RightMtrSpeed(80);
        }
        char current_state = TIMERS_IsTimerActive(2);
        if (current_state == TIMER_NOT_ACTIVE && previous_state == TIMER_ACTIVE)
        {
            Roach_LeftMtrSpeed(80);
            Roach_RightMtrSpeed(80);
            break;
        }
        previous_state = current_state;
    }
    
    current_state = Moving_Forward;
    TIMERS_InitTimer(3,1000);
    char previous_state2 = TIMER_NOT_ACTIVE;
    while(1)
    {
        char current_state2 = TIMERS_IsTimerActive(3);
        isTurning = 1;
        if (previous_state2 == TIMER_ACTIVE && current_state2 == TIMER_NOT_ACTIVE)
        {
            break;
            isTurning = 0;
        }
        previous_state2 = current_state2;
    }
    
}

void turnWall(Event e)
{
    while (Roach_ReadFrontRightBumper() == BUMPER_NOT_TRIPPED && Roach_ReadFrontLeftBumper() == BUMPER_NOT_TRIPPED)
    {
        if (e == REAR_RIGHT_BUMP_RELEASED)
        {
            Roach_LeftMtrSpeed(80);
            Roach_RightMtrSpeed(0);
        }
        if (e == REAR_LEFT_BUMP_RELEASED)
        {
            Roach_LeftMtrSpeed(0);
            Roach_RightMtrSpeed(80);
        }
    }
    Roach_LeftMtrSpeed(80);
    Roach_RightMtrSpeed(80);
}
void turnCorner(Event e)
{
    char previous_state = TIMER_NOT_ACTIVE;
    TIMERS_InitTimer(4,200);
    while(Roach_ReadFrontRightBumper() == BUMPER_TRIPPED && Roach_ReadFrontLeftBumper() == BUMPER_TRIPPED)
    {
        current_state = TIMERS_IsTimerActive(4);
        if (e == FRONT_RIGHT_BUMP_PRESSED)
        {
            Roach_LeftMtrSpeed(80);
            Roach_RightMtrSpeed(-80);
        }
        else if (e == FRONT_LEFT_BUMP_PRESSED)
        {
            Roach_LeftMtrSpeed(-80);
            Roach_RightMtrSpeed(80);
        }
        /*if (current_state == TIMER_NOT_ACTIVE && previous_state == TIMER_ACTIVE)
         {
         Roach_LeftMtrSpeed(80);
         Roach_RightMtrSpeed(80);
         break;
         }*/
        previous_state = current_state;
    }
    Roach_LeftMtrSpeed(80);
    Roach_RightMtrSpeed(80);
}

int returnTurning(void)
{
    if (isTurning) return 1;
    else return 0;
}
int stopFunction(void)
{
    if (current_state == Hiding)
    {
        return 1;
        
    }
    else return 0;
}

void Reverse(void)
{
    current_state = Reversing;
    char timer0_Expired_EventFlag = 0;
    static char previous_timer_state = TIMER_NOT_ACTIVE;
    TIMERS_InitTimer(0,100);
    while (1)
    {
        Roach_LeftMtrSpeed(-100);
        Roach_RightMtrSpeed(-100);
        char current_timer_state = TIMERS_IsTimerActive(0);
        if (previous_timer_state == TIMER_ACTIVE && current_timer_state == TIMER_NOT_ACTIVE)
        {
            break;
        }
        previous_timer_state = current_timer_state;
    }
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
}

void Turn (Event event)
{
    TIMERS_InitTimer(1,275);
    char previous_turnTimer_state = TIMER_NOT_ACTIVE;
    current_state = Turning_Randomly;
    while(1)
    {
        char current_turnTimer_state = TIMERS_IsTimerActive(1);
        if (event == FRONT_RIGHT_BUMP_PRESSED)
        {
            Roach_LeftMtrSpeed(-80);
            Roach_RightMtrSpeed(80);
        }
        if (event == FRONT_LEFT_BUMP_PRESSED)
        {
            Roach_LeftMtrSpeed(100);
            Roach_RightMtrSpeed(-100);
        }
        if (current_turnTimer_state == TIMER_NOT_ACTIVE && previous_turnTimer_state == TIMER_ACTIVE)
        {
            break;
        }
        previous_turnTimer_state = current_turnTimer_state;
    }
    Roach_LeftMtrSpeed(100);
    Roach_RightMtrSpeed(100);
}
/*
 * @briefThis function feeds newly detected events to the roach state machine.
 * @param event:  The most recently detected event*/
void Run_RoachStateMachine(Event event)
{
    switch (current_state) {
        case Moving_Forward:
            printf("Current state:  Moving_Forward\r\n");
            if (event == ENTERED_DARK) {
                current_state = Hiding;
                //stop motors:
                Roach_LeftMtrSpeed(0);
                Roach_RightMtrSpeed(0);
            }
            break;
        case Reversing:
            printf("Current state: Reversing\r\n");
            break;
        case Hiding:
            printf("Current state:  Hiding\r\n");
            //no transitions out of hiding (for now)
            break;
            
    }
};
