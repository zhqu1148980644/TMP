---
title: Exchange Seats
date: 2021-01-04
---
SQL架构
Mary is a teacher in a middle school and she has a table seat storing students' names and their corresponding seat ids.

The column id is continuous increment.
 

Mary wants to change seats for the adjacent students.
 

Can you write a SQL query to output the result for Mary?
 

+---------+---------+
|    id   | student |
+---------+---------+
|    1    | Abbot   |
|    2    | Doris   |
|    3    | Emerson |
|    4    | Green   |
|    5    | Jeames  |
+---------+---------+
For the sample input, the output is:
 

+---------+---------+
|    id   | student |
+---------+---------+
|    1    | Doris   |
|    2    | Abbot   |
|    3    | Green   |
|    4    | Emerson |
|    5    | Jeames  |
+---------+---------+
Note:
If the number of students is odd, there is no need to change the last one's seat.


#### Solutions


1. ##### CASE

```sql
# Write your MySQL query statement below
SELECT (CASE
            WHEN id = cnt AND cnt & 1 THEN id
            WHEN id & 1 THEN id + 1
            ELSE id - 1
        END) AS id, student
FROM seat, (SELECT COUNT(*) AS cnt FROM seat) AS c
ORDER BY id
```


2. ##### RANK

```sql
# Write your MySQL query statement below
SELECT RANK() OVER(ORDER BY (id-1)^1) AS id, student FROM seat
```

3. ##### IF

```sql
# Write your MySQL query statement below
SELECT IF(MOD(id, 2), IF(id = cnt, id, id + 1), id - 1) AS id, student
    FROM seat, (SELECT COUNT(*) AS cnt FROM seat) c
    ORDER BY id
```