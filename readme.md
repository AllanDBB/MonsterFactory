# Monster Factory

## Overview
Monster Factory is a production simulator built with C++ and Qt. The project simulates a factory that creates monsters with different properties based on combinations of materials and attributes.

## System Architecture

The application is structured around several key components:

- **Raw Materials**: Different types of materials used in monster creation
- **Production Line**: Various stages monsters go through during creation
- **Quality Control**: Inspection system for validating monster quality
- **Storage System**: Storage for completed monsters
- **Delivery System**: Process for fulfilling customer orders

## Core Components

### Materials
The factory uses three types of raw materials to create monsters:
- **Energy**: Types include Cosmic, Elemental, and Dark
- **Material**: Types include Organic, Metallic, and Radioactive
- **Evil**: Types include Cunning, Chaotic, and Ruthless

### Monster Creation
Monsters are created through specific combinations of materials that produce different monster types:
- Cosmic + Organic + Cunning = INTELLIGENCE
- Elemental + Radioactive + Chaotic = DESTRUCTION
- Dark + Organic + Ruthless = REGENERATION
- Elemental + Metallic + Ruthless = STRENGTH
- Dark + Metallic + Cunning = EVIL
- Dark + Radioactive + Ruthless = POISON
- Cosmic + Radioactive + Chaotic = MADNESS
- Cosmic + Metallic + Cunning = TECHNOLOGY
- Elemental + Organic + Chaotic = SPEED

### Production Process
1. **Material Sources**: Generate raw materials
2. **Combiner**: Mixes materials to create monsters
3. **Furnace**: Contains trays for "baking" monsters
4. **Quality Control**: Inspectors validate monster quality
5. **Storage**: Holds completed monsters ready for delivery
6. **Garbage Collector**: Handles rejected monsters

### Order System
- Customers place orders with specific monster requirements
- Orders can have priority status
- Delivery system manages order fulfillment

## Logging System
The application maintains detailed logs in the following categories:
- General Log
- Order Log
- Storage Log
- Inspector Logs
- Garbage Collector Log
- Delivery Log
- Queue Log

## Project Setup

### Prerequisites
- Qt 6.7.3 or later
- C++ compiler (MinGW 64-bit recommended)
- CMake 3.29 or later

### Building the Project
1. Clone the repository
2. Open the project in Qt Creator or your preferred IDE
3. Configure the project with CMake
4. Build the project

### Project Structure
- **MonsterFactoryCore/**: Core simulation logic
  - **src/**: Source files
    - **Headers/**: Header files
    - **Functions/**: Implementation files
  - **logs/**: Log files
  - **orders/**: Order files
- **assets/**: Image resources
- **CMakeLists.txt**: Build configuration

## License
This project is licensed under the terms of the included LICENSE file.
