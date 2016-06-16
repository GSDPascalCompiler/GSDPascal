program suck;
var
    d,s:array[0..20,0..1000000]of longint;
    a,b:array[0..1000000]of longint;
    i,n,m:longint;
procedure qsort(l,r:longint);
var
    mid,i,j,t:longint;
begin
  mid:=b[a[(l+r)>>1]];
  i:=l;j:=r;
  repeat
    while b[a[i]]<mid do i:=i+1;
    while b[a[j]]>mid do j:=j-1;
    if i<=j then
      begin
        t:=a[i];a[i]:=a[j];a[j]:=t;
        i:=i+1;
        j:=j-1;
      end;
  until i>j;
  if i<r then qsort(i,r);
  if l<j then qsort(l,j);
end;
procedure build(k,l,r:longint);
var
    i,mid,p:longint;
begin
  if l=r then exit;
  mid:=(l+r+1)>>1;p:=0;
  for i:=l to r do
    begin
      if d[k][i]<mid then
        begin
          d[k+1][l+p]:=d[k][i];
          p:=p+1;
          s[k][i]:=p;
        end
      else
        begin
          d[k+1][mid+i-l-p]:=d[k][i];
          s[k][i]:=p;
        end;
    end;
  build(k+1,l,mid-1);
  build(k+1,mid,r);
end;
function find(k,ll,rr,l,r,x:longint):longint;
var
    ls,rs,mid:longint;
begin
  if l=r then exit(d[k][r]);
  mid:=(ll+rr+1)>>1;
  rs:=s[k][r];
  if l=ll then ls:=0 else ls:=s[k][l-1];
  if rs-ls