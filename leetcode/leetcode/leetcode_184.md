---
title: Department Highest Salary
date: 2021-01-04
---
The Employee table holds all employees. Every employee has an Id, a salary, and there is also a column for the department Id.

```
+----+-------+--------+--------------+
| Id | Name  | Salary | DepartmentId |
+----+-------+--------+--------------+
| 1  | Joe   | 70000  | 1            |
| 2  | Jim   | 90000  | 1            |
| 3  | Henry | 80000  | 2            |
| 4  | Sam   | 60000  | 2            |
| 5  | Max   | 90000  | 1            |
+----+-------+--------+--------------+

The Department table holds all departments of the company.

+----+----------+
| Id | Name     |
+----+----------+
| 1  | IT       |
| 2  | Sales    |
+----+----------+

Write a SQL query to find employees who have the highest salary in each of the departments. For the above tables, your SQL query should return the following rows (order of rows does not matter).

+------------+----------+--------+
| Department | Employee | Salary |
+------------+----------+--------+
| IT         | Max      | 90000  |
| IT         | Jim      | 90000  |
| Sales      | Henry    | 80000  |
+------------+----------+--------+

Explanation:

Max and Jim both have the highest salary in the IT department and Henry has the highest salary in the Sales department.
```


#### Solutions

1. ##### inner join

```sql
# Write your MySQL query statement below

SELECT D.Name as Department, 
       E.Name as Employee, 
       E.Salary
FROM Employee E, Department D
WHERE D.Id = E.DepartmentId
    AND (E.DepartmentId, E.Salary) IN (
        SELECT DepartmentId, MAX(Salary)
        FROM Employee
        GROUP BY DepartmentId);
```


2. ##### dense_rank()

- reference: https://leetcode-cn.com/problems/department-highest-salary/comments/188672

```sql
# Write your MySQL query statement below

SELECT S.Department, S.Employee, S.Salary
FROM (
    SELECT D.Name AS Department,
           E.Name AS Employee,
           E.Salary,
           dense_rank() over(PARTITION BY E.DepartmentId ORDER BY E.Salary DESC) as 'Rank'
    FROM Employee E, Department D
    WHERE D.Id = E.DepartmentId
) AS S
WHERE S.Rank = 1
```