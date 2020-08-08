
SQL架构
Table: Enrollments

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| student_id    | int     |
| course_id     | int     |
| grade         | int     |
+---------------+---------+
(student_id, course_id) is the primary key of this table.

Write a SQL query to find the highest grade with its corresponding course for each student. In case of a tie, you should find the course with the smallest course_id. The output must be sorted by increasing student_id.

The query result format is in the following example:

Enrollments table:
+------------+-------------------+
| student_id | course_id | grade |
+------------+-----------+-------+
| 2          | 2         | 95    |
| 2          | 3         | 95    |
| 1          | 1         | 90    |
| 1          | 2         | 99    |
| 3          | 1         | 80    |
| 3          | 2         | 75    |
| 3          | 3         | 82    |
+------------+-----------+-------+

Result table:
+------------+-------------------+
| student_id | course_id | grade |
+------------+-----------+-------+
| 1          | 2         | 99    |
| 2          | 2         | 95    |
| 3          | 3         | 82    |
+------------+-----------+-------+

#### Solutions

1. ##### partition

```sql
# Write your MySQL query statement below
SELECT student_id, course_id, grade
    FROM (SELECT *, 
            ROW_NUMBER() OVER(PARTITION BY student_id 
                            ORDER BY grade DESC, course_id ASC) as r
            FROM Enrollments) t
    WHERE r = 1;
```


2. ##### sub query

```sql
# Write your MySQL query statement below

SELECT student_id, MIN(course_id) as course_id, grade
    FROM Enrollments
    WHERE (student_id, grade) IN
        (SELECT student_id, MAX(grade) as grade
                FROM Enrollments 
                GROUP BY student_id)
    GROUP BY student_id
    ORDER BY student_id
```