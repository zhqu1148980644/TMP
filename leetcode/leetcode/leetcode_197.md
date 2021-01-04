---
title: Rising Temperature
date: 2021-01-04
---
Given a Weather table, write a SQL query to find all dates' Ids with higher temperature compared to its previous (yesterday's) dates.

```
+---------+------------------+------------------+
| Id(INT) | RecordDate(DATE) | Temperature(INT) |
+---------+------------------+------------------+
|       1 |       2015-01-01 |               10 |
|       2 |       2015-01-02 |               25 |
|       3 |       2015-01-03 |               20 |
|       4 |       2015-01-04 |               30 |
+---------+------------------+------------------+

For example, return the following Ids for the above Weather table:

+----+
| Id |
+----+
|  2 |
|  4 |
+----+
```

#### Solutions

1. ##### DateDiff with self join


```sql
SELECT DISTINCT w2.Id AS Id
    FROM Weather as w1, Weather as w2
    WHERE DATEDIFF(w2.RecordDate, w1.RecordDate) = 1
          AND w1.Temperature < w2.Temperature;
```

2. ##### inner join

```sql
SELECT DISTINCT w2.Id AS Id
    FROM Weather as w1 JOIN Weather as w2
    ON DATEDIFF(w2.RecordDate, w1.RecordDate) = 1
          AND w1.Temperature < w2.Temperature;
```