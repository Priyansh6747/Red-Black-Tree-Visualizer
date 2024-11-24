# Red-Black Tree Visualizer
fork test

A **Red-Black Tree Visualizer** built with **C++** and **SDL2**, designed to help users understand the structure and operations of Red-Black Trees through interactive visualization.

## Features

- **Interactive Visualization**: See the tree structure update dynamically as you perform insertions and deletions.
- **Dynamic Balancing**: Observe rotations and color changes that maintain the Red-Black Tree properties.
- **Error Handling**: Detect and handle edge cases like duplicate insertions or empty deletions gracefully.
- **User-Friendly Interface**: Designed for ease of use with a clean, intuitive UI.
- **Multiple Tree Management**: Save and switch between trees effortlessly using the save button.

## Installation

1. Clone the repository:
   ```bash  
   https://github.com/Priyansh6747/Red-Black-Tree-Visualizer
   ```

## Usage

1. The program does not contain a prebuilt executable file, so you need to build it first (or use a released version in the future).
   To build it, open a terminal in the project directory and run:
   ```bash
    mingw32-make -f MakeFile
    ```
2. To run the program, use the following command:
    ```bash
    .\main.exe    
    ```

   > **Note:** No released version is available yet.

## How-it-works

1. Red-Black Tree Properties

    The visualizer enforces the following Red-Black Tree rules:

   1. Each node is either Red or Black.
   2. The root is always Black.
   3. Red nodes cannot have Red children ("No double reds").
   4. Every path from a node to its descendant null nodes
      must have the same number of Black nodes (Black height).

2. Operations
   1. Insertion:
   
      1. Adds a new node and dynamically updates the visualization. 
      2. Recolors and rotates nodes as necessary to maintain Red-Black Tree properties.
   2. Deletion: 
      1. Removes a node and rebalances the tree to restore its properties.
   3. Reset: 
      1. Clears the current tree, allowing you to start fresh.
   4. Save:
      1. **Save the Current Tree:** Save the current working tree, including its structure and operations.
      2. **Display Tree Buttons:** Create a button for each saved tree, labeled with the tree's root value,
      with the minimum root value displayed first (priority queue ordering).
      3. **Load a Tree on Click:** Load the clicked tree and make it the active tree in the visualizer.
## Contributing

Contributions are welcome to enhance the functionality and features of the Red-Black Tree Visualizer.

**How to Contribute**

1. Fork the repository on GitHub.
2. Create a new branch for your feature or bug fix.
3. Write clear and concise commit messages.
4. Submit a pull request with a detailed description of your changes.


**Future Enhancements**

If you'd like to contribute, here are some ideas for future features:

1. Implement animations for rotations and recoloring during balancing.
2. Extend UI with advanced features using libraries like Dear ImGui.
3. Provide export/import functionality in formats like JSON.
4. We’re open to suggestions and contributions that improve usability and learning outcomes.
