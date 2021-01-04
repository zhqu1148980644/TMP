---
title: Winning Candidate
date: 2021-01-04
---
Table: Candidate

+-----+---------+
| id  | Name    |
+-----+---------+
| 1   | A       |
| 2   | B       |
| 3   | C       |
| 4   | D       |
| 5   | E       |
+-----+---------+  
Table: Vote

+-----+--------------+
| id  | CandidateId  |
+-----+--------------+
| 1   |     2        |
| 2   |     4        |
| 3   |     3        |
| 4   |     2        |
| 5   |     5        |
+-----+--------------+
id is the auto-increment primary key,
CandidateId is the id appeared in Candidate table.
Write a sql to find the name of the winning candidate, the above example will return the winner B.

+------+
| Name |
+------+
| B    |
+------+
Notes:

You may assume there is no tie, in other words there will be only one winning candidate.
 

#### Solutions

1. ##### Subquery

```sql
# Write your MySQL query statement below
SELECT Name
    FROM Candidate
    WHERE id = (SELECT CandidateId 
                FROM Vote GROUP BY CandidateId 
                ORDER BY COUNT(CandidateId) DESC LIMIT 1);
```

or

```sql
# Write your MySQL query statement below
SELECT Name
    FROM Candidate c1,
    (SELECT CandidateId 
        FROM Vote GROUP BY CandidateId 
        ORDER BY COUNT(CandidateId) DESC LIMIT 1) c2
    WHERE c1.id = c2.CandidateId
```

2. ##### JOIN

```sql
# Write your MySQL query statement below
SELECT c.Name
    FROM Candidate c JOIN Vote v
    ON c.id = v.CandidateId
    GROUP BY v.CandidateId
    ORDER BY COUNT(v.CandidateId) DESC
    LIMIT 1
```