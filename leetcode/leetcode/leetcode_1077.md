---
title: Project Employees III
date: 2021-01-04
---
SQL架构
Table: Project

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| project_id  | int     |
| employee_id | int     |
+-------------+---------+
(project_id, employee_id) is the primary key of this table.
employee_id is a foreign key to Employee table.
Table: Employee

+------------------+---------+
| Column Name      | Type    |
+------------------+---------+
| employee_id      | int     |
| name             | varchar |
| experience_years | int     |
+------------------+---------+
employee_id is the primary key of this table.
 

Write an SQL query that reports the most experienced employees in each project. In case of a tie, report all employees with the maximum number of experience years.

The query result format is in the following example:

Project table:
+-------------+-------------+
| project_id  | employee_id |
+-------------+-------------+
| 1           | 1           |
| 1           | 2           |
| 1           | 3           |
| 2           | 1           |
| 2           | 4           |
+-------------+-------------+

Employee table:
+-------------+--------+------------------+
| employee_id | name   | experience_years |
+-------------+--------+------------------+
| 1           | Khaled | 3                |
| 2           | Ali    | 2                |
| 3           | John   | 3                |
| 4           | Doe    | 2                |
+-------------+--------+------------------+

Result table:
+-------------+---------------+
| project_id  | employee_id   |
+-------------+---------------+
| 1           | 1             |
| 1           | 3             |
| 2           | 1             |
+-------------+---------------+
Both employees with id 1 and 3 have the most experience among the employees of the first project. For the second project, the employee with id 1 has the most experience.

#### Solutions

1. ##### sub queries

```sql
# Write your MySQL query statement below

SELECT p.project_id, p.employee_id
    FROM Project p LEFT JOIN Employee e
    ON p.employee_id = e.employee_id
    WHERE (project_id, experience_years)
        IN (SELECT project_id, MAX(experience_years)
            FROM Project p1 LEFT JOIN Employee e1
            ON p1.employee_id = e1.employee_id
            GROUP BY project_id)
    
```

2. ##### PARTITION

```sql
# Write your MySQL query statement below
SELECT project_id, employee_id
    FROM (
        SELECT p.project_id, p.employee_id, 
                RANK() OVER(PARTITION BY project_id ORDER BY experience_years DESC) AS r
            FROM Project p LEFT JOIN Employee e
            ON p.employee_id = e.employee_id
    ) p1
    WHERE r = 1;
```