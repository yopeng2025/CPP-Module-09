# CPP Module 09


## ex00 — BitcoinExchange (map)

### 1) What is `std::map` and why it fits here?
`std::map<Key, Value>` is an **ordered associative container** (usually a Red–Black Tree):

- **Unique keys**, automatically sorted by key
- `find/insert/erase` are typically **O(log N)**
- Great for “lookup by key” problems (here: **date → exchange rate**)

In this exercise, the common approach is:

- **Key**: `YYYY-MM-DD` (string)
- **Value**: exchange rate (`double`/`float`)

### 2) How it’s used in code
**(a) Load the database (CSV) into a map**
- Parse each line like: `date,exchange_rate`
- Store: `rates[date] = rate`

**(b) Read the input file and query by date**
For each input line like: `date | value`:
- validate date/value format and constraints
- if the date does not exist exactly in the map, select the **closest previous date**:
  - use `lower_bound(date)` to find the first key `>= date`
  - if it’s not an exact match, step back one iterator to get the last date `< date`

### 3) Example: why `lower_bound` helps
Database:
- 2021-01-01 → 30000
- 2021-01-03 → 33000

Query `2021-01-02`:
- `lower_bound("2021-01-02")` points to `2021-01-03`
- step back → `2021-01-01`
- use the rate at `2021-01-01` for the computation



## ex01 — RPN (stack/list)

### 1) What is RPN?
**RPN (Reverse Polish Notation)** places operators *after* operands, so parentheses are unnecessary.

Example:
- Infix: `(3 + 4) * 5`
- RPN: `3 4 + 5 *`

### 2) Why a stack?
RPN evaluation naturally follows a **LIFO** pattern:

- read a number → push to stack
- read an operator → pop two numbers `b` then `a`, compute `a op b`, push result back
- at the end, the stack must contain **exactly one value** (the final result)

### 3) Logic
- tokenize input (split by spaces or parse char-by-char)
- validate:
  - invalid tokens
  - insufficient operands (stack size < 2 when an operator appears)
  - division by zero
  - final stack size != 1
- compute operators: `+ - * /`

### 4) Example (stack evolution)
Expression: `3 4 + 5 *`

- push 3 → `[3]`
- push 4 → `[3, 4]`
- `+` → pop 4 and 3 → push 7 → `[7]`
- push 5 → `[7, 5]`
- `*` → pop 5 and 7 → push 35 → `[35]`

Final answer: `35`



## ex02 — Jacobsthal + Ford–Johnson (PmergeMe)
### 1) Fibonacci vs Jacobsthal
**Fibonacci**
- `F(0)=0, F(1)=1`
- `F(n)=F(n-1)+F(n-2)`

**Jacobsthal**
- `J(0)=0, J(1)=1`
- `J(n)=J(n-1)+2*J(n-2)`

**Key difference**
- Jacobsthal grows in a different pattern and is commonly used in Ford–Johnson-related explanations to define an **insertion order** that reduces the number of comparisons (closer to optimal in theory).

### 2) Ford–Johnson Sort / Merge-Insertion Sort
A typical Ford–Johnson-style strategy:

1. **Pairing**: group elements into pairs
2. **Sort inside each pair**: make sure `(small, big)` is consistent
3. **Build the main chain**: sort all “big” elements to form a sorted backbone
4. **Insert the small elements**: insert “small” elements into the main chain using **binary insertion**, in an order guided by **Jacobsthal indices**
5. If there is an **odd leftover element**, insert it at the end

### 3) Example

`[25，24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0]`
1. **swap**
- order = 1 `(24 25) (22 23) (20 21) (18 19) (16 17) (14 15) (12 13) (10 11) (8 9) (6 7) (4 5) (2 3) (0 1)`
- order = 2 `(22 23)(24 25) (18 19)(20 21) (14 15)(16 17) (10 11)(12 13) (6 7)(8 9) (2 3)(4 5)`     `(0 1)`
- order = 4 `(18 19 20 21) (22 23 24 25) (10 11 12 13) (14 15 16 17) (2 3 4 5) (6 7 8 9)`           `(0 1)`
- order = 8 `(10 11 12 13 14 15 16 17) (18 19 20 21 22 23 24 25)`               `(2 3 4 5 6 7 8 9)` `(0 1)`
2. **insert**
- order = 8
            `main = [17 25]` 
            `pend = [9]`
            `insert 9 -> main = [9, 17, 25]`
  
            `rebuild = [(2 3 4 5 6 7 8 9), (10 11 12 13 14 15 16 17), (18 19 20 21 22 23 24 25), (0 1)]`
  
            `vec = rebuild`
  
            `vec = [2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 0 1]`
  
 - order = 4
            `vec = [(2 3 4 5) (6 7 8 9) (10 11 12 13) (14 15 16 17) (18 19 20 21) (22 23 24 25) (0 1)]`
            `main = [5 9]`
            `pend = [13]`
            `main += [17]`
            `pend += [21]`
            `main += [25]`

            `main = [5 9 17 24]`
            `pend = [13 21]`
      inset
            `idx = J(3) - J(2) = 3 - 1 = 2` *insert 2 numbers at once from right to left
            `main = [5 9 17 21 24]`
            `pend = [13]`
            `main = [5 9 13 17 21 24]`
            `pend = [NULL]`

            `rebuild = [(2 3 4 5) (6 7 8 9) (10 11 12 13) (14 15 16 17) (18 19 20 21) (22 23 24 25) (0 1)]`
            `vec = rebuild = [2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 0 1]`
