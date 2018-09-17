%input parameters P[...] from Y drive
P=[10.9631
0.4005
0.1367
8.1092
1.6043
24.8423
0.0029]; %These are station 6 parameters
T=0.001;
g=9.81;

X0=[pi/2+.1 -.05 0 0]; %intial conditon

q10=pi/2;
%q20=0;
q20=0;

%Matrices from page 3
M_bar=[P(1)+2*P(2)*cos(q20) P(3)+P(2)*cos(q20); P(3)+P(2)*cos(q20) P(3)];
K_bar=[-P(4)*g*sin(q10)-sin(q10+q20)*P(5)*g -sin(q10+q20)*P(5)*g; -sin(q10+q20)*P(5)*g -sin(q10+q20)*P(5)*g]; % q1=pi/2

%portions of the A and B matrices
I=[1 0;0 1];
zero=zeros(2,2);

%Calculating our A,B,C matrices
A=[zero I;-inv(M_bar)*K_bar zero];
B=[zero;inv(M_bar)]*[1;0]
C=[1 0 0 0;0 1 0 0]; %page 4 was corrected by the TA

Pcon=ctrb(A,B); %Controllability matrix
Pcrank=rank(Pcon); %Rank of controllability matrix, needs to equal 4

DesK=[-9 -6 -5-i -5+i];
K=place(A,B,DesK)%Places poles are in desired location
Kpoles=transpose(eig(A-B*K)); %Checks that poles are in desired location

Pobv=obsv(A,C); %Observability matrix
Pobvrank=rank(Pobv); %Rank of observability matrix, needs to equal 4

DesL=5*DesK;
Lt=place(A',C',DesL); %Places poles are in desired location
L=Lt'
Lpoles=transpose(eig(A-L*C)); %Checks that poles are in desired location
