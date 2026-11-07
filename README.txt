Project 2 - Milestone 1

A C++ console program for facility ID lookup through a custom hash table,
undirected campus graph display and BFS reachability, and an ordered general
department tree with insertion, search, hierarchy display, and preorder.

Build from the repository root on Linux / UNT CELL:
    mkdir -p build
    g++ -std=c++11 -Wall -Wextra -Wpedantic src/*.cpp -o build/campus

Run from the repository root:
    ./build/campus
    ./build/campus testdata/collision
    ./build/campus testdata/
The default directory is data/ relative to the current working directory.
The optional directory accepts a trailing slash or no trailing slash.
Quote directory paths containing spaces. No absolute paths are embedded.
From src/, pass ../data explicitly if running a locally built executable there.

Run tests from the repository root (Python 3 required):
    python3 tests/test_milestone1.py
    g++ -std=c++11 -Wall -Wextra -Wpedantic tests/hash_table_test.cpp src/HashTable.cpp src/FacilityRecords.cpp -o build/hash_table_test
    ./build/hash_table_test
The Python runner also accepts the compiled program path as its first argument.
It uses temporary directories for malformed, empty, and missing-file tests.

Layout:
    include/               Class declarations and shared file-input helpers
    src/                   Implementations and the M1 menu
    data/                  Original four input files, unchanged
    testdata/              Existing tests plus collision/ demonstration files
    tests/                 Repeatable M1 integration and custom hash-table tests
    build/                 Local executables (ignored; not part of submission)
    design_document.txt    Hash formula, collisions, representation, modules
    test_results.txt       Test inputs, expected/actual results, pass/fail
    CONTRIBUTIONS.txt      Existing team contribution statements, preserved

Menu options 1-9 perform M1 operations; 10 exits. Option 0 also exits.
Names accept spaces. Matches ignore ASCII capitalization and outer whitespace.
Menu department additions are in memory only; input files are never rewritten.
Final-only searches, reports, tree statistics and traversals are not added.
The pre-existing Final shortest-path method and commented Final menu remain
as reference and are not exposed by the M1 menu or validated here.

Validation status:
    Built and tested in this Linux cloud workspace; see test_results.txt.
    UNT CELL execution and the team's live demonstration remain to be done.
    Contribution statements and commit authorship are not rewritten to imply
    that team members performed this AI-assisted work. Team members must
    verify and accurately complete their own contribution evidence.
