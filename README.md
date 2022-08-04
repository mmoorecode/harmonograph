# harmonograph

A harmonograph is an image created by the movement of a stylus guided by the motions of pendulums.  The path traced by a stylus guided by two pendulums can be described by the parametric equations:

x(t) = (A1 * sin(t * f1 + p1) * e ^ (-d1 * t)) + (A2 * sin(t * f2 + p2) * e ^ (-d2 * t))

y(t) = (A3 * sin(t * f3 + p3) * e ^ (-d3 * t)) + (A4 * sin(t * f4 + p4) * e ^ (-d4 * t))

This program plots the graph generated by the parametric equations given a set of initial values provided by the user. 

Libraries used:
SFML - https://www.sfml-dev.org/
ImGui - https://github.com/ocornut/imgui
ImGui-SFML - https://github.com/eliasdaler/imgui-sfml

![Alt text](https://github.com/mmoorecode/julia-set-visualizer/blob/main/images/harmonograph.png)