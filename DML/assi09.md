1. Procedure to add two numbers;
mysql> delimiter &&
mysql> create procedure addTwoNumbers ( IN a INT, IN b INT, OUT sum INT )
    -> begin
    -> set sum = a + b;
    -> end &&
Query OK, 0 rows affected (0.14 sec)

mysql> delimiter ;
mysql> call addTwoNumbers(5, 10, @sum);
Query OK, 0 rows affected (0.00 sec)

mysql> select @sum;
+------+
| @sum |
+------+
|   15 |
+------+
1 row in set (0.00 sec)
# Assignment 9 (Stored procedure)

- Write a stored procedure in mysql which will add discount to the customers according to the order amount.
-- 1. Add discount of 5% to all the customers whose order amount is more than rupees 10,000
-- 2. Add discount of 15% to all the customers whose order amount is more than rupees 25,000
-- updating order amount upto 50000 rupees
    
    ```sql
    update payment
    set amount =
    case
    when id = 1 then "14000"
    when id = 2 then "26000"
    when id = 3 then "67000"
    when id = 4 then "3000"
    when id = 5 then "56000"
    end
    where id in (1,2,3,4,5);
    
    update products
    set price =
    	case
    		when id = 1 then "3000"
    		when id = 2 then "2699"
    		when id = 3 then "4577"
    		when id = 4 then "1299"
    		when id = 5 then "5999"
    	end
    where id in (1,2,3,4,5);
    
    -- Stored procedure for it
    CREATE PROCEDURE `add_discounts`()
    BEGIN
    	-- apply 10% disocunt
    	update payment p
        join orders o on p.order_id = o.id
        set p.amount = p.amount * 0.90
        where p.amount > 10000;
        
        -- apply 25% discount
        update payment p
        join orders o on p.order_id = o.id
        set p.amount = p.amount * 0.75
        where p.amount > 25000;
    END
    ```
    
1. write a stored procedure to count number of customers who ordered the product **without using aggregate function.**
2. To display customers details who is staying in nashik.
    
    ```sql
    -- All customers who had given orders
    select c.name as "customer name" ,p.name as "Product Name", c.city,  c.loyalty_level,  pay.amount, o.date_ordered
        -> from orders o
        -> join customers c on o.customer_id = c.id
        -> join payment pay on o.id = pay.order_id
        -> join products p on o.product_id = p.id
        -> ;
    +---------------+--------------+--------+---------------+----------+--------------+
    | customer name | Product Name | city   | loyalty_level | amount   | date_ordered |
    +---------------+--------------+--------+---------------+----------+--------------+
    | John Doe      | Product A    | pune   | gold          | 12600.00 | 2023-05-01   |
    | John Doe      | Product B    | pune   | gold          | 23400.00 | 2023-05-02   |
    | Jane Doe      | Product C    | Nashik | bronze        | 45225.00 | 2023-05-03   |
    | Bob Smith     | Product D    | Nagpur | bronze        |  3000.00 | 2023-05-04   |
    | Alice Johnson | Product E    | sangli | bronze        | 37800.00 | 2023-05-05   |
    +---------------+--------------+--------+---------------+----------+--------------+
    5 rows in set (0.00 sec)
    
    --customers orders only from pune
    select c.name as "customer name" ,p.name as "Product Name", c.city,  c.loyalty_level,  pay.amount, o.date_ordered
    from orders o
    join customers c on o.customer_id = c.id
    join payment pay on o.id = pay.order_id
    join products p on o.product_id = p.id
    where c.city = "pune";
    +---------------+--------------+------+---------------+----------+--------------+
    | customer name | Product Name | city | loyalty_level | amount   | date_ordered |
    +---------------+--------------+------+---------------+----------+--------------+
    | John Doe      | Product A    | pune | gold          | 12600.00 | 2023-05-01   |
    | John Doe      | Product B    | pune | gold          | 23400.00 | 2023-05-02   |
    +---------------+--------------+------+---------------+----------+--------------+
    2 rows in set (0.00 sec)
    
    --Created stored procedure for above statements
    CREATE PROCEDURE `customers_from_city`(in city varchar(20))
    BEGIN
    	select c.name as "customer name" ,p.name as "Product Name", c.city,  c.loyalty_level,  pay.amount, o.date_ordered
    	from orders o
    	join customers c on o.customer_id = c.id
    	join payment pay on o.id = pay.order_id
    	join products p on o.product_id = p.id
    	where c.city = city;
    END
    mysql> call customers_from_city("nashik");
    +---------------+--------------+--------+---------------+----------+--------------+
    | customer name | Product Name | city   | loyalty_level | amount   | date_ordered |
    +---------------+--------------+--------+---------------+----------+--------------+
    | Jane Doe      | Product C    | Nashik | bronze        | 45225.00 | 2023-05-03   |
    +---------------+--------------+--------+---------------+----------+--------------+
    1 row in set (0.00 sec)
    
    Query OK, 0 rows affected (0.01 sec)
    ```
    
3. Write stored procedure to accept **customer number** from user and will be displayed his purchase amount of the user
    
    ```sql
    CREATE PROCEDURE `user_purchase_amount`(in cust_id int)
    BEGIN
    	select c.name as "customer name", p.name as "product name", sum(pay.amount) as "total spend"
    	from orders o
    	join customers c on o.customer_id = c.id
    	join payment pay on o.id = pay.order_id
    	join products p on o.product_id = p.id
    	where c.id = cust_id
    	group by c.id, p.name;
    END
    mysql> call user_purchase_amount(1);
    +---------------+--------------+-------------+
    | customer name | product name | total spend |
    +---------------+--------------+-------------+
    | John Doe      | Product A    |    14000.00 |
    | John Doe      | Product B    |    26000.00 |
    +---------------+--------------+-------------+
    2 rows in set (0.01 sec)
    
    Query OK, 0 rows affected (0.01 sec)
    ```
    
4. Write a procedure to get customer and data item information for a specific purchase order.
    
    ```sql
    CREATE PROCEDURE `specific_order`(in order_id int)
    BEGIN
    	select c.name as "customer name", p.name as "product name",o.quantity, sum(pay.amount) as "total spend", o.date_ordered as "Ordered on"
    	from orders o
    	join customers c on o.customer_id = c.id
    	join payment pay on o.id = pay.order_id
    	join products p on o.product_id = p.id
    	where o.id = order_id
    	group by c.id, p.name, o.quantity, o.date_ordered;
    END
    
    mysql> call specific_order(5);
    +---------------+--------------+----------+-------------+------------+
    | customer name | product name | quantity | total spend | Ordered on |
    +---------------+--------------+----------+-------------+------------+
    | Alice Johnson | Product E    |        1 |    56000.00 | 2023-05-05 |
    +---------------+--------------+----------+-------------+------------+
    1 row in set (0.00 sec)
    
    Query OK, 0 rows affected (0.01 sec)
    ```
    
5. write a stored procedure to accept number from user and tell whether it is even or odd.
    
    ```sql
    CREATE PROCEDURE `even_odd`(in num int, out result varchar(20))
    BEGIN
    	if ((num%2)=0) then set result = "even"; 
        else set result = "odd";  end if;
    END
    
    mysql> call even_odd(15, @result);
    Query OK, 0 rows affected (0.00 sec)
    
    mysql> select @result;
    +---------+
    | @result |
    +---------+
    | odd     |
    +---------+
    1 row in set (0.00 sec)
    ```

Write a procedure to get customer and data item information for a specific purchase order.

write a stored procedure to find purchase details of all customers who made shopping today.







