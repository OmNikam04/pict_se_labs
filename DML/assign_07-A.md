# Assignment 7

### All tables and data used for queries:

```sql
mysql> use ecommerce;
Database changed
mysql> select * from customers;
+----+---------------+--------------------------+----------+
| id | name          | email                    | phone    |
+----+---------------+--------------------------+----------+
|  1 | John Doe      | johndoe@example.com      | 555-1234 |
|  2 | Jane Doe      | janedoe@example.com      | 555-5678 |
|  3 | Bob Smith     | bobsmith@example.com     | 555-2468 |
|  4 | Alice Johnson | alicejohnson@example.com | 555-1357 |
|  5 | Tom Jones     | tomjones@example.com     | 555-3691 |
+----+---------------+--------------------------+----------+
5 rows in set (0.00 sec)

mysql> select * from products;
+----+-----------+-------+
| id | name      | price |
+----+-----------+-------+
|  1 | Product A | 19.99 |
|  2 | Product B | 24.99 |
|  3 | Product C | 29.99 |
|  4 | Product D | 14.99 |
|  5 | Product E |  9.99 |
+----+-----------+-------+
5 rows in set (0.00 sec)

mysql> select * from orders;
+----+-------------+------------+----------+--------------+
| id | customer_id | product_id | quantity | date_ordered |
+----+-------------+------------+----------+--------------+
|  1 |           1 |          1 |        2 | 2023-05-01   |
|  2 |           1 |          2 |        1 | 2023-05-02   |
|  3 |           2 |          3 |        3 | 2023-05-03   |
|  4 |           3 |          4 |        2 | 2023-05-04   |
|  5 |           4 |          5 |        1 | 2023-05-05   |
+----+-------------+------------+----------+--------------+
5 rows in set (0.00 sec)

mysql> select * from payment;
+----+----------+--------+------------+
| id | order_id | amount | date_paid  |
+----+----------+--------+------------+
|  1 |        1 |  39.98 | 2023-05-01 |
|  2 |        2 |  24.99 | 2023-05-02 |
|  3 |        3 |  89.97 | 2023-05-03 |
|  4 |        4 |  29.98 | 2023-05-04 |
|  5 |        5 |   9.99 | 2023-05-05 |
+----+----------+--------+------------+
5 rows in set (0.00 sec)
```

### Assignment 7a

- Display all the Purchase orders of a specific Customer.
    
    ```sql
    select p.name as "Product Name", p.price, o.quantity, 
    o.date_ordered, pay.amount, pay.date_paid
    from orders o 
    join customers c on o.customer_id = c.id
    join products p on o.product_id = p.id
    join payment pay on pay.order_id = o.id
    where c.name = "John Doe";
    
    +--------------+-------+----------+--------------+--------+------------+
    | Product Name | price | quantity | date_ordered | amount | date_paid  |
    +--------------+-------+----------+--------------+--------+------------+
    | Product A    | 19.99 |        2 | 2023-05-01   |  39.98 | 2023-05-01 |
    | Product B    | 24.99 |        1 | 2023-05-02   |  24.99 | 2023-05-02 |
    +--------------+-------+----------+--------------+--------+------------+
    2 rows in set (0.00 sec)
    ```
    
- Get Customer and Data Item Information for a Specific Purchase Order.
    
    ```sql
    select c.name as "customer name",c.email, p.name as "product name",
     p.price, o.quantity, pay.amount
    from orders o
    join customers c on o.customer_id = c.id
    join products p on o.product_id = p.id
    join payment pay on pay.order_id = o.id
    where o.id = 1;
    
    +---------------+---------------------+--------------+-------+----------+--------+
    | customer name | email               | product name | price | quantity | amount |
    +---------------+---------------------+--------------+-------+----------+--------+
    | John Doe      | johndoe@example.com | Product A    | 19.99 |        2 |  39.98 |
    +---------------+---------------------+--------------+-------+----------+--------+
    1 row in set (0.00 sec)
    ```
    
