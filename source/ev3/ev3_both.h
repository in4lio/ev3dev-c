/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  ev3_both.h
 *  \brief  EV3 brick definitions.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define GPIO_KEYS_PATH  "/dev/input/by-path/platform-gpio-keys.0-event"

/**
 *  \brief Identifiers of EV3 keys.
 */
enum {
	EV3_KEY__NONE_ = 0,

	EV3_KEY_UP     = 0x01L,
	EV3_KEY_DOWN   = 0x02L,
	EV3_KEY_LEFT   = 0x04L,
	EV3_KEY_RIGHT  = 0x08L,
	EV3_KEY_CENTER = 0x10L,
	EV3_KEY_BACK   = 0x20L,
};

#define DESC_LIMIT    64
#define DESC_VEC_LEN  4
