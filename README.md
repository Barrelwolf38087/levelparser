# Unnamed Level Parser
This is a parser for my tile-based level format. Tiles are grouped into
"chunks" of 16x16. These chunks are assigned coordinates on a cartesian plane.
The point of reference for these coordinates is the top left corner of the chunk.
This is because the first tile in a chunk is the top left one.

## Format outline
* Format version (2 bytes, unsigned int)
* Null-terminated UTF-8 title string
* Number of chunks (5 bytes, unsigned int)
* Table mapping chunk coordinates to indices in the chunk array (size derived from number of chunks)
* Array of raw chunk data (size derived from number of chunks)

## Limitations
* No support for entities (yet)
* Theoretical limit of 2<sup>32</sup> chunks (a lot!)
* Theoretical limit of 65536 (2<sup>16</sup>) tile types
* No compression
    * Each chunk is 512 bytes, so a level containing the theoretical maximum
    number of chunks would weigh in at more than 2 Terabytes.
    * If I ever end up using this for something big enough that file size is a
    problem, I will implement compression.
