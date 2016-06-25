program test4; 
var i, j:integer;
procedure swap(var a:integer; var b:integer);
var t:integer;
begin
  t := a;
  a := b;
  b := t;
end;
begin
  i := 10;
  j := 5;
  i := (i * 3 + 10) mod 7 / 5 + 1; 
  j := (j / 5 + 4 * (3 - 2)) / 5; 
  if (i > j) then
    swap(i, j);
  writeln(i);
  writeln(j);
end.
