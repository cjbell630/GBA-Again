learn about libfat - only slightly touched on in the tutorial. Could allow for pulling files directly rather than hard coding them.

data arrays basically always should be const - this is because the default array storage location is less than half the size of the gba screen at 16bpp. Making it a const puts it in ROM which has plenty of space.
Besides, it should be a const anyway bc im not gonna change it
just a warning in case i for some reason do something really stupid sometime

raw2c.exe and bin2s.exe convert raw and bin files to c files (located somewhere in devkitarm)
usenti would be good since I'm basically making the files from scratch. located in documents>gba dev tools

GBACrusher can be used to compress non-image files:
http://www.coranac.com/files/gba/GBACrusher.zip



Imporatant:
So please, do yourself a favor and do not #include every file you have into main.c or its moral equivalent. Put function and variable definitions in separate source files to be compiled separately and linked later.

Instead:
Do separate files. Define functions in the source file (ex. util.c) as normal.
At the top of the main file, or whatever file will be calling those functions, redeclare them with no brackets, just a semicolon.
NOTE: I think the above line is only necessary for editing purposes. Maybe consider commenting it out each time!
Cmake.txt does not need to be modified. The Makefile in multiple_code_files should work.
CLion should be able to handle this without errors if you declare at the top. However, you won't be able to get documentation or source information.
There might be a way to fix this, but even though the author of the tutorial said it was better in every way (and it seems it is), I can't find anything online where people don't use #include. Idk.

TLDR: The #include directive is only to be used for files with preprocessor directives and declarations and type definitions. Oh, and inline functions. Those are okay there too.


Idea for project structure:

```
.main directory
+-- source
|   +-- main.c
|   |   +-- main method, sets up and invokes menu
|   +-- menu.c (eventually invokes something in game.c)
|   +-- game.c
+-- resources
|   +-- ... (binary data for gba to use, gfx sound etc)
+-- external (think of better name)
|   +-- ... (contains viewable graphics and sound)
```


# Left off at: #
[5.4.5. Data alignment][1]

[1]: https://www.coranac.com/tonc/text/bitmaps.htm#ssec-data-align