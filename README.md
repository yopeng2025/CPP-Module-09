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
`[7, 3, 5, 2, 9, 1, 6]`
- pairing result: `(7,3), (5,2), (9,1), (6)` (last one is leftover)
- per-pair normalization (swap if needed) so each pair is `(small, big)`
- main chain built from all `big` values (sorted)
- insertion of `small` values into the main chain using `lower_bound` (binary search)
- Jacobsthal-driven insertion order (which small element is inserted)
- final insertion of the leftover element (if any)


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
