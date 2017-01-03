# factordistinct
Find a factorization of an integer into the largest number of distinct factors. For example 100 can be written as `2*5*10` and no other factorization of 100 has more than 3 distinct factors greater than 1.

# example

Here is a test run on some inputs.

```bash
$ factordistinct 1000 10010000000 4537367247103891200 1940321191818240000
```

```
1000: 2 4 5 25
10010000000: 2 4 5 7 8 10 11 13 25 125
4537367247103891200: 2 3 4 5 6 7 9 10 11 13 14 17 21 22 33 34 567
1940321191818240000: 2 3 4 5 6 7 8 9 10 11 12 14 15 18 21 27 35 54
```

