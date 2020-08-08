
+------------+------------+----------+-------+
| product_id | first_year | quantity | price |
+------------+------------+----------+-------+ 
| 100        | 2008       | 10       | 5000  |
| 200        | 2011       | 15       | 9000  |
+------------+------------+----------+-------+

#### Solutions

1. ##### sub query

```sql
# Write your MySQL query statement below

SELECT product_id,  year AS first_year, quantity, price
    FROM Sales
    WHERE (product_id, year) 
        IN (SELECT product_id, MIN(year) 
            FROM Sales GROUP BY product_id); 
```