# TermiDS: C-DSA Logic Guide (Senior View)

Welcome to TermiDS! This is a terminal-based, menu-driven application written in C designed to help visualize and understand various Data Structures and Algorithms (DSA). Think of it as an interactive, text-based DSA textbook chapter, complete with step-by-step visualizations for many operations.

## ✨ Features

* **Modular Design:** The project is structured with separate `.c` and `.h` files for different DSA units (Lists, Stacks/Queues, Trees, Searching/Sorting, Graphs) for better organization and maintainability.
* **Menu-Driven Interface:** Easy navigation through different DSA topics grouped by "Sessionals" and "Units".
* **Step-by-Step Visualizations:** For implemented algorithms, the console output provides detailed, step-by-step walkthroughs showing:
    * Stack states (vertical container view) for relevant operations (Infix/Postfix, Reversal, Balancing Symbols).
    * Queue states (linear view) for BFS.
    * Linked List structures (SLL, DLL, CLL) with pointers.
    * Tree structures (BT, BST, Expression Tree) using ASCII art.
    * Array states with pointers (Binary Search) or after intermediate steps (Sorting algorithms, Hash Table).
    * Graph traversals (DFS stack simulation, BFS queue updates).
    * Dijkstra's algorithm distance updates.
* **Written in C:** Uses standard C libraries and GCC extensions (like nested functions, though these might be refactored later for portability).

## 🚀 Getting Started

Follow these steps to get TermiDS running on your local machine.

### Prerequisites

* **C Compiler:** You need a C compiler installed, specifically **GCC** (like the one included with **MinGW** on Windows), as the project was developed using it. You can download MinGW-w64 from [https://www.mingw-w64.org/](https://www.mingw-w64.org/). Ensure `gcc` is added to your system's PATH environment variable.
* **Git:** You need Git installed to clone the repository. [https://git-scm.com/](https://git-scm.com/)

### Installation & Running

1.  **Clone the Repository:**
    Open your terminal or Git Bash and navigate to the directory where you want to store the project. Then, run:
    ```bash
    git clone [https://github.com/RustyLegend/TermiDS.git](https://github.com/RustyLegend/TermiDS.git)
    ```
2.  **Navigate into the Project Directory:**
    ```bash
    cd TermiDS
    ```
3.  **Compile the Project:**
    A batch script is provided to compile all necessary `.c` files. Run it from the terminal within the `TermiDS` directory:
    ```bash
    ./compileAll.bat
    ```
    (Or just `compileAll.bat` if you are using Windows Command Prompt).
    This will use `gcc` to compile all source files and create an executable named `termi_ds.exe` (or similar, depending on the script) in the same directory.
    * **Note:** If you encounter errors like `cannot open output file termi_ds.exe`, ensure no previous instance of the program is running and check that your antivirus isn't blocking the compiler from creating the executable file. Adding the project folder to your antivirus exclusions might be necessary.
4.  **Run the Executable:**
    Once compiled successfully, run the program from the terminal:
    ```bash
    ./termi_ds.exe
    ```
    (Or `termi_ds.exe` on Windows Command Prompt).

The TermiDS menu should now launch in your terminal!

## 💡 Implemented Topics (with Visualizations)

As of now, the following DSA topics are fully implemented with step-by-step visualizations:

* **Unit 1: Lists**
    * Array Max/Min
    * Singly Linked List (All Ops: Insert/Delete Front, End, Pos, Value)
    * Doubly Linked List (All Ops: Insert/Delete Front, End, Pos, Value)
    * Circular Linked List (Singly & Doubly: Insert/Delete Front, End, Pos, Value)
    * Polynomial Creation (Term-by-term, sorted insert, combine like terms)
    * Polynomial Addition/Subtraction
* **Unit 2: Stacks & Queues**
    * Stack Operations (Array-based, Vertical Viz)
    * Queue Operations (Circular Array-based)
    * Infix to Postfix Conversion (Stack Viz)
    * String Reversal using Stack (Stack Viz)
    * Postfix Evaluation (Stack Viz)
    * Balancing Symbols (Stack Viz)
    * Count Sort (Frequency/Position Viz)
    * Radix Sort (Pass-by-pass Viz)
* **Unit 3: Trees**
    * Binary Tree (Manual Build, ASCII Viz)
    * Binary Search Tree (Insert, Traversals)
    * Expression Tree (Build from Postfix, Traversals, ASCII Viz)
* **Unit 4: Hashing, Searching & Sorting**
    * Hash Table (Separate Chaining, Insert/Delete/Search, Table Viz)
    * Linear Search
    * Binary Search (Array Pointer Viz)
    * Insertion Sort (Pass-by-pass Viz)
    * Quick Sort (Lomuto Partition Viz)
    * Merge Sort (Merge Step Viz)
    * Heap Sort (Heap Build & Extraction Viz with Tree Viz)
* **Unit 5: Graphs**
    * Depth First Search (DFS) (Adjacency Matrix, Stack Viz)
    * Breadth First Search (BFS) (Adjacency Matrix, Queue Viz)
    * Dijkstra's Shortest Path (Adjacency Matrix, Distance Update Viz)


---

Happy coding and visualizing!
