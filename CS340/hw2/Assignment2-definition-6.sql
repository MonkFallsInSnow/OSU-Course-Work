-- For part one of this assignment you are to make a database with the following specifications and run the following queries
-- The drop table queries below are to facilitate testing on my end

DROP TABLE IF EXISTS `os_support`;
DROP TABLE IF EXISTS `device`;
DROP TABLE IF EXISTS `operating_system`;
DROP TABLE IF EXISTS `category_tbl`;

SET default_storage_engine=INNODB;
-- Create a table called category_tbl with the following properties:
-- id - an auto incrementing integer which is the primary key
-- name - a varchar with a maximum length of 255 characters, cannot be null
-- subcategory - a varchar with a maximum length of 255 characters, cannot be null
-- the combinatino of a name and subcategory must be unique

create table if not exists category_tbl (
id int primary key auto_increment,
name varchar(255) not null,
subcategory varchar(255) not null,
unique key (name,subcategory));


-- Create a table called operating_system with the following properties:
-- id - an auto incrementing integer which is the primary key
-- name - a varchar of maximum length 255, cannot be null
-- version - a varchar of maximum length 255, cannot be null
-- name version combinations must be unique

create table if not exists operating_system (
id int primary key auto_increment,
name varchar(255) not null,
version varchar(255) not null,
unique key (name,version));


-- Create a table called device with the following properties:
-- id - an auto incrementing integer which is the primary key
-- cid - an integer which is a foreign key reference to the category_tbl table
-- name - a varchar of maximum length 255 which cannot be null
-- received - a date type (you can read about it here http://dev.mysql.com/doc/refman/5.0/en/datetime.html)
-- isbroken - a boolean

create table if not exists device (
id int primary key auto_increment,
cid int not null,
name varchar(255) unique not null,
recieved date,
isbroken boolean,
foreign key (cid) references category_tbl(id));


-- Create a table called os_support with the following properties, this is a table representing a many-to-many relationship
-- between devices and operating systems:
-- did - an integer which is a foreign key reference to device
-- osid - an integer which is a foreign key reference to operating_system
-- notes - a text type
-- The primary key is a combination of did and osid

create table if not exists os_support (
did int,
osid int,
notes text,
primary key (did,osid),
foreign key (did) references device(id),
foreign key (osid) references operating_system(id));


-- insert the following into the category_tbl table:

-- name: phone
-- subcategory: maybe a tablet?

-- name: tablet
-- subcategory: but kind of a laptop

-- name: tablet
-- subcategory: ereader
insert into category_tbl (name,subcategory) values
("phone","maybe a tablet?"),("tablet","but kind of a laptop"),("tablet","ereader");


-- insert the folowing into the operating_system table:
-- name: Android
-- version: 1.0

-- name: Android
-- version: 2.0

-- name: iOS
-- version: 4.0
insert into operating_system (name,version) values
("Android","1.0"),("Android","2.0"),("iOS","4.0");


-- insert the following devices instances into the device table (you should use a subquery to set up foriegn keys referecnes, no hard coded numbers):
-- cid - reference to name: phone subcategory: maybe a tablet?
-- name - Samsung Atlas
-- received - 1/2/1970
-- isbroken - True

-- cid - reference to name: tablet subcategory: but kind of a laptop
-- name - Nokia
-- received - 5/6/1999
-- isbroken - False

-- cid - reference to name: tablet subcategory: ereader
-- name - jPad
-- received - 11/18/2005
-- isbroken - False
insert into device (cid,name,recieved,isbroken) values
((select id
from category_tbl
where name="phone"),"Samsung Atlas",'1970-01-02', true),
((select id
from category_tbl
where subcategory="but kind of a laptop"),"Nokia",'1999-05-06', false),
((select id
from category_tbl
where subcategory="ereader"),"jPad",'2005-11-18', false);

-- insert the following into the os_support table using subqueries to look up data as needed:
-- device: Samsung Atlas
-- os: Android 1.0
-- notes: Works poorly

-- device: Samsung Atlas
-- os: Android 2.0
-- notes: NULL

-- device: jPad
-- os: iOS 4.0
-- notes: NULL
insert into os_support (did,osid)
select d.id, o.id
from device d
inner join operating_system o
on d.id=o.id;

update os_support
set notes="Works poorly"
where did=
(select d.id 
from device d
inner join operating_system o
on d.id=o.id
where d.name="Samsung Atlas" and o.name="Android" and o.version="1.0")