- Get the Total Value of Purchase Orders.
    
    ```sql
    select sum(amount) as "Total purchase value" from payment;
    +----------------------+
    | Total purchase value |
    +----------------------+
    |               194.91 |
    +----------------------+
    1 row in set (0.00 sec)
    ```
    
- List the Purchase Orders in descending order as per total.
    
    ```sql
    select c.name as "customer", p.name as "product", o.quantity, 
    pay.amount as "Amount Paid" 
    from orders o 
    join customers c on o.customer_id = c.id
    join products p on o.product_id = p.id
    join payment pay on pay.order_id = o.id
    order by pay.amount desc;
    
    +---------------+-----------+----------+-------------+
    | customer      | product   | quantity | Amount Paid |
    +---------------+-----------+----------+-------------+
    | Jane Doe      | Product C |        3 |       89.97 |
    | John Doe      | Product A |        2 |       39.98 |
    | Bob Smith     | Product D |        2 |       29.98 |
    | John Doe      | Product B |        1 |       24.99 |
    | Alice Johnson | Product E |        1 |        9.99 |
    +---------------+-----------+----------+-------------+
    5 rows in set (0.00 sec)
    ```
    
- Display the name of customers whose first name starts with “Rav”. (String
matching :Like operator)
    
    ```sql
    select name from customers where name like "Alic%";
    +---------------+
    | name          |
    +---------------+
    | Alice Johnson |
    +---------------+
    1 row in set (0.00 sec)
    ```
    
- Display the name of customer whose order amount is greater than all the
customers. (Relational Operator: <, >, <=, >=, = =,!=)
    
    ```sql
    SELECT c.name, pay.amount
    FROM customers c
    JOIN orders o ON c.id = o.customer_id
    JOIN payment pay ON o.id = pay.order_id
    WHERE pay.amount > 
    (SELECT MAX(amount) FROM payment WHERE order_id IN 
    	(SELECT id FROM orders WHERE customer_id != c.id)
    );
    OR
    select c.name, sum(pay.amount) as "total spend"
    from orders o
    join customers c on o.customer_id = c.id
    join payment pay on pay.order_id = o.id
    group by c.id
    order by sum(pay.amount) desc
    limit 1;
    
    +----------+-------------+
    | name     | total spend |
    +----------+-------------+
    | Jane Doe |       89.97 |
    +----------+-------------+
    1 row in set (0.00 sec)
    ```
    
- Display order details of customer whose city name is “Pune” and purchase
date is “22/08/2016” (Boolean Operators: and, or)
    
    ```sql
    SELECT o.id, o.quantity, p.name AS product_name,
     c.name AS customer_name, c.city, o.date_ordered, pay.amount, pay.date_paid
    FROM orders o
    JOIN customers c ON o.customer_id = c.id
    JOIN products p ON o.product_id = p.id
    JOIN payment pay ON o.id = pay.order_id
    WHERE c.city = 'Pune' AND o.date_ordered = '2023-05-01';
    
    +----+----------+--------------+---------------+------+--------------+--------+------------+
    | id | quantity | product_name | customer_name | city | date_ordered | amount | date_paid  |
    +----+----------+--------------+---------------+------+--------------+--------+------------+
    |  1 |        2 | Product A    | John Doe      | pune | 2023-05-01   |  39.98 | 2023-05-01 |
    +----+----------+--------------+---------------+------+--------------+--------+------------+
    1 row in set (0.00 sec)
    ```
    
- Add discount of 5% to all the customers whose order is more than Rs. 10000/-.
(Arithmetic Operators +, -, *, /)
    
    ```sql
    UPDATE payment
    JOIN (
      SELECT o.id, o.customer_id, pay.amount, pay.date_paid
      FROM orders o
      JOIN payment pay ON o.id = pay.order_id
      WHERE pay.amount > 30
    ) AS p
    ON payment.id = p.id
    SET payment.amount = p.amount * 0.95;
    ```
    
- Delete Purchase Order 1001.
    
    ```sql
    delete from orders where id=10;
    Query OK, 1 row affected (0.10 sec)
    ```
