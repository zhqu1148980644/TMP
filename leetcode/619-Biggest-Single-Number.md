SQL架构
Table my_numbers contains many numbers in column num including duplicated ones.
Can you write a SQL query to find the biggest number, which only appears once.

+---+
|num|
+---+
| 8 |
| 8 |
| 3 |
| 3 |
| 1 |
| 4 |
| 5 |
| 6 | 
For the sample data above, your query should return the following result:
+---+
|num|
+---+
| 6 |
Note:
If there is no such number, just output null.


#### Solutions

1. ##### straight forward

```sql
# Write your MySQL query statement below

SELECT IFNULL((SELECT num
                FROM my_numbers
                GROUP BY num
                HAVING COUNT(*) = 1
                ORDER BY num DESC
                LIMIT 1), null) AS num
```