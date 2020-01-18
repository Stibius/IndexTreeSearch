# Indexing of records using trees

### Introduction:

In this project, you will create a C++ program that will store information about a university/college/school roster in an array list and uses indexes to access records quickly.

Each student record will be stored in the array list in order of student ID. This means that, when we need to retrieve a student record based on student ID, we can use binary search. But what happens when we need to look up a student by last name, or date of birth? We would have to sequential search through the array until we find a match. Unless we have indexes!

An index contains two data: the searched value (or key), and its position in the array. This way we can keep the index sorted by key and retrieve the position of the record in the array, without having to create duplicates of the records.

### Input and Output:

This program will need two input files to work: a file with the student records that will fill the array list, and a file with the key(s) that will need to be retrieved.

Each student record will include (separated by comma):

- Student ID (string)
- First name (string)
- Last name (string)
- Date of birth (date)
- Major (string)
- GPA (float)

Labels will be used in the key file to identify what field to search, followed by ":"

- ID
- FIRSTNAME
- LASTNAME
- DOB
- MAJOR
- GPA

### Example of input file for student records:

    03985, Carita, Palencia, 1988-06-14, CS, 3.24
    11122, Nannie, Usrey, 1995-10-12, Math, 2.65
    … (more records)

### Example of input file for keywords:

    LASTNAME: Palencia
    
The output file should include the full retrieved record (or records, in case of multiple matches/keys), followed by the number of accesses necessary to retrieve the record searching the array list and the one achieved using indexes.

If no record is found, print "No record found for <LABEL> <key>", followed by the accesses necessary to determine that the record was not in the database.

### Example of output file:

    03985, Carita, Palencia, 1988-06-14, CS, 3.24 
    Without index: 22 accesses
    With index: 4 accesses

### Example of output file for missing record:

    No record found for LASTNAME Alvarez 
    Without index: 100 accesses
    With index: 7 accesses

The result should be written on another text file (output file), provided on the command line. 

### Usage:

The general call to the executable (search_roster in this example) is as follows:

    search_roster "A=<file>;B=<file>;C=<file>"
    
Call example with two input files and another output file:

    search_roster "A=database.txt;B=keyword.txt;C=c.out"
    
### Filling the array list with student records:

Your first step in this project will be reading the first input file and store its content in an array list. You can assume a maximum of 100 entries.

The array should store objects of an appositely designed "student" class. The class should include the following member attributes:

- Student ID (string)
- First name (string)
- Last name (string)
- Date of birth (date)
- Major (string)
- GPA (float)

The date of birth will be stored using another custom class "date" with 3 member attributes:

- Day (int)
- Month (int)
- Year (int)

Both classes should be complete with all the necessary method to create and manipulate the objects.

The array list must be sorted by student ID.

### Creating indexes:

After filling the array completely, you must create index trees for each attribute in the student record. Each node of the tree will include the key and the location (array index) where to retrieve the record.

Each node should be a structure template with the following attributes:

- Key (Type)
- Index (LinkedList)
- rlink (pointer to right subtree)
- llink (pointer to left subtree)

Index should be a linked list so that every key in the tree remains unique, but, in case of records with the same key, it will be possible to store multiple locations by adding them to the linked list in the node.

Nodes must be organized in a binary AVL tree.

### Retrieving records:

When asked to retrieve a record, you will look for it in the array list using linear search, and then using the indexes in the binary tree. Checking the value stored in an item of the array or in a node of the tree counts as 1 access. You will need to count all the accesses necessary to find the record and add them to your output file. For example, if the item we are looking for is the 40th element of the array, we will need 40 accesses to find it using linear search.

Note that you need to account for one extra access to the array when using indexes! For example, if I visit 3 nodes in the binary tree before finding the key, then I need one more access to retrieve the record from the array list using the index, for a total of 4 accesses. You do not need to add the accesses to the nodes of the linked list in case a key is associated with multiple indexes.

Multiple records, or records retrieved using different keys, in case the file includes more than one, should be separated by 1 line when printed.

You may be asked to retrieve a record using the student ID. In that case, you should use binary search directly on the array list and the output should include only the number of accesses without indexing.

### Bonus:

As a bonus, you will be asked to retrieve not an exact match, but all records within a range (inclusive). Each individual record should be followed by the number of accesses necessary to retrieve it:

Example:

    GPA: 3.00-4.00

Result:

    03985, Carita, Palencia, 1988-06-14, CS, 3.24 
    Without index: 22 accesses
    With index: 4 accesses

    00987, Hyman Tschanz, 1990-06-20, Math, 3.92 
    Without index: 12 accesses
    With index: 2 accesses


