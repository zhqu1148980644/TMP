---
title: Employees Earning More Than Their Managers
date: 2021-01-04
---
The Employee table holds all employees including their managers. Every employee has an Id, and there is also a column for the manager Id.

```
+----+-------+--------+-----------+
| Id | Name  | Salary | ManagerId |
+----+-------+--------+-----------+
| 1  | Joe   | 70000  | 3         |
| 2  | Henry | 80000  | 4         |
| 3  | Sam   | 60000  | NULL      |
| 4  | Max   | 90000  | NULL      |
+----+-------+--------+-----------+

Given the Employee table, write a SQL query that finds out employees who earn more than their managers. For the above table, Joe is the only employee who earns more than his manager.

+----------+
| Employee |
+----------+
| Joe      |
+----------+
```

#### Solutions

1. ##### Self join

```sql
SELECT e.Name as Employee
    FROM Employee as e, Employee as m;
    WHERE e.ManagerId = m.id AND e.Salary > m.Salary;
```

2. ##### Inner join

```sql
SELECT e.Name as Employee
    FROM Employee as e JOIN Employee as m
    ON e.ManagerId = m.id AND e.Salary > m.Salary;

```