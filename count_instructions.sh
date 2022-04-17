#!/bin/bash

instructions=`grep -Pi "#define\s+\w+\s+0x[0-9a-f]{2}" src/game/cpu/opcodes.h src/game/cpu/cb_prefixed_opcodes.h`
echo "$instructions"
echo "$instructions" | wc -l 

