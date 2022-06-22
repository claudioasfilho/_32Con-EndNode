#!/bin/bash
# Basic while loop

make -j11 all

commander flash soc_text_BG22.s37 -s 440172391
