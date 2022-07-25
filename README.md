# Kick Covid in the _____. - CS 2341 Final Project

Developed and maintained by Kirk Watson.

Email: klwatson@smu.edu

Class: Data Structures CS 2341 - Fall 2020

Southern Methodist University

## Functionality

This is a COVID-19 Research Article Search Engine written in C++ and built using CMAKE that utilizes a self-implemented AVLTree for word storage and self-implemented HashTable for author storage.
The documents are ranked by the term-frequency/inverse document frequency (tf/idf) metric and indexed with a command line user interface.
After indexing, a user can enter a search query with multiple keywords and view statistics of the index.

## How to Use

Compile and build with CMAKE. There are no command-line arguments.

A corpus of 3,000 documents is included in this repository.
If interested in utilizing the full dataset, click here to download: [CORD -19](https://www.semanticscholar.org/cord19/download).
To run the application with a different dataset, simply change the value of the variable **filePath** on line 17 in **SearchEngine.h** to the dataset's file path.

Upon starting the application, the user will need to create the index using the interface.
After parsing the documents, the user can use the search engine, view index statistics, or save the index to a persistence file for later use.

To make a search query, the user can utilize the following operators: "AND", "OR", "NOT", and "AUTHOR".
* AND: Returns documents that contain all words in the query.
* OR: Returns documents that contain at least one word in the query.
* NOT: Returns all documents that do not contain the particular word. Can be compounded with AND or ORs.
* AUTHOR: Returns all results of particular author. When AUTHOR is preceded by a word, the results are documents that contain that word from that author.

Example Search Queries

`chicken`

`AND chicken dog`

`OR chicken dog`

`dog NOT cat`

`AND chicken dog NOT cat`

`AUTHOR duncan`

`chicken AUTHOR duncan`
