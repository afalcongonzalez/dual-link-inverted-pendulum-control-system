%% Linearization Point
q1 = pi/2;
q2 = 0;
g = 9.81;
X0=[q1+.1 q2-.2 0 0];
T=.001;
NewPanto=1;
%% System Parameters
Parameters = [];
%% Linear System Definition
M = [Parameters(1)+2*Parameters(2)*cos(q2),  Parameters(3)+Parameters(2)*cos(q2);
    Parameters(3)+Parameters(2)*cos(q2),     Parameters(3)];

F = [Parameters(6), 0;
    0, Parameters(7)];

K = [-Parameters(4)*g*sin(q1)-sin(q1+q2)*g*Parameters(5),  -sin(q1+q2)*g*Parameters(5);
    -sin(q1+q2)*g*Parameters(5),                   -sin(q1+q2)*g*Parameters(5)];

A = [zeros(2,2),    eye(2,2);
     -M^-1*K,        -M^-1*F];

B = [zeros(2,2);
    M^-1]*[1;0];

C = [1 0 0 0;
     0 1 0 0];

%% Stability Analysis
EigenValues=eig(A)

%% Controllability and Controller Gain Design
Pc=ctrb(A,B)
rank(Pc)
p=[];
K = place(A,B,p)
%% Observability and Estimator Gain Design
Po=obsv(A,C)
rank(Po)
po=[];
L = transpose(place(A', C',po))