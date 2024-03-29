<meta charset="utf-8"/>

# Code Kata: Landing Rover

Just for fun, we sometimes do code Katas. This time, it's "Landing Rover".

(This description is taken from https://github.com/lysium/kata-landing-rover
/ It is licensed under the MIT license by lysium)

# Task
## Description
You're part of an exploration team. Your team is sending Landing Rovers on planets. These Landing Rovers are remotely controlled vehicles used to explore the surface of the planet.

Your task is to develop an API that translates a sequence of commands into action of the vehicle. The Landing Rover excepts the following commands:

    MF - Move Forward one unit
    MB - Move Backwards one unit
    TL - Turn Left by 90°
    TR - Turn Right by 90°

## Requirements

The commands are given by a text file (one command per line), e.g.:

    MF
    MF
    TL
    MF
    TL
    MF

The planet is given by a text file and it should always be a square, e.g.
planet 10x10

    xx........
    xxxx......
    ..xx......
    ..xx......
    ..........
    ..........
    .....xx...
    ......xx..
    ....xxx...
    .....x....

## Good to know

- Planets are torus-shaped, so there are no left/right or top/bottom boundaries (so if you leave the map in north/south direction you re-enter it in the same column; when leaving the map in east/west direction you re-enter in the same row)
- a `.` is a free surface, where the Landing Rover can land or drive on
- a `x` is a obstacle, which can't crossed by the Landing Rover
- one character is one moving unit (for command MF/MB)
- if the Landing Rover encounters an obstacle, it does not move any further. Instead it aborts the command-sequence and reports the obstacle.

## Summary
- You are given a starting point (x, y) and a direction (N, S, W, E).
- You are given the planet as a text file.
- You are given a collection of commands as a text file.
- You should drive the Landing Rover on the planet. :-)
- You have to return the finish position and direction or the report of an obstacle (with current stop position and direction).

# Bonus
Create a text file, where you visualize the path of the Landing Rover for a given planet with given command-list.

# My solution

I took over the command line syntax of lysium's program:

- Usage: rover x y direction command_file planet_file [planet_trace_file]
- Output:
  - DONE x y direction  --or--
  - OBSTACLE x y direction (exit code 1)
- planet_trace_file is name of file where we output planet with trace.
- Coordinates for user:
  - top, left is 0,0
  - left <-> right is x-direction
  - top <-> down is y-direction

