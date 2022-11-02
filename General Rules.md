General Rules
Use 4 spaces for aligning code instead of tabs. Caution: configuring the editor to size the tab character as four spaces is not enough. You must force the editor to insert four spaces when you press TAB.
Maximum line length must be set to 120 characters.
Avoid using inner classes unless they are very short and are only used in the particular class they're defined in.
Use of lambda expressions is encouraged but not mandatory.
Use of for-each structures, where applicable, is mandatory over user iterators or old style i=0->n-1.
Documentation
All classes and members must have Doxygen comments describing their usage and parameters and return value in the header file.

Naming scheme
Names should clearly express meaning and usage of the variable, method or class. Avoid using shortcuts! You have autocomplete functions in your IDE, use it! So don't use cmd instead of command or retVal instead of returnValue. The only exceptions are well established names for index iterators: i, j, k and coordinates names: x, y, z.

Variable Names
Local method variables must start with a lowercase character and follow the camel-case naming scheme: megaImportantVariable
Instance variables (non-static fields) must begin with a lowercase m (for "member") and follow the camel-case naming scheme: mMegaImportantField
Class variables (static, non-const fields) must begin with a lowercase s and follow the camel-case naming scheme: sMegaImportantStaticVariable
Class constants (static const fields) must be all uppercase and follow the snake-case naming scheme: MEGA_IMPORTANT_CONSTANT
In order to improve readability of the code, acronyms should not appear all caps in variable names: newUrlForFile instead of newURLForFile
Method Names
All method names (except for constructors) must start with a lowercase character and follow the camel-case naming scheme: doTheWork()

Structures Names
All class, structures, unions and enumumerations names must start with an uppercase character and follow the camel-case convention: MyMegaClass

Namespaces
Namespaces must be all lowercase and follow the snake-case convention: aces::ocr_engine

Bracketing
The bracketing style used is OTBS (One True Brace Style) with the observation that the open bracket is always at the end of the begin statement, even for method and classes:

class Foo {
}
instead of

class Foo 
{
}
There must ALWAYS be brackets placed after control blocks (like for and if), even if the controlled block has only one statement, with the exception of the case where the entire block is short enough to be written in one line. The following is acceptable:

for (vector<vector<uint8_t>> &myList : listOfLists) myList.clear();
This is not:


for (vector<vector<uint8_t>> &myList : listOfLists) 
    myList.clear();

Spacing
A space character must be inserted in the following situations:

before an open bracket;
after an open bracket (if there is something else on that line);
after the keywords for, if, else, while (in while blocks) and do (in do-while blocks);
before and after binary operators with the exception of the dot (.) operator.
Language Specific Requirements
Use #pragma once instead of old style macro include guards.
We prefer the use of references over pointers, when possible.
Use fixed width data types (int8_t, uint16_t) instead of default primitive types (int or unsigned short).
The use of auto type is permitted where the type is easy to determine by the reader.
We prefer the use of class constants and inline functions to preprocessor macros.
Code Formatting and Revision Control
Configure your IDE and ALWAYS run an automatic formatting operation on the written code before a Git commit.