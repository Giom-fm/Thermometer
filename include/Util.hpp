#pragma once

#define IS_BIT_SET(_byte, _bit) (((_byte) & (1 << (_bit))) >> (_bit))

