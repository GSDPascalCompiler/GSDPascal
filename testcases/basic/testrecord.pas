program test5; 
type
 test=record
  a:integer;
  b:real;
end;

var f:test;

begin
  f.a := 10;
  f.b := 99.9;
  writeln(f.a);
  writeln(f.b);
end.
