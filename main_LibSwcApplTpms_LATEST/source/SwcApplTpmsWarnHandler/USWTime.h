

#ifndef USWTime_H
#define USWTime_H
extern void ResetUSWTime(void);
extern void StopFilterSTWT( void );
extern unsigned char ucStartFilterSTWT( unsigned short);
extern unsigned char ucStartFilterHDWT(  unsigned short);
extern void StopFilterHDWT( void );
extern uint8 ui8HWTimerExpired(void);
extern uint8 ui8SWTimerExpired(void);
extern uint8 ui8KL15OFFnXsec(void);
#endif

