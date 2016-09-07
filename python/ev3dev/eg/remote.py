# -*- coding: utf-8 -*-

import sys
from ev3dev import *

# Motor speed for linear motion, in percents
SPEED_LINEAR   = 75
# ... for circular motion
SPEED_CIRCULAR = 50

# Motor maximal speed (will be detected)
max_speed = 0

MOTOR_LEFT  = OUTC
MOTOR_RIGHT = OUTB
MOTOR_BOTH  = MOTOR_LEFT | MOTOR_RIGHT

IR_CHANNEL = 0

# IR sensor port (will be detected)
ir = SOCKET__NONE_

STOP  = 0
FORTH = 1
BACK  = 2
LEFT  = 3
RIGHT = 4

# Command for `drive` coroutine
command = STOP

# Program is alive
alive = True

def init():
    global max_speed, ir

    if tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ ):  # any type of motor
        max_speed = tacho_get_max_speed( MOTOR_LEFT )
        tacho_reset( MOTOR_BOTH )
    else:
        print '''Please, plug LEFT motor in C port,
        RIGHT motor in B port and try again.'''
        # Quit, inoperative without motors
        return False

    ir = sensor_search( LEGO_EV3_IR )
    if ir:
        ir_set_mode_ir_remote( ir )
        print '''IR remote control:
        RED UP   & BLUE UP   - forward
        RED DOWN & BLUE DOWN - backward
        RED UP   | BLUE DOWN - left
        RED DOWN | BLUE UP   - right'''
    else:
        print '''IR sensor is NOT found,
        use the EV3 brick buttons.'''

    print 'Press BACK on the EV3 brick for EXIT...'
    return True

IR_ACTIONS = {
    RED_UP_BLUE_UP     : FORTH,
    RED_DOWN_BLUE_DOWN : BACK,
    RED_UP             : LEFT,
    RED_UP_BLUE_DOWN   : LEFT,
    BLUE_DOWN          : LEFT,
    RED_DOWN           : RIGHT,
    RED_DOWN_BLUE_UP   : RIGHT,
    BLUE_UP            : RIGHT,
}

def coro_handle_ir_control():
    """
    Coroutine of IR remote control handling.
    """
    global command

    if ir == SOCKET__NONE_:
        # Do nothing if no IR sensor
        while True:
            yield

    pressed = btns = IR_REMOTE__NONE_
    while True:
        # Waiting any IR RC button is pressed or released
        while btns == pressed:
            btns = sensor_get_value( IR_CHANNEL, ir )
            yield

        pressed = btns
        # Set command for `drive` coroutine
        if pressed in IR_ACTIONS:
            command = IR_ACTIONS[ pressed ]
        else:
            command = STOP
        yield

KEY_ACTIONS = {
    EV3_KEY_UP    : FORTH,
    EV3_KEY_DOWN  : BACK,
    EV3_KEY_LEFT  : LEFT,
    EV3_KEY_RIGHT : RIGHT,
}

def coro_handle_brick_control():
    """
    Coroutine of the EV3 brick keys handling.
    """
    global command, alive

    pressed = keys = EV3_KEY__NONE_
    while True:
        # Waiting any brick's key is pressed or released
        while keys == pressed:
            keys = brick_keys()
            yield

        pressed = keys
        # Set command for `drive` coroutine
        if pressed in KEY_ACTIONS:
            command = KEY_ACTIONS[ pressed ]
        else:
            command = STOP
            if pressed == EV3_KEY_BACK:
                alive = False  # Quit
        yield

def coro_drive():
    """
    Coroutine of control the motors.
    """
    speed_linear = max_speed * SPEED_LINEAR / 100
    speed_circular = max_speed * SPEED_CIRCULAR / 100
    state = STOP

    while True:
        # Waiting new command
        while state == command:
            yield

        if command == STOP:
            tacho_stop( MOTOR_BOTH )
            # Waiting the vehicle is stopped
            while tacho_is_running( MOTOR_BOTH ):
                yield

        elif command == FORTH:
            tacho_set_speed_sp( MOTOR_BOTH, -speed_linear )
            tacho_run_forever( MOTOR_BOTH )

        elif command == BACK:
            tacho_set_speed_sp( MOTOR_BOTH, speed_linear )
            tacho_run_forever( MOTOR_BOTH )

        elif command == LEFT:
            tacho_set_speed_sp( MOTOR_LEFT, speed_circular )
            tacho_set_speed_sp( MOTOR_RIGHT, -speed_circular )
            tacho_run_forever( MOTOR_BOTH )

        elif command == RIGHT:
            tacho_set_speed_sp( MOTOR_LEFT, -speed_circular )
            tacho_set_speed_sp( MOTOR_RIGHT, speed_circular )
            tacho_run_forever( MOTOR_BOTH )

        state = command
        yield

if __name__ == '__main__':
    print 'Waiting the EV3 brick online...'
    if not brick_init(): sys.exit( 1 )

    print '*** ( EV3 ) Hello! ***'
    alive = init()

    handle_ir_control = coro_handle_ir_control()
    handle_brick_control = coro_handle_brick_control()
    drive = coro_drive()

    while alive:
        handle_ir_control.next()
        handle_brick_control.next()
        drive.next()
        sleep_ms( 10 )

    brick_uninit()
    print
    print '*** ( EV3 ) Bye! ***'
