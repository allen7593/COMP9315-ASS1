create table mySets (id integer primary key, iset intSet);

/*#valid*/
insert into mySets values (1, '{ }');
insert into mySets values (2, '{11,5}');
insert into mySets values (3, '{11, 1, 5}');
insert into mySets values (4, '{1, 22, 34}');
insert into mySets values (5, '{    1  ,  22  ,  34}');
insert into mySets values (6, '{6 ,-6 ,6 , -6, 6 , -6 }');
insert into mySets values (7, '{6 ,6 ,6 , 6, 6 , 6 }');
insert into mySets values (8, '{1, 999, -11, 666, -5}');

/*invalid*/
insert into mySets values (9,'{a,b,c}');
insert into mySets values (9, '{ a, b, c }');
insert into mySets values (9,'{1, 2.0, 3}');
insert into mySets values (9, '{1, {2,3}, 4}');
insert into mySets values (9,'{1, 2, 3, 4, five}');
insert into mySets values (9,'{ 1 2 3 4 }');
insert into mySets values (9, '{1,}');
insert into mySets values (9,'{1,,5}');
insert into mySets values (9,'{1,/}');
insert into mySets values (9,'{1,/n}');
insert into mySets values (9,'{1,2}');
insert into mySets values (9,'[1,2]');
insert into mySets values (9,'{1*5,2}');
insert into mySets values (9,'{5555555555}');
insert into mySets values (9,'{-5555555555}');

/*operation*/
select id, iset, (@iset) as card from mySets order by id;

select * from mySets where 1 <@ mySets.iset;

select a.*, b.* from mySets a, mySets b
where (a.iset @> b.iset);

select a.*, b.* from mySets a, mySets b
where (a.iset @> b.iset) and a.id != b.id;

select a.*, b.*, a.iset @> b.iset from mySets a, mySets b
where a.id < b.id;

select a.*, b.* from mySets a, mySets b
where (a.iset = b.iset);

select a.*, b.*, a.iset && b.iset from mySets a, mySets b
where a.id < b.id;

select a.*, b.*, a.iset || b.iset from mySets a, mySets b
where a.id < b.id;

select a.*, b.*, a.iset - b.iset from mySets a, mySets b
where a.id < b.id;

select a.*, b.*, a.iset !! b.iset from mySets a, mySets b
where a.id < b.id;
