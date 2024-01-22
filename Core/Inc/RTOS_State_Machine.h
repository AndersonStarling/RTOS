#ifndef RTOS_STATE_MACHINE
#define RTOS_STATE_MACHINE

typedef enum
{
    main_menu = 0,
    led_menu  = 1,
    rtc_menu  = 2,
	rtc_menu_configure_time = 3,
	rtc_menu_configure_hour = 4,
	rtc_menu_configure_min  = 5,
	rtc_menu_configure_second = 6
} RTOS_State_Machine_enum_t;

#endif /* RTOS_STATE_MACHINE */








