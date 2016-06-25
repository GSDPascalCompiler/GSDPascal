program test6; 
var i:integer;
function l1(u:integer):integer;
var x:integer;
   function l2(v:integer):integer;
   var y:integer;
   begin
    writeln(y);
    writeln(x);   
   end; 
begin
  x:=1;
  l1:=l2(u+1);
  writeln(x+1);
end;

begin
  i:=l1(1);
  writeln(i);
end.
