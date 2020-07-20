Write a SQL query to rank scores. If there is a tie between two scores, both should have the same ranking. Note that after a tie, the next ranking number should be the next consecutive integer value. In other words, there should be no "holes" between ranks.

```
+----+-------+
| Id | Score |
+----+-------+
| 1  | 3.50  |
| 2  | 3.65  |
| 3  | 4.00  |
| 4  | 3.85  |
| 5  | 4.00  |
| 6  | 3.65  |
+----+-------+

For example, given the above Scores table, your query should generate the following report (order by highest score):

+-------+------+
| Score | Rank |
+-------+------+
| 4.00  | 1    |
| 4.00  | 1    |
| 3.85  | 2    |
| 3.65  | 3    |
| 3.65  | 3    |
| 3.50  | 4    |
+-------+------+
```


#### Solutions

1. self join

```sql
# Write your MySQL query statement below

SELECT s1.Score as Score, 
    (SELECT COUNT(DISTINCT s2.Score) 
        FROM Scores s2 
        WHERE s2.Score >= s1.Score) as 'Rank'
    FROM Scores s1
    ORDER BY Score DESC;
```

or

```sql
SELECT s1.Score, COUNT(DISTINCT s2.score) AS 'Rank'
    FROM Scores s1, Scores s2
    WHERE s1.Score <= s2.Score
    GROUP BY s1.Id
    ORDER BY s1.Score DESC;
```

2. dense rank

- ranking/dense_rank/row_num

```sql
SELECT Score, dense_rank() over(ORDER BY Score DESC) as 'Rank'
    FROM Scores;
```