
%% System definition %%%%%
A= [0.2    1.2  -10;
    0.8   -0.5   -4;
    0.05    0.025   -1.25]

B=[1,-1;
    0 1;
   -1, 1]

C=[1, 0, 0;
   0, 1, 0]


%% checking stability %%%%
Lambda=eig(A) %eigenvalues


%% Checking controlability %%%
Pc=ctrb(A,B) %computing controllability matrix
Rank_c=rank(Pc) %computing the rank of the matrix


%% pole placement %%%
p=[-2+1j,-2-1j, -1]; %location of desired poles

k=place(A,B,p) %computed state-feedback gain
%% Closed loop system %%%
A_Cl= A-B*k;

%% checking stability %%%%
Lambda_Cl=eig(A_Cl) %eigenvalues

