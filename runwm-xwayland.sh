#!/bin/bash

# 
# This is used for testing (i'm creating this WM on a Wayland compositor)
#

DISPLAY=:10

Xwayland $DISPLAY &
XWAYLAND_PID=$!

sleep 0.5

./moonwm &
MOONWM_PID=$!

sleep 0.5

xterm

kill -TERM $MOONWM_PID
kill -TERM $XWAYLAND_PID
