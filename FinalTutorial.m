clear
clc


A1=[.5 -.5 .5; -.5 -.5 -.5; -.5 .5 -.5];
B1=[.5 -.5;.5 -.5; .5 .5];
P1=ctrb(A1,B1);
rP1=rank(P1);

C11=[1 0 0];
Q11=obsv(A1,C11);
rQ11=rank(Q11);
C12=[0 1 0];
Q12=obsv(A1,C12);
rQ12=rank(Q12);

poles1=eig(A1);
Dpoles1=[-3 -2 -1];
K1 = place(A1,B1,Dpoles1);
Cpoles1 = eig(A1-B1*K1);

DPO1 = [-15 -10+5i -10-5i];
L1 = transpose(place(A1',C11',DPO1));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

A2 = [0 1 0 0; 0 0 9.81/(1+2/5*4) 0; 0 0 0 1; -0.032*9.81/.062 0 0 -(4.77*4.91/4.7+1.52)/0.062];
B2 = [0;0;0;4.91/4.7/0.062];
P2 = ctrb(A2,B2);
rP2 = rank(P2);
C2 = [1 0 0 0;
      0 1 0 0];
Q2=obsv(A2,C2);
rQ2 = rank(Q2);

poles2=eig(A2);
Dpoles2=[-5 -3 -1+1i -1-1i];
K2 = place(A2,B2,Dpoles2);
Cpoles2 = eig(A2-B2*K2);

DPO2 = [-20 -18 -11+4i -11-4i];
L2 = transpose(place(A2',C2',DPO2));