- order = 2
            `vec = [(2 3) (4 5) (6 7) (8 9) (10 11) (12 13) (14 15) (16 17) (18 19) (20 21) (22 23) (24 25) (0 1)]`
            `main = [3 5]` `main += [9]` `main += [13]` `main += [17]` `main += [21]` `main += [25]`
            `pend = [7]`  `pend += [11]` `pend += [15]` `pend += [19]` `pend += [23]` 
            `main = [3 5 9 13 17 21 25]`
            `pend = [7 11 15 19 23]`
      insert 
            idx = J(3) - J(2) = 3 - 1 = 2 *insert 2 numbers at once from right to left
            `pend[1] = 11` `pend[0] = 7`
            search range = J(3) = 3  
            `main = [search(3 5 9) 13 17 21 25]`
      insert`main = [3 5 9 11 13 17 21 25]`
            search range = J(4) = 5
            `main = [(3 5 9 11 13) 17 21 25]`
      insert`main = [3 5 7 9 11 13 17 21 25]`

             idx = J(4) - J(3) = 5 - 3 = 2
             `pend[1] = 19` `pend[0] = [15]`
             search range = J(6) = 21
             `main = [search(3 5 7 9 11 13 17 21 25)]`
      insert `main = [3 5 7 9 11 13 17 19 21 25]`
             search range = J(7) = 43
             `main = [search(3 5 7 9 11 13 17 21 25)]`
      insert `main = [3 5 7 9 11 13 15 17 19 21 25]`

              idx = J(5) - J(4) = 11 - 5 = 6
              `pend[0] = 23`
      insert `main = [3 5 7 9 11 13 15 17 19 21 23 25]`

      rebuild = [(2 3) (4 5) (6 7) (8 9) (10 11) (12 13) (14 15) (16 17) (18 19) (20 21) (22 23) (24 25) (0 1)]
      vec = rebuild = [(2 3) (4 5) (6 7) (8 9) (10 11) (12 13) (14 15) (16 17) (18 19) (20 21) (22 23) (24 25) (0 1)]

- order = 1
          `main = [2 3 5 7 9 11 13 15 17 19 21 23 25]`
          `pend = [4 6 8 10 12 14 16 18 20 22 24]`

          idx = J(3) - J(2) = 3 - 1 = 2
          `pend[1] = 6` `pend[0] = 4`
          search range = J(3) - 0 = 3
          `main = [search(2 3 5) 7 9 11 13 15 17 19 21 23 25]`
    insert`main = [2 3 5 6 7 9 11 13 15 17 19 21 23 25]`
          search range = J(4) - 1 = 5 - 1 = 4
          `main = [search(2 3 5 6) 7 9 11 13 15 17 19 21 23 25]`
    insert`main = [2 3 4 5 6 7 9 11 13 15 17 19 21 23 25]`

          idx = J(4) - J(3) = 5 - 3 = 2
          `pend[1] = 10` `pend[0] = 8`
          search range = J(4 + 2) - 0 = 43 
          `main = [search(2 3 4 5 6 7 9 11 13 15 17 19 21 23 25)]`
    insert`main = [2 3 4 5 6 7 9 10 11 13 15 17 19 21 23 25]`
          search rang = J(4 + 3) - 1 = 84
          `main = [search(2 3 4 5 6 7 9 11 13 15 17 19 21 23 25)]`
    insert`main = [2 3 4 5 6 7 8 9 10 11 13 15 17 19 21 23 25]`

          idx = J(5) - J(4) = 11 - 5 = 6
          `pend = [12 14 16 18 20 22]`
          search range = J(5 + 4) - 0 = 171 
          `main = [search(2 3 4 5 6 7 8 9 11 10 13 15 17 19 21 23 25)]`
          ...
    insert`main = [2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 25]`

          idx = J(6) - J(5) = 21 - 11 = 10
          `pend = [24]`
          search range = J(6 + 5) - 0 = 683
          `main = [search(all ...)]`
    insert`main = [2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25]`
    insert odd
          `main = [0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25]`

          `rebuild = [0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25]`
          
    

## Build & Run

- **ex00**
  - `make`
  - `./btc input.txt`


- **ex01**
  - `make`
  - `./RPN "8 9 * 9 - 9 - 9 - 9 - 4 - 1 +"`

- **ex02**
  - `make`
  - `./PmergeMe 3 5 9 7 4`
