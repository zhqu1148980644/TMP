Write a SQL query to get the nth highest salary from the Employee table.

```
+----+--------+
| Id | Salary |
+----+--------+
| 1  | 100    |
| 2  | 200    |
| 3  | 300    |
+----+--------+

For example, given the above Employee table, the nth highest salary where n = 2 is 200. If there is no nth highest salary, then the query should return null.

+------------------------+
| getNthHighestSalary(2) |
+------------------------+
| 200                    |
+------------------------+
```

#### Solutions

1. ##### LIMIT

- LIMIT b, a : skip b records and fetch a records.
- LIMIT a OFFSET b : skip b records and fetch a records.

```sql
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
    SET N = N - 1;
  RETURN (
      SELECT IFNULL((SELECT DISTINCT salary
                    from Employee
                    ORDER BY salary DESC
                    LIMIT N, 1), NULL) AS NthHighest
  );
END
```

Or

```sql
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
    SET N = N - 1;
  RETURN (
      SELECT IFNULL((SELECT DISTINCT salary 
                    from Employee 
                    ORDER BY salary DESC 
                    LIMIT 1 OFFSET N), NULL) AS NthHighest
  );
END
```