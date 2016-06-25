program test3;
var f:array[1..10]of integer;
  i:integer;

function gcd(a:integer;b:integer):integer;
begin
  if b=0 then
    gcd:=a
  else 
    gcd:=gcd(b, a mod b);
end;
begin
  f[1] := 1;
  f[2] := 1;
  writeln(f[1]);
  writeln(f[2]);
  for i := 3 to 10 do
  begin
    f[i] := f[i-1] + f[i-2];
    writeln(f[i]);
  end;
  if f[i-1] = 55 then
  begin
    i:=gcd(f[i-1], 45);
    writeln(i);
  end;
end.