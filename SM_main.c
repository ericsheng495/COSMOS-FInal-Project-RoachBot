/*
 * File:   Hello_World_main.c
 * Author: AutonomousSystemsLab
 *
 * Created on July 5, 2019, 1:32 PM
 */

//Standard C libraries:
#include <stdio.h>
#include <stdlib.h>

//Microchip's specialized library
#include <xc.h>

//A library to use the uc32 board
#include "BOARD.h"
#include "roach.h"
#include "timers.h"
#include "Roach_State_Machine.h"
#include "Roach_Events.h"

//static char bothPressed;

void PrintEvent(Event event)
{
    switch (event) {
            
        case NO_EVENT:
            printf("Event:  NO_EVENT \r\n");
            break;
        case FRONT_RIGHT_BUMP_PRESSED:
            printf("Event:  FRONT_RIGHT_BUMP_PRESSED\r\n");
            if (Roach_ReadFrontLeftBumper() == BUMPER_TRIPPED) turnCorner(event);
            else turn90(event);
            
            break;
        case FRONT_LEFT_BUMP_PRESSED:
            printf("Event:  FRONT_LEFT_BUMP_PRESSED\r\n");
            if (Roach_ReadFrontRightBumper() == BUMPER_TRIPPED) turnCorner(event);
            else turn90(event);
            break;
        case REAR_RIGHT_BUMP_PRESSED:
            printf("Event:  REAR_RIGHT_BUMP_PRESSED\r\n");
            break;
        case REAR_LEFT_BUMP_PRESSED:
            printf("Event:  REAR_LEFT_BUMP_PRESSED\r\n");
            break;
        case FRONT_RIGHT_BUMP_RELEASED:
            printf("Event:  FRONT_RIGHT_BUMP_RELEASED\r\n");
            turnWall(event);
            break;
        case FRONT_LEFT_BUMP_RELEASED:
            printf("Event:  FRONT_LEFT_BUMP_RELEASED\r\n");
            turnWall(event);
            break;
        case REAR_RIGHT_BUMP_RELEASED:
            printf("Event:  REAR_RIGHT_BUMP_RELEASED\r\n");
            turnWall(event);
            break;
        case REAR_LEFT_BUMP_RELEASED:
            printf("Event:  REAR_LEFT_BUMP_RELEASED\r\n");
            break;
        case ENTERED_DARK:
            printf("Event:  ENTERED_DARK\r\n");
            Roach_LeftMtrSpeed(0);
            Roach_RightMtrSpeed(0);
            break;
        case ENTERED_LIGHT:
            printf("Event:  ENTERED_LIGHT\r\n");
            break;
        case NAV_TIMER_EXPIRED:
            printf("Event:  NAV_TIMER_EXPIRED\r\n");
            break;
            
    }
    
}


int main(void)
{
    // <editor-fold defaultstate="collapsed" desc="//Initialization code (BOARD_Init(), etc)">
    
    
    //These calls configure the Pic32 so that it can interact with the Roach hardware
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();
    
    //Initialization code here:
    printf("Welcome to Roach State Machine lab, compiled on %s %s\r\n", __TIME__, __DATE__);
    // </editor-fold>
    
    //first, setup the framework:
    Initialize_RoachStateMachine();
    
    while (1) {
        //continuous services (event checkers):
        Event this_event = CheckForAllEvents();
        
        
        if (this_event != NO_EVENT) {
            PrintEvent(this_event);
            //run service:
            Run_RoachStateMachine(this_event);
            //clear event:
            this_event = NO_EVENT;
            
        }
        if (stopFunction() == 1)
        {
            break;
        }
        
        
    }
    
    return (EXIT_SUCCESS);
}
