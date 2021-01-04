---
title: Employee Bonus
date: 2021-01-04
---
SQL架构
Select all employee's name and bonus whose bonus is < 1000.

Table:Employee

+-------+--------+-----------+--------+
| empId |  name  | supervisor| salary |
+-------+--------+-----------+--------+
|   1   | John   |  3        | 1000   |
|   2   | Dan    |  3        | 2000   |
|   3   | Brad   |  null     | 4000   |
|   4   | Thomas |  3        | 4000   |
+-------+--------+-----------+--------+
empId is the primary key column for this table.
Table: Bonus

+-------+-------+
| empId | bonus |
+-------+-------+
| 2     | 500   |
| 4     | 2000  |
+-------+-------+
empId is the primary key column for this table.
Example ouput:

+-------+-------+
| name  | bonus |
+-------+-------+
| John  | null  |
| Dan   | 500   |
| Brad  | null  |
+-------+-------+

#### Solutions

1. ##### LEFT JOIN

```sql
# Write your MySQL query statement below
SELECT name, bonus
    FROM Employee e LEFT JOIN Bonus b
    ON e.empId = b.empId
    WHERE b.bonus < 1000 OR b.bonus IS NULL
```

or

```sql
# Write your MySQL query statement below
SELECT name, bonus
    FROM Employee e LEFT JOIN Bonus b
    ON e.empId = b.empId
    WHERE IFNULL(b.bonus, 0) < 1000
```