# Simulation-of-Planetary-Motion

This C++ project involves simulating the motion of celestial bodies using the Runge-Kutta numerical method. The simulation is designed to explore the gravitational interactions among multiple bodies and gain insights into their dynamics.

## Mathematical Background
The simulation is based on solving a system of ordinary differential equations (ODE) that describe the motion of celestial bodies. Each body's motion is influenced by the gravitational attraction between all pairs of bodies in the system. The gravitational force between two bodies $i$ and $j$ is calculated using Newton's law of gravitation:

$F_{ij} = G \frac{m_i m_j}{d_{ij}^2} \hat{d}_{ij}$

Here:
* $F_{ij}$ represents the force on body $i$ due to body $j$.
* $G$ is the gravitational constant.
* $m_{i}$ and $m_{j}$ denote the masses of bodies $i$ and $j$ respectively.
* $d_{ij}$ is the distance between bodies $i$ and $j$
* $\hat{d_{ij}} is the unit vector pointing from body $i$ to body $j$
