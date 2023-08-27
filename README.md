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
* $\hat{d_{ij}}$ is the unit vector pointing from body $i$ to body $j$

The motion of each body can be described by a set of second-order differential equations:

$x_{i}'' = G\sum_{j\neq i}  \frac{m_j}{d_{ij}^3} (x_j - x_i)$

$y_{i}'' = G\sum_{j\neq i}  \frac{m_j}{d_{ij}^3} (y_j - y_i)$

## Simulation Details
The simulation process involves numerically solving the system of equations. The input is read from a file named *parameters.txt*, an example of which can be located in the current working directory. This file contains the following information:

* The first line includes the values of $G$, $ $T$ and $\Delta t$
* Subsequent lines describe each body, providing initial position, initial velocity and mass

## Output and Visualization
The code was tested on the following scenarios:
| Case     | Body Index $i$ |  $x_{i}(0)$ | $y_{i}(0)$ |  $\dot{x_{i}}(0)$ |  $\dot{y_{i}}(0)$ |  $m_{i}$ |
| ---------|----------------|-------------|------------|-------------------|-------------------|----------|
| One Body | 1              | 0.0         |  0.0       | 1.0               | 1.0               | 1.0      |
| Deflect  | 1              | 0.0         |  0.0       |  0.0              |   0.0             | 10.0     |
|          | 2              | 1.0         |  -1.0      |  0.0              |5.0                |1.0       |          
| Orbit1   |1               |0.0          |0.0         |0.0                |0.0                |625.0     |
|          |2               |1.0          |0.0         |0.0                |25.0               |1.0       |
| Orbit2   |1               |0.0          |0.0         |0.0                |0.0                |500.0     |
|          |2               |1.0          |0.0         |0.0                |25.0               |1.0       |
|          |3               |-1.0         |0.0         |     0.0           | -25.0             |1.0       |


## Results

| Case     | Body Index $i$ |  $x_{i}(T)$ | $y_{i}(T)$ |  $\dot{x_{i}}(T)$ |  $\dot{y_{i}}(T)$ |  $m_{i}$ |
| ---------|----------------|-------------|------------|-------------------|-------------------|----------|
| One Body | 1              | 1.0         |  1.0       | 1.0               | 1.0               | 1.0      |
| Deflect  | 1              | 0.25871     |  0.11466   |0.30631            | 0.2546            | 10.0     |
|          | 2              | -1.6177     |  2.8279    |  -3.0578          |2.4462             |1.0       |          
| Orbit1   |1               |2.245e-06    |0.039996    |-0.0014913         |1.3446e-05         |625.0     |
|          |2               |0.9986       |0.002763    |0.93206            |24.992             |1.0       |
| Orbit2   |1               |0.0          |0.0         |0.0                |0.0                |500.0     |
|          |2               |-1.0998      |1.0538      |-13.848            |-9.4612            |1.0       |
|          |3               |1.0998       |-1.0538     | 13.848            | -9.4612           |1.0       |


 
