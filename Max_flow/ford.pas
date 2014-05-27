const
maxn = 100; 
oo = maxint;

var
f: array [1..maxn, 1..maxn] of integer; { f[i, j] = -f[j, i] }
c: array [1..maxn, 1..maxn] of integer;
n: integer;


const
queue_size = maxn + 2; 

type
queue = record 
a: array [0..queue_size-1] of integer;
head, tail: integer;
end;

procedure init_queue(var q: queue);
begin
with q do
begin
tail := 0;
head := 0;
end;
end;

function is_queue_empty(const q: queue): boolean;
begin
is_queue_empty := q.tail = q.head;
end;

procedure push_to_queue(var q: queue; x: integer);
begin
with q do
begin
a[tail] := x;
tail := (tail + 1) mod queue_size;
end;
end;

function pop_from_queue(var q: queue): integer;
begin
with q do
begin
pop_from_queue := a[head];
head := (head + 1) mod queue_size;
end;
end;

var
p: array [1..maxn] of integer;
v: array [1..maxn] of boolean;
q: queue;

function bfs(s, t: integer): boolean;
var
i, j: integer;
begin
fillchar(v, sizeof(v), false); 
init_queue(q);
push_to_queue(q, s);
v[s] := true;
p[s] := -1; 

while not is_queue_empty(q) do
begin
i := pop_from_queue(q); 
for j := 1 to n do 
if not v[j] and 
(c[i, j]-f[i, j] > 0) then 
begin
v[j] := true; 
push_to_queue(q, j); 
p[j] := i; 
end;
end;
bfs := v[t];
end;




function min(a, b: integer): integer;
begin
if a > b then min := b else min := a;
end;



function maxflow(s, t: integer): integer;
var
k: integer;
d, flow: integer;
begin
fillchar(f, sizeof(f), 0);
flow := 0; 

while bfs(s, t) do 
begin 
d := oo; 
k := t; 
while k <> s do 
begin
d := min(d, c[p[k], k]-f[p[k], k]);
k := p[k];
end;

k := t;
while k <> s do 
begin
f[p[k], k] := f[p[k], k] + d;
f[k, p[k]] := f[k, p[k]] - d;
k := p[k]; 
end;

flow := flow + d; 
end;

maxflow := flow; 
end;

procedure init;
var
m, i, x, y, z: integer;
begin
fillchar(c, sizeof(c), 0);
assign(input, 'flow.in');
reset(input);

read(n, m);

for i := 1 to m do
begin
read(x, y, z);
c[x, y] := z;
end;

close(input);
end;

procedure solve;
begin
writeln(maxflow(1, n));
end;


begin
init;
solve;
end.
