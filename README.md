# DiffFile - Edit Distance Calculation Using Dynamic Programming

This project implements a **dynamic programming solution** to calculate the **edit distance** between two strings, which represent two text files. The goal is to determine the minimum number of edit operations required to convert one string into another. The edit operations are defined as:

- **Delete**: Remove a character (xi → λ)
- **Insert**: Add a character (λ → yj)
- **Replace**: Replace one character with another (xi → yj)

### Problem Description

Given two strings `X` and `Y` representing the contents of two text files, we want to calculate the **edit distance** between them and generate a `Diff` file that shows the necessary edit operations.

- **Input**: The strings `X` (In1) and `Y` (In2) are read from two text files.
- **Output**: The program computes the edit distance and outputs a `Diff` file, containing the operations needed to convert `In1` into `In2`.

### Diff File Format

The `Diff` file contains the edit operations in the following format:

- **Text Removal**: `$-text$`
- **Text Addition**: `$+text$`
- **Text Replacement**: `$#text1$text2$` (where `text1` is replaced by `text2`)

### Conditions for the Diff File

- Consecutive operations of the same type should be grouped together:
  - Incorrect: `$+a$$+b$`
  - Correct: `$+ab$`
  - Incorrect: `$-a$$-b$`
  - Correct: `$-ab$`
  - Incorrect: `$#a$x$$#b$y$`
  - Correct: `$#ab$xy$`

- The number of edit operations must be minimized.

### Function to Implement

int Diff(string in1, string in2, string &out);

This function computes the edit distance between two input strings (`in1` and `in2`) and returns the number of edit operations. The `out` string contains the operations needed to transform `in1` into `in2`.

### Example

#### Input 1 (In1):

#include <stdio.h>
int main() {
    printf("Hello World!");
    return 0;
}

#### Input 2 (In2):

#include <stdio.h>
int main() {
    printf("Hello XY World!");
    return 0;
}

#### Output (Diff File):

Distancia d’edició: 3
#include <stdio.h>
int main() {
    printf("Hello$+ XY$ World!");
    return 0;
}

### Requirements

C++ compiler for running the code.
