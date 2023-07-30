create table t_user(
id bigint unsigned auto_increment primary key,
name varchar(260),
tel varchar(260),
password varchar(260),
icon int,
feeling varchar(260)

);

create table t_friend(
idA bigint unsigned,
idB bigint unsigned
);