# Project_CS162_APCS22: VisualGo clone in C++

This project is a clone version from [VisualGo](https://visualgo.net/en) with basic data structures.

## Introduction

Data Structure Visualization is a program that allows users to visualize the behavior of common data structures such as linked lists, stacks, queues. This program is written in C++ and uses the SFML library for graphics rendering.

## Features
This program currently supports the following data structures:
- Static Array
- Dynamic Array (resize one element each insertion or deletion only)
- Singly Linked List
- Doubly Linked List
- Circular Linked List
- Stack
- Queue
Main features included:
- Smooth animations of the algorithms responsible for inserting, deleting, searching, and updating values in the data structure.
- Control the speed of the animations and play, pause or reverse the animations.
- Step-by-step code highlight
- Create random, user defined or load-from-file list.

## Installation

### Prerequisites

- C++ compiler (such as g++ or clang++)
- SFML library installation instructions available on the [SFML website](https://www.sfml-dev.org/download.php)

### Building

1. Download or clone the repository to your local machine.
2. Install SFML library by following the instructions in SFML's official website.
3. Navigate to the project directory and open a terminal.
4. Compile the code using the following command:
```console
cd src/
g++ -fdiagnostics-color=always -g *.cpp -o DataVisual.exe -Ipath_to_SFML/include -Ipath_to_project/header -DSFML_STATIC -Lpath_to_SFML/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows
```

### Running

1. Navigate to the directory of the project.
2. Run the executable file through terminal:
```console
./src/DataVisual.exe
```
or move the DataVisual.exe file in the "src/" folder to its parent folder and double-click it.

## Credits

This program was created by 22125074 - Le Duc Phu (dphu2609) as a project for CS162 - Introduction to Computer Science II at VNU - University of Science.

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
