## Note

This project is unfinished.

# Gartenzaun Encryption

This projects encrypts and decrypts text using the rail fence cipher ("Gartenzaun Cipher" in German).

## Usage

TODO

## Example

TODO

# Documentation

The main algorithm is implemented in the `gartenzaun_index_function(...)` in `gartenzaun.c`. This function maps a given index for a character in a given row of the rail fence to the position of the same character in a plain text string.

Example rail fence with key `5` (meaning 5 rows) and plain text `rail fence cipher test`

``` text
n | r a i l _ f e n c e _ c i p h e r _ t e s t
------------------------------------------------
0 | r       ⁸       c               r
1 | ¹ a     ⁶     n ² e           e   _
2 | ²   i   ⁴   e   ⁴   _       h       t
3 | ³     l ² f     ⁶     c   p           e   t
4 | ⁴       _       ⁸       i               s
```

It can be noticed that the size of every gap between a character with an even and an uneven index doubles in size with every passing row.
This behavior can be described as `2 * n`.
For example in row `n=1` between `n` while `e` is a gap of `²` and in row `n=3` between `f` and `c` is a gap of `⁶`.

The same logic can be applied for the gap between uneven and even indexes but this time its reversed. Instead of increasing with row number the gap size is decreasing with increasing row number, starting from the maximum gap size.
The maximum gap size can be described as `key + (key - 2)` and the resulting formula for the  gap size is  `key + (key - 2) - 2 * n`.

Additionally in every row before index `1` a gap can be found. This gap corresponds to the current row number and therefore can be described with simply `n`.

The algorithm in `gartenzaun_index_function(...)` simply counts the amount of uneven and even indexes up (for this example called `a` and `b`) until the desired index, multiplies those with the corresponding gap size for the current row and then sums up both products up and adds the initial starting gap.

The final formula is `n + a * (2 * n) + b * (key + (key - 2) - 2 * n)`.

For the `n=0` (first) and `n=key-1` (last) rows there is always only one type of gap. In those cases the formula can be shortened to:

- `n + i * (key + (key - 2) - 2 * n)` for `n = 0`

- `n + i * (2 * n)` for `n = key - 1`
