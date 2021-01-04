---
title: Find Customer Referee
date: 2021-01-04
---
SQL架构
Given a table customer holding customers information and the referee.

+------+------+-----------+
| id   | name | referee_id|
+------+------+-----------+
|    1 | Will |      NULL |
|    2 | Jane |      NULL |
|    3 | Alex |         2 |
|    4 | Bill |      NULL |
|    5 | Zack |         1 |
|    6 | Mark |         2 |
+------+------+-----------+
Write a query to return the list of customers NOT referred by the person with id '2'.

For the sample data above, the result is:

+------+
| name |
+------+
| Will |
| Jane |
| Bill |
| Zack |
+------+

#### Solutions

1. #####

```sql
# Write your MySQL query statement below
SELECT name
    FROM customer
    WHERE IFNULL(referee_id, 0) != 2
```

or

```sql
# Write your MySQL query statement below
SELECT name
    FROM customer
    WHERE referee_id IS NULL OR referee_id != 2
```

```sql
# Write your MySQL query statement below
SELECT name
    FROM customer
    WHERE id NOT IN (SELECT id FROM customer WHERE referee_id = 2)
```