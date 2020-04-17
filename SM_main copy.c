#include <stdio.h>

#include "Roach_Events.h"
#include "roach.h"
#include "Roach_Top_Level_SM.h"
#include "timers.h"

#define ISLAND_TIMER 0
#define TURN_TIMER 1
#define EXIT_ISLAND_TIMER 2

//a list of states that this SM uses:

enum {
    //your states here
    Moving_Forward,
    Arc_Left,
    Arc_Right,
    Turn_Left,
    Turn_Right,
    Timed_Move_Forward,
    Right_Corner_Turn,
    Left_Corner_Turn,
    Hiding,
};

int current_state;

/* This function initializes the roach state machine.
 * At a minimum, this requires setting the first state.
 * Also, execute any actions associated with initializing the SM
 * (that is, the actions on the arrow from the black dot in the SM diagram)*/
// visual studio code

void Initialize_NavigateObstacleField_StateMachine(void) {
    TIMERS_InitTimer(ISLAND_TIMER, 25000);
    current_state = Moving_Forward;
    Roach_LeftMtrSpeed(100);
    Roach_RightMtrSpeed(100);
};

/*
 * @briefThis function feeds newly detected events to the roach state machine.
 * @param event:  The most recently detected event*/

Event Run_Roach_NavigateObstacleField_StateMachine(Event event) {
    switch (current_state) {
            TRANSITION_TO(Moving_Forward);
        case Moving_Forward:
            Roach_LEDSSet(0b110000000000);
            printf("Current state = MOVING FORWARD\r\n");
            if (event == STATE_TRANSITION) {
                Roach_LeftMtrSpeed(100);
                Roach_RightMtrSpeed(100);
            }
            
            
            if (event == FRONT_LEFT_BUMP_PRESSED) {
                TRANSITION_TO(Arc_Left);
            }
            if (event == FRONT_RIGHT_BUMP_PRESSED) {
                TRANSITION_TO(Arc_Right);
            }
            if (event == ENTERED_DARK) {
                TRANSITION_TO(Hiding);
            }
            
            //            if (event == ISLAND_TIMER_EXPIRED) {
            //                Roach_LEDSSet(0b111111111111);
            //                TRANSITION_TO(Timed_Move_Forward);
            //            }
            
            break;
            
            
        case Arc_Left:
            printf("Current state = Arc Left\r\n");
            Roach_LEDSSet(0b001100000000);
            if (event == STATE_TRANSITION) {
                TIMERS_InitTimer(NAV_TIMER, 250);
                Roach_LeftMtrSpeed(-100);
                Roach_RightMtrSpeed(100);
            }
            
            
            if (event == NAV_TIMER_EXPIRED) {
                TRANSITION_TO(Arc_Right);
                
            }
            
            
            
            
            
            if (event == ENTERED_DARK) {
                TRANSITION_TO(Hiding);
            }
            
            if (event == ISLAND_TIMER_EXPIRED) {
                Roach_LEDSSet(0b111111111111);
                TRANSITION_TO(Timed_Move_Forward);
            }
            
            break;
            
        case Arc_Right:
            printf("Current state = Arc Left\r\n");
            Roach_LEDSSet(0b000011000000);
            if (event == STATE_TRANSITION) {
                TIMERS_InitTimer(NAV_TIMER, 350);
                Roach_LeftMtrSpeed(-100);
                Roach_RightMtrSpeed(100);
                //                  Roach_LeftMtrSpeed(100);
                //                  Roach_RightMtrSpeed(100);
            }
            if (event == NAV_TIMER_EXPIRED) {
                Roach_LeftMtrSpeed(100);
                Roach_RightMtrSpeed(100);
                //                if (event == FRONT_LEFT_BUMP_PRESSED) {
                //                    TRANSITION_TO(Right_Corner_Turn);
                //                }
            }
            
            
            if (event == FRONT_LEFT_BUMP_PRESSED) {
                //                TRANSITION_TO(Right_Corner_Turn);
                TRANSITION_TO(Arc_Right);
            }
            if (event == FRONT_RIGHT_BUMP_RELEASED) {
                TRANSITION_TO(Turn_Right);
                
            }
            
            if (event == ENTERED_DARK) {
                TRANSITION_TO(Hiding);
            }
            
            if (event == ISLAND_TIMER_EXPIRED) {
                Roach_LEDSSet(0b111111111111);
                TRANSITION_TO(Timed_Move_Forward);
            }
            
            break;
            //
            //        case Turn_Left:
            //            printf("Current state = Turn_Left \r\n");
            //            Roach_LEDSSet(0b000000110000);
            //            if (event == STATE_TRANSITION) {
            //                Roach_LeftMtrSpeed(0);
            //                Roach_RightMtrSpeed(100);
            //            }
            //            if (event == FRONT_LEFT_BUMP_PRESSED) {
            //                TRANSITION_TO(Arc_Left);
            //                // Roach_LeftMtrSpeed(100);
            //                // Roach_RightMtrSpeed(-100);
            //            }
            //
            //            if (event == ENTERED_DARK) {
            //                TRANSITION_TO(Hiding);
            //            }
            //
            //            if (event == ISLAND_TIMER_EXPIRED) {
            //                Roach_LEDSSet(0b111111111111);
            //                TRANSITION_TO(Timed_Move_Forward);
            //            }
            //
            //            break;
            
        case Turn_Right:
            printf("Current state = Turn_Right \r\n");
            Roach_LEDSSet(0b000000001100);
            if (event == STATE_TRANSITION) {
                Roach_LeftMtrSpeed(100);
                Roach_RightMtrSpeed(0);
                
            }
            if (event == FRONT_RIGHT_BUMP_PRESSED) {
                TRANSITION_TO(Arc_Right);
            }
            
            if (event == ENTERED_DARK) {
                TRANSITION_TO(Hiding);
            }
            
            if (event == ISLAND_TIMER_EXPIRED) {
                Roach_LEDSSet(0b111111111111);
                TRANSITION_TO(Timed_Move_Forward);
            }
            
            break;
            
            //        case Right_Corner_Turn:
            //            printf("Current state = Right_Corner_Turn \r\n");
            //            Roach_LEDSSet(0b100000000001);
            //            if (event == FRONT_LEFT_BUMP_RELEASED) {
            //                TRANSITION_TO(Arc_Right);
            //            }
            //            if (event == STATE_TRANSITION) {
            //                //                TIMERS_InitTimer(NAV_TIMER, 500);
            //                Roach_RightMtrSpeed(100);
            //                Roach_LeftMtrSpeed(-100);
            //            }
            //
            //            //            if (event == NAV_TIMER_EXPIRED) {
            //            //
            //            //
            //            //            }
            //
            //            if (event == ENTERED_DARK) {
            //                TRANSITION_TO(Hiding);
            //            }
            //
            //            if (event == ISLAND_TIMER_EXPIRED) {
            //                Roach_LEDSSet(0b111111111111);
            //                TRANSITION_TO(Timed_Move_Forward);
            //            }
            //            break;
            
        case Left_Corner_Turn:
            printf("Current state = Left_Corner_Turn \r\n");
            Roach_LEDSSet(0b010000000100);
            if (FRONT_RIGHT_BUMP_RELEASED) {
                TRANSITION_TO(Arc_Left);
            }
            if (event == STATE_TRANSITION) {
                //                TIMERS_InitTimer(NAV_TIMER, 500);
                Roach_RightMtrSpeed(-100);
                Roach_LeftMtrSpeed(100);
            }
            
            
            if (event == ENTERED_DARK) {
                TRANSITION_TO(Hiding);
            }
            
            if (event == ISLAND_TIMER_EXPIRED) {
                Roach_LEDSSet(0b111111111111);
                TRANSITION_TO(Timed_Move_Forward);
            }
            
            break;
            
        case Timed_Move_Forward:
            printf("Current state = Timed_Move_Forward \r\n");
            if (event == STATE_TRANSITION) {
                TIMERS_InitTimer(NAV_TIMER, 500);
                TIMERS_InitTimer(ISLAND_TIMER, 25000);
                Roach_RightMtrSpeed(100);
                Roach_LeftMtrSpeed(-100);
            }
            if (event == NAV_TIMER_EXPIRED) {
                Roach_RightMtrSpeed(100);
                Roach_LeftMtrSpeed(100);
            }
            if (event == ENTERED_DARK) {
                TRANSITION_TO(Hiding);
            }
            
            if (event == FRONT_LEFT_BUMP_PRESSED) {
                TRANSITION_TO(Arc_Left);
            }
            if (event == FRONT_RIGHT_BUMP_PRESSED) {
                TRANSITION_TO(Arc_Right);
            }
            
            if (event == ISLAND_TIMER_EXPIRED) {
                Roach_LEDSSet(0b111111111111);
                TRANSITION_TO(Timed_Move_Forward);
            }
            
            
            //            if (event == ENTERED_DARK) {
            //                TRANSITION_TO(Hiding);
            //            }
            //
            //            if (event == FRONT_LEFT_BUMP_PRESSED) {
            //                TRANSITION_TO(Arc_Left);
            //            }
            //            if (event == FRONT_RIGHT_BUMP_PRESSED) {
            //                TRANSITION_TO(Arc_Right);
            //            }
            //
            //            if (event == ISLAND_TIMER_EXPIRED) {
            //                Roach_LEDSSet(0b111111111111);
            //                TRANSITION_TO(Timed_Move_Forward);
            //            }
            
            break;
        case Hiding:
            if (event == STATE_TRANSITION) {
                Roach_RightMtrSpeed(0);
                Roach_LeftMtrSpeed(0);
            }
    }
    // Roach_LEDSSet(current_state);
    
    return event;
};
