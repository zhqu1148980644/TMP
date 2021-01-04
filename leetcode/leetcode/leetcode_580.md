---
title: Count Student Number in Departments
date: 2021-01-04
---
A university uses 2 data tables, student and department, to store data about its students and the departments associated with each major.

Write a query to print the respective department name and number of students majoring in each department for all departments in the department table (even ones with no current students).

Sort your results by descending number of students; if two or more departments have the same number of students, then sort those departments alphabetically by department name.

The student is described as follow:

| Column Name  | Type      |
|--------------|-----------|
| student_id   | Integer   |
| student_name | String    |
| gender       | Character |
| dept_id      | Integer   |
where student_id is the student's ID number, student_name is the student's name, gender is their gender, and dept_id is the department ID associated with their declared major.

And the department table is described as below:

| Column Name | Type    |
|-------------|---------|
| dept_id     | Integer |
| dept_name   | String  |

#### Solutions

1. ##### LEFT JOIN

```sql
# Write your MySQL query statement below
SELECT d.dept_name, COUNT(s.student_id) AS student_number
    FROM department d LEFT JOIN student s
    ON d.dept_id = s.dept_id
    GROUP BY d.dept_id
    ORDER BY COUNT(s.student_id) DESC
```

or with subquery

```sql
# Write your MySQL query statement below
SELECT d1.dept_name, IFNULL(d2.number, 0) AS student_number
    FROM department d1
    LEFT JOIN (SELECT dept_id, COUNT(*) AS number FROM student GROUP BY dept_id) d2
    ON d1.dept_id = d2.dept_id
    ORDER BY d2.number DESC
```