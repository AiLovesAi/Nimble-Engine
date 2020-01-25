#  Bug List

* There is a small chance that when the game closes, it fails to close threads and crashes. This has yet to be discovered why this happens and testing is difficult due to how rarely it occurs.

* Texture or world object allocation leaves behind 23 bytes of data when being freed

* Probably a lot of memory allocation issues; check with Valgrind on Linux
