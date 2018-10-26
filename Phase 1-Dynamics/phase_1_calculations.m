%% System Derivations 
syms q1 q2 q1dot q1dotdot q2dot q2dotdot m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 tau1; 
% first we must calculate the potential energy of the system. 
% from the diagram we can setup the following equations 

% first arm 
K1 = 0.5*m1*((-lc1*sin(q1)*q1dot)^2 + (lc1*cos(q1)*q1dot)^2) + 0.5*I1*q1dot^2;
P1 = m1*g*lc1*sin(q1);

%second arm
K2 = 0.5*m2*((-lc2*sin(q1+q2)*(q1dot+q2dot)- l1*sin(q1)*q1dot)^2 + 
(lc2*cos(q1+q2)*(q1dot+q2dot)+ l1*cos(q1)*q1dot)^2) + 0.5*I2*(q1dot+q2dot)^2;
P2 = m2*g*(l1*sin(q1)+lc2*sin(q1+q2));

K = K1 +K2;
P = P1+P2; 
L = K-P; 
euler_lagrange_1 = diff(diff(K, q1dot),q1dot) - diff(P,q1);
euler_lagrange_2 = diff(diff(K, q2dot),q2dot) - diff(P,q2);

% our mechanical system has 2 degrees of freedom q1,q2 therefor
% the euler lagrang fomulations are as follows 
%%
% we have euler lagrangian equation relating potential engerys to kinetic
% engeries for the double pendulum system 
% lagrange equations follow the form D(q)*qdotdot +N(q,qdot) = tau
d11 = m1*lc1^2 +m2*(l1^2 + lc2^2 +2*l1*lc2*cos(q2))+I1+I2; 
d12 = m2*(lc2+l1*lc2*cos(q2))+I2;
d21 = d12;
d22 = m2*lc2^2 + I2; 
d_q = [ d11 d12;d21 d22];
qdotdot = [q1dotdot;q2dotdot]; 
h = -m2*l1*lc2*sin(q1); 
n1 = 2*h*q1dot*q2dot + h*q2dot^2 + bf1*q1dot + (m1*lc1 + m2*l1)*g*cos(q1) + m2*lc2*g*cos(q1+q2); 
n2 = -h*q1dot^2 + bf2*q2dot + m2*lc2*g*cos(q1+q2);
N_q_qdot = [n1;n2];
tau = [tau1;0];


euler_lagrange = d_q*qdotdot + N_q_qdot == tau;
% isolate(euler_lagrange(1,1),q1dotdot);
Q1DotDot = rhs(isolate(subs(isolate(euler_lagrange(1,1),q1dotdot),q2dotdot,rhs(isolate(euler_lagrange(2,1),q2dotdot))),q1dotdot));
Q2DotDot = rhs(isolate(subs(isolate(euler_lagrange(1,1),q2dotdot),q1dotdot,rhs(isolate(euler_lagrange(2,1),q1dotdot))),q2dotdot));
syms k u1 u2 x1dot x2dot x3dot x4dot x1 x2 x3 x4; 
Xdot = [x3;x4;subs(Q1DotDot,[q1,q2,q1dot,q2dot,tau1],[x1,x2,x3,x4,k*u1]);subs(Q2DotDot,[q1,q2,q1dot,q2dot,tau1],[x1,x2,x3,x4,k*u1])];
%% Linerization at two equilibruim points p1, p2
X = [ x1; x2 ;x3;x4];
Tau = [u1;u2];
A = jacobian(Xdot,X); 
B = jacobian(Xdot,Tau);
C =  [ 1 0 0 0;0 1 0 0; 0 0 0 0; 0 0 0 0];
D = 0;
% equilibrium point 1
Abar = double(subs(A,[x1 x2 x3 x4 m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[ pi/2 0 0 0 0.03 0.03 0.05 0.05 0.04 0.04 0.08 9.8 0.003 0.0006 1]));
Bbar =double(subs(B,[x1 x2 x3 x4 m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[ pi/2 0 0 0.03 0.03 0.05 0.05 0.04 0.04 0.08 9.8 0.003 0.0006 1]));
% equilibrium point 2
Abar_2 = double(subs(A,[x1 x2 x3 x4 m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[ pi/2 pi 0 0 0.03 0.03 0.05 0.05 0.04 0.04 0.08 9.8 0.003 0.0006 1]));
Bbar_2 =double(subs(B,[x1 x2 x3 x4 m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[ pi/2 pi 0 0.03 0.03 0.05 0.05 0.04 0.04 0.08 9.8 0.003 0.0006 1]));


Q1DotDot = (subs(Q1DotDot,[ m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[ 0.03 0.03 0.05 0.05 0.04 0.04 0.08 9.8 0.003 0.0006 1]));
Q2DotDot = (subs(Q2DotDot,[m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[ 0.03 0.03 0.05 0.05 0.04 0.04 0.08 9.8 0.003 0.0006 1]));
A1 = subs(A,[x1 x2 x3 x4],[pi/2 0 0 0]);
B1 = subs(B,[x1 x2 x3 x4],[pi/2 0 0 0]);
A_ = subs(A1,[m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[5 3 5 5 0.04 0.04 0.08 9.8 0.4 0.6 0.5]);
B_ = subs(B1,[m1 m2 I1 I2 lc1 lc2 l1 g bf1 bf2 k],[5 3 5 5 0.04 0.04 0.08 9.8 0.4 0.6 0.5]);
system = ss(double(A_),double(B_(:,1)),[ 1 0 0 0;0 1 0 0; 0 0 1 0; 0 0 0 1],0);