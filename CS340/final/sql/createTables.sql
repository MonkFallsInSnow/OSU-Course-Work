drop table if exists job_skill, skill_activity, activity_venue, job, skill, activity, venue, employer;

create table if not exists employer
(id int primary key auto_increment,
name varchar(255) not null,
street varchar(255),
city varchar(255),
state varchar(2) default "NC",
zip varchar(10),
phone varchar(10),
rating enum('1','2','3','4','5','6','7','8','9','10') not null)
engine = innodb;


create table if not exists job
(id int primary key auto_increment,
employerID int not null,
title varchar(255) not null,
description varchar(255) not null,
pay decimal(10,2) unsigned,
rating enum('1','2','3','4','5','6','7','8','9','10') not null,
unique(title,description),
foreign key (employerID) references employer(id)
on delete cascade)
engine = innodb;


create table if not exists skill
(id int primary key auto_increment,
name varchar(255) not null,
description varchar(255) not null,
proficiency enum('very poor','poor','acceptable','good','very good','excellent') not null,
unique(name,description))
engine = innodb;


create table if not exists activity
(id int primary key auto_increment,
description varchar(255) unique not null,
rating enum('1','2','3','4','5','6','7','8','9','10') not null)
engine = innodb;


create table if not exists venue
(id int primary key auto_increment,
name varchar(255) not null,
street varchar(255),
city varchar(255),
state varchar(2) default "NC",
zip varchar(10),
phone varchar(10),
description varchar(255) not null,
rating enum('1','2','3','4','5','6','7','8','9','10') not null)
engine = innodb;


create table if not exists job_skill
(jobID int not null,
skillID int not null,
primary key (jobID,skillID),
foreign key (jobID) references job(id)
on delete cascade,
foreign key (skillID) references skill(id))
engine = innodb;


create table if not exists skill_activity
(skillID int not null,
activityID int not null,
primary key (skillID,activityID),
foreign key (skillID) references skill(id),
foreign key (activityID) references activity(id)
on delete cascade)
engine = innodb;


create table if not exists activity_venue
(activityID int not null,
venueID int not null,
primary key (activityID,venueID),
foreign key (activityID) references activity(id)
on delete cascade,
foreign key (venueID) references venue(id)
on delete cascade)
engine = innodb;