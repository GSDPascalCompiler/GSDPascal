program test2;
var f:array[1..10]of integer;
  i:integer;
begin
  i:=10*2;
  for i:= 10 to 5 do
  begin
    f[i] := 9999;
  end;
  if (true) then
    writeln(9998)
  else
    writeln(9997);
  if (false) then
    writeln(9996)
  else
    writeln(9995);
  while (false) do begin
    writeln(9994);
  end;
  repeat
    writeln(9993);
  until true;
  while (true) do begin
    writeln(9992);
  end;
  repeat
    writeln(9991);
  until false;
end.