--1
select film_id
from film
where length = (select max(length) from film) and
rental_duration = (select min(rental_duration) from film);


--2
select f.film_id, f.title, count(a.actor_id)
from film f
inner join film_actor fa
on f.film_id=fa.film_id
inner join actor a
on fa.actor_id=a.actor_id
group by f.film_id;


--3
select l.name, avg(f.length)
from language l
left join film f
on l.language_id=f.language_id
group by l.language_id;


--4
select c.name, count(f.film_id)
from category c
left join film_category fc 
on c.category_id=fc.category_id
left join film f
on fc.film_id=f.film_id
where f.film_id in (select fa.film_id
from film_actor fa
inner join actor a
on fa.actor_id=a.actor_id
where a.first_name="KEVIN" and a.last_name="BLOOM")
group by c.name
order by c.name asc;


--5 
select title
from film
where film_id not in 
(select f.film_id
from film f
inner join film_actor fa
on f.film_id=fa.film_id
inner join actor a
on fa.actor_id=a.actor_id
where ((a.first_name="SCARLETT" and a.last_name="DAMON") or
(a.first_name="BEN" and a.last_name="HARRIS")) 
group by f.film_id
having count(f.film_id) > 1)
order by title desc;
