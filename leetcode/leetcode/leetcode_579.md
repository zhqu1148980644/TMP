---
title: Find Cumulative Salary of an Employee
date: 2021-01-04
---
SQL架构
The Employee table holds the salary information in a year.

Write a SQL to get the cumulative sum of an employee's salary over a period of 3 months but exclude the most recent month.

The result should be displayed by 'Id' ascending, and then by 'Month' descending.

Example
Input

| Id | Month | Salary |
|----|-------|--------|
| 1  | 1     | 20     |
| 2  | 1     | 20     |
| 1  | 2     | 30     |
| 2  | 2     | 30     |
| 3  | 2     | 40     |
| 1  | 3     | 40     |
| 3  | 3     | 60     |
| 1  | 4     | 60     |
| 3  | 4     | 70     |
Output
| Id | Month | Salary |
|----|-------|--------|
| 1  | 3     | 90     |
| 1  | 2     | 50     |
| 1  | 1     | 20     |
| 2  | 1     | 20     |
| 3  | 3     | 100    |
| 3  | 2     | 40     |
 

Explanation
Employee '1' has 3 salary records for the following 3 months except the most recent month '4': salary 40 for month '3', 30 for month '2' and 20 for month '1'
So the cumulative sum of salary of this employee over 3 months is 90(40+30+20), 50(30+20) and 20 respectively.

| Id | Month | Salary |
|----|-------|--------|
| 1  | 3     | 90     |
| 1  | 2     | 50     |
| 1  | 1     | 20     |
Employee '2' only has one salary record (month '1') except its most recent month '2'.
| Id | Month | Salary |
|----|-------|--------|
| 2  | 1     | 20     |
 

Employ '3' has two salary records except its most recent pay month '4': month '3' with 60 and month '2' with 40. So the cumulative salary is as following.
| Id | Month | Salary |
|----|-------|--------|
| 3  | 3     | 100    |
| 3  | 2     | 40     |


#### Solutions

- Over a period of 3 month means accumulating the nearest 3(including self) month's sum as the current month's result.

1. ##### SUM OVER

- must use `ROWS 2 PRECEDING`

```sql
# Write your MySQL query statement below
SELECT Id, Month, Salary
    FROM (SELECT Id, Month, 
            SUM(Salary) OVER(PARTITION BY Id ORDER BY Month ROWS 2 PRECEDING) AS Salary
            FROM Employee
            ORDER BY Id, Month DESC) AS e
    WHERE (e.Id, e.Month) NOT IN (SELECT Id, MAX(Month) FROM Employee GROUP BY Id)
```


2. ##### JOIN

```sql
# Write your MySQL query statement below
# Write your MySQL query statement below

SELECT e1.Id, e1.Month, SUM(e2.Salary) AS Salary
    FROM Employee e1, Employee e2
    WHERE e1.Id = e2.Id
    AND e1.Month >= e2.Month
    AND e1.Month < e2.Month + 3
    AND (e1.Id, e1.Month) NOT IN (SELECT Id, MAX(Month) FROM Employee GROUP BY Id)
    GROUP BY e1.Id, e1.Month
    ORDER BY e1.Id, e1.Month DESC 
```