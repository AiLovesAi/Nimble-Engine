# Functions:

* Nimble engine functions should begin with "n", including function macros and wrappers.
* Functions should be prototyped in the following way, including the Doxygen description:
```C
/**
 * @brief [Brief description]
{Optional:} * [Description]
 *
 * Example:
 * @code
 * [Clear example]
 * @endcode
 *
{As needed:} * @param[in/out] [Parameter] [Description of how parameter affects function]
{As needed:} * @return [Description of what is returned]
 *
{Optional:} * @note [Note]
 */
{Optional:}[NIMBLE_EXTERN or NIMBLE_INLINE]
[Return type]
[Function name]([Param1],
       [Param2]
       )
{Optional:}[Attributes];
```
Note that if a function only takes one paramater (or void, which must be specified), it should not need a new line for the parenthesis. The semicolon must not be on a new line. There should not be an empty line before the end of the Doxygen comment.

* Function prototype parameter names must match that of their source code.

# Variables:

* Pointers should be paired with the variable name: `void *name`
* String variable names must end with "Str".
* Variables describing the length of a string must end in "Len".
* Strings that define error info must start with "einfo".
* All variables, enumerators, structures, unions, structure/union members, typedefs, function parameters, and macro definitions declared in header files must include a Doxygen description.

# Files:

* No line shall be more than 80 characters long unless it is clearly unreasonable to do so (a variable cannot be declared following other rules). The only exception is inline comments.
* Continued lines shall start with at least one space more than the previous line, or the start of the line, to denote that the line is continued.
* The first non-comment or non-space in header files must be a C++ wrapper:
```C
#ifdef __cplusplus
extern "C" {
#endif
```
* The last non-comment or non-space in header files must close the C++ wrapper:
```C
#ifdef __cplusplus
}
#endif
```
* All files must end with an empty line, followed by a comment with the file's name, followed by another new line:
```C

// [FileName]

```
* All files must start with an include of NimbleLicense.h, followed by a comment block in the following format:
```C
/*
 * [FileName]
 * Nimble Game Engine [Product (Library, Application, etc.)]
 *
 * Created by [Author] on [YYYY-MM-DD].
 * Copyright (C) [YYYY] [Author] {Optional:}<[Email]>
 *
 */
```
* All header files must have a Doxygen file description:
```C
/**
 * @file [FileName]
 * @author [Author]
 * @copyright
 * @parblock
 * [Complete copyright license]
 * @endparblock
 * @date [YYYY-MM-DD]
 *
 * @brief [Brief description]
{Optional:} * {Description}
{Optional:} * @note [Note]
 */
```
