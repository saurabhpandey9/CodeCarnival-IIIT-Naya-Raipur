# Problem 2:

## Description:

The city of wizards are under attack! They are attacked by their worst enemy, the Vampires!
And to defend his empire, the king of wizards summoned the most powerful and old wizard of
the kingdom, Kiatra.
Kiatra has a special spell of creating exact duplicates of him but he can only cast 4 such spells
simultaneously. Also, he needs 1 second before casting the next set of spells. So, for example
Kiatra casts 4 spells at time 0, he will cast the next 4 spells at time 1 since he needs 1 second
between each set of spells. Each spell creates another duplicate wizard capable of performing
the same spell.
The city of wizards can be represented as a N by N grid (N is always odd). Kiatra stands at
middle of the city and starts to cast spell at all the immediate neighboring cells (the four
neighbor cells which share a side with the Kiatra cell) which makes duplicate wizards in the four
cells. In the next second, the new wizards along with Kiatra again cast spells in their respective
immediate neighbors creating new wizards and this goes on. **Please note that only one wizard
will cast spells from each cell.** Also, the city is special! The borders are surrounded by
mirrors, so if a wizard is standing at a cell which is at the border of the city(the cells having
immediate neighbors less than 4) casts spell, the spell in the direction of the mirror will be
reflected and hit back the wizard and hence, the new duplicate wizard will be created at the cell
from where the spell was cast. The strength of a cell S is defined as the number of wizards
standing on the cell. This can be pictorially represented as (here each cell represents the
Strength of the cell S ):

|0|0|0|
|:--:|:--:|:--:|
|0|1|0|
|0|0|0|

At time t = 0


|0 |1 |0|
|:--:|:--:|:--:|
|1 |1 |1|
|0 |1 |0|


At time t = 1

|1| 3| 1|
|:--:|:--:|:--:|
|3 |5 |3|
|1 |3 |1|

At time = 2, please note that the cell strength at border summed to 3 because of reflection from
border.

|6 |7 |6|
|:--:|:--:|:--:|
|7 |9| 7|
|6 |7 |6|


At time = 3

The vampires are attacking from the air and each have a hitpoint H. Each vampire has been
already ordered to attack a specific cell only with coordinates (i, j). If Strength S of the cell is
greater than or equal to H at the time the vampire attacks the cell is safe.You are the minister to
the king and are ordered to determine if a particular cell can be defended by the wizards so that
if required help can be sent to Kiatra. Please note that initially at time t=0, Kiatra is standing at
the center is ready to cast his first set of spells in next second.

## Input:
Each input has the following format:

1. First line contains N, denoting the size of the city. Please note that N is always odd.
2. Second line contains Q the number of queries, each subsequent Q lines has following
        format:
    - Four spaced integers i, j, t, H where (i, j) denotes the ith row and jth column of the
    city (0 indexed), t denotes the time at which Vampire attacks and H denotes the
    hitpoint of the vampire

## Output:

For each query in a new line print “YES” (without quotes) if the cell can be defended else print
“NO”

### Constraints:

```
3 <= N <= 1000
1 <= Q <= 10**7
0 <= i, j <= N-1
0 <= t <= 10**5
0 <= H <= 10**5
```

### Sample Input 0:

```
3
3
1 1 1 1
2 1 5 3
2 2 10 3
```

### Sample Output 0:

```
YES
YES
NO
```
### Explanation:
Please refer to the above diagram to see strength S for different values of t, In the first
query H and S both are equal to one and hence the answer YES. Rest of the queries
are similar.
### Sample Input 1:
```
5
2
1 1 1 2
2 4 3 3
```
### Sample Output 1:
```
NO
YES
```
## Explanation:
For the first query, cell at (1,1) did not have even a single wizard at t=1 and hence
cannot be defended by the monster. In the second query, the cell at (2, 4) had 3 wizards
hence S = 3 and were able to defend against monster with H = 3.

## Code (In Python) :

```python
def f1(i, j, t, n):
    cent = (n//2, n//2)
    i -= cent[0]; j-= cent[1]
    i = abs(i); j = abs(j)

    ans = -1
    if i == 0 and j == 0:
        ans = 1
    elif i == 0 or j == 0:
        if i+j == t:
            ans = 1
        elif i+j < t:
            if i == n//2 or j == n//2:
                ans = 3
            else:
                ans = 2
        else:
            ans = 0
    else:
        if i+j == t:
            ans = 2
        elif i+j < t:
            if i == n//2  and j == n//2:
                ans = 2
            elif i == n//2 or j == n//2:
                ans = 1
            else:
                ans = 0
        else:
            ans = 0
    
    ans += max(t-1-(i+j), 0)*4
    if i!= 0 and j != 0 and (t-1) >= (i+j):
        ans += 4
    return ans


n = int(input())
p = int(input())
for h in range(p):
    i, j, t, h = map(int, input().strip().split())
    a = f1(i, j, t, n)

    if a >= h: print("YES") 
    else: print("NO")

```
