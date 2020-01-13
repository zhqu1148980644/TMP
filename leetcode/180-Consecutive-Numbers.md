Write a SQL query to find all numbers that appear at least three times consecutively.

```
+----+-----+
| Id | Num |
+----+-----+
| 1  |  1  |
| 2  |  1  |
| 3  |  1  |
| 4  |  2  |
| 5  |  1  |
| 6  |  2  |
| 7  |  2  |
+----+-----+

For example, given the above Logs table, 1 is the only number that appears consecutively for at least three times.

+-----------------+
| ConsecutiveNums |
+-----------------+
| 1               |
+-----------------+
```

#### Solutions

1. ##### Self join

```sql
SELECT DISTINCT a.Num as ConsecutiveNums FROM
    Logs as a,
    Logs as b,
    Logs as c
WHERE
    a.Num = b.Num AND
    b.Num = c.Num AND
    a.id + 1 = b.id AND
    b.id + 1 = c.id;
```