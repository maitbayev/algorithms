Var C : Array [1..MaxN, 1..MaxN] Of Integer;
      Mark : Array[1..MaxN] Of Boolean;
      N, M, Res  : Integer;

Function DFS(A,By : Integer): Integer;
Var I, Am : Integer;
Begin
  DFS:=0;
  If A = Sink Then Begin
    DFS:=By;
    Exit;
  End;
  If Mark[A] Then Exit;
  Mark[A]:=True;
  For I:=1 To N Do If C[A, I]>0 Then Begin
    Am:=DFS(I, Min(By, C[A, I]));
    If Am>0 Then Begin
      Dec(C[A, I], Am);
      Inc(C[I, A], Am);
      DFS:=Am;
      Exit;
    End;
  End;
End;

Procedure Main;
Var Am:Integer;
Begin
  Res:=0;
  Repeat
    FillChar(Mark, SizeOf(Mark), False);
    Am:=DFS(Source, Infinity);
    Inc(Res, Am);
  Until Am=0;
End; 