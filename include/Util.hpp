#pragma once

#define CHECK_BIT(_byte, _bit) (((_byte) & (1 << (_bit))) >> (_bit))
#define CLEAR_BIT(_byte, _bit) ((_byte) &= ~(1 << (_bit)))
