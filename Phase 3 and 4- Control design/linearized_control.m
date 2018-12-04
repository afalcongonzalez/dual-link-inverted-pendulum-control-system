Parameters = [11.9253 0.4203 0.1455 7.2462 1.8150 35.1492 0.0089]'; % identification from phase 2 see "Identified System Parameters.txt"
% Case 1: Angle 1 = pi/2, Angle 2 = 0
q10 = pi/2;
q20 = 0; %Change to pi for Case 2
g = 9.81;

X0 = [q10-0.1, q20+.2 , 0 ,0]';
Kbar = [-(Parameters(4)*g*sin(q10))-sin(q10+q20)*Parameters(5)*g -sin(q10+q20)*Parameters(5)*g;-sin(q10+q20)*Parameters(5)*g -sin(q10+q20)*Parameters(5)*g];
Mbar = [Parameters(1)+2*Parameters(2)*cos(q20) Parameters(3)+Parameters(2)*cos(q20);Parameters(3)+Parameters(2)*cos(q20) Parameters(3)];
Fbar = [Parameters(6) 0;0 Parameters(7)];

A = [zeros(2,2) eye(2);-Mbar\Kbar -Mbar\Fbar];
B = [zeros(2,2);inv(Mbar)]*[1;0];
C = [1 0 0 0;0 1 0 0];
D = 0;

sys = ss(A,B,C,D);
figure;
pzmap(sys);
title('Pole-Zero Plot for Equilibrium State 2');

% Controller Design
Pd = [-15 -12 -10 -8]; 
K = place(A,B,Pd);

Pc = ctrb(A,B);
rc = rank(Pc);

controlled = ss(A-B*K,[0 0 0 0]',C,0);
figure;
pzmap(controlled);
title('Pole-Zero Plot With Controller Case:1');
%% Observability and Estimator Gain Design
Po=obsv(A,C)
rank(Po)
po=10*Pd; % ten times the gain of the controller
L = transpose(place(A', C',po))






