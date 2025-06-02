# Physics Simulator

A visual physics simulation tool with GUI support that allows users to create and manipulate static, kinematic, and dynamic bodies. This project includes configurable physics properties, spring constraints, and full simulation control.

![image](https://github.com/user-attachments/assets/6b3d33ca-ecfe-4975-a22b-e2e540066205)

---

## Features

### Core Simulation Support

- **Static Bodies**: Immovable; not affected by forces or collisions.
- **Kinematic Bodies**: Moves with a defined velocity; unaffected by external physics forces.
- **Dynamic Bodies**: Fully simulated using physics forces like gravity, collisions, and springs.

### Per-Object Configurations

Each object can be configured individually with:
- Mass
- Size
- Damping
- Gravity Scale
- Restitution (Bounciness)
- Spring system (if attached)

### Spring System

Objects can be connected using spring constraints, with support for:
- Stiffness (spring constant)
- Damping

![image](https://github.com/user-attachments/assets/e00b5866-1e20-42d4-acef-a6292c27c83e)

---

## GUI Capabilities

![image](https://github.com/user-attachments/assets/b6283ad7-6db8-4ac4-a2dc-0bac69895668)


### Object Management
- Add Static / Kinematic / Dynamic bodies
- Configure each body's parameters via the UI

### Spring Creation
- Select two bodies to connect with a spring
- Customize stiffness and damping values

### Global Controls
- Adjust global simulation settings:
  - Global gravity
  - Gravitational force
  - Spring stiffness multiplier

### Simulation Flow
- Start / Pause the simulation
- Reset simulation to clear all objects and connections

---

## Physics Behavior

- Dynamic bodies respond correctly to forces, collisions, and gravity.
- Spring mechanics follow real-world physics behavior using Hooke's law with damping.
- Reset functionality clears all objects and springs, returning to a clean state.
- Pause functionality freezes the simulation while preserving the current state.

---

# License
Copyright (c) 2020-2025 Jeffery Myers

This software is provided "as-is", without any express or implied warranty. In no event 
will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you 
  wrote the original software. If you use this software in a product, an acknowledgment 
  in the product documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be misrepresented
  as being the original software.

  3. This notice may not be removed or altered from any source distribution.
