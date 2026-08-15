#ifndef FSM_H
#define FSM_H

// States
typedef enum
{
    STATE_SETUP,
    STATE_TRAINING,
    STATE_RESTING
} FSM_State_t;  

//Training modes
typedef enum
{
    MODE_REP,
    MODE_TIMED
} FSM_Mode_t;

void FSM_Init(void);
void FSM_Update(void);

#endif