Function naming
===============

Each function, function pointer and function reference in TheLibrary must be
named according to a defined naming scheme.

The naming scheme in TheLibrary has the following goals in mind(it is subjective
whether it actually accomplishes these goals):

- To be able to infer a rough estimate of what a function does based on its name.
- To be able to tell the full argument list of a function only from its name. What each type is and in what order.
- To be able to tell how each argument is related to what a function does, whether an argument is used as an input, an output or as an input and output only from its name.
- To be able to know the return value of a function and what it represents.

To achieve this the naming scheme in TheLibrary requires that functions have a
predetermined name based on various rule that differ based on what the function
is meant to do.

Spelling
--------
Fist off, spelling, that is how each word in a function name is spelled.

Functions
*********
NormalFunctionsNeedToBeSpelledInPascalCase.

Function pointers and references
********************************
Function pointers and references need to be spelled based on their scope, which
is documented at :ref:`Variable naming`

Form
----
Second off, the form of the function name, that is what each word represents and
the rules that come into play for determining what the function actually needs
to look like.

Currently, in TheLibrary there are 2 function forms:

- Commands, when you call these types of functions you are demanding that a certain specific action be taken, such as adding a node or finding an index.
- Statements, when calling these functions you claim that a certain condition is true, such as this array has no items or this queue is full.

.. //TODO: Should callbacks have a place here

Most functions will fall under the first form, while only very specific and a
small portion of functions will fall under the second form.

Commands
********
Most functions will belong in this form. Commands are used to do one very
specific action on a specific set of data. They are comprised of three parts:

#. Action
#. Arguments
#. Elaboration

Where the function looks like this: <Action><Arguments>[_Elaboration]

(Everything in <> is required, everything in [] is optional)

.. //TODO: Provide examples of command functions

Action
^^^^^^
The action of a command function is what that function actually does. The action
must be any of the values in the table bellow. The action determents what a
given function does and how. It also defines the return value of a function.

.. //TODO: Complete the action table

+---------------+
| Action        |
+===============+
| Allocate      |
+---------------+
| Create        |
+---------------+
| Find          |
+---------------+
| Get           |
+---------------+
| Destroy       |
+---------------+
| Deallocate    |
+---------------+

Arguments
^^^^^^^^^
After the action is specified, next comes the argument list. The argument list
is made up of the type names of each argument, in the order in which the are
defined in the function signature, following a preposition that tells you how
an argument is used, either as an input(From), output(To), or both(Using).

Additionally, the "On" word may be used to specify on what condition an argument
is used. If an argument is used with "On" then it is a non const reference.
The form of this is <Argument type>On<Condition>.

TODO: Formal way of defining conditions, and what even is a condition?

TODO: "As" for descriptions.

Elaboration
^^^^^^^^^^^
Finally at the end of a function name an elaboration can be specified. The
elaboration is optional and may not be included.

The elaboration must be prefixed with an underscore(_). After that any text may
follow, with the only rule being that it must be spelled in the same way as the
rest of the function. Multiple underscores are allowed after the initial one.

Statements
**********
The only functions that belong is this category are going to be the ones that
return a boolean and take in all of their arguments are const references. They
are primarily used for testing whether a particular condition holds true for
some arguments, such as for example, does an array have any items, or are 2
chucks of memory the same.

TODO: Add
