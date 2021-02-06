#pragma once

#include "Bitset.h"
#include "unordered_map"

typedef unsigned char byte;
typedef std::unordered_map<byte, Bitset> CodeTable;
typedef std::unordered_map<Bitset, byte, BitsetHash> DecodeTable;