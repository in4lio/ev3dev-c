#pragma once

.macro ENUM_0 name
.set ENUM_COUNTER, 0
.equiv \name, ENUM_COUNTER
.endm

.macro ENUM_N name
.set ENUM_COUNTER, ENUM_COUNTER + 1
.equiv \name, ENUM_COUNTER
.endm

.macro ENUM_EQ name, value
.set ENUM_COUNTER, \value
.equiv \name, ENUM_COUNTER
.endm
