theta = [11.9253 0.4203 0.1455 7.2462 1.8150 35.1492 0.0089]'; % identification from phase 2 see "Identified System Parameters.txt"

q_10 = pi/2; % linearized angle 1

q_20 = pi; % linearized angle 2

g = 9.81; 
M = [ theta(1)-2*theta(2)*cos(q_20) , theta(3)+theta(2)*cos(q_20); theta(3)+theta(2)*cos(q_20) , theta(3)];

K = [ -theta(4)*g*sin(q_10)- sin((2*1i+1)*pi/2)*theta(5)*g , -sin((2*1i+1)*pi/2)*theta(5)*g; -sin((2*1i+1)*pi/2)*theta(5)*g,-sin((2*1i+1)*pi/2)*theta(5)*g]; 

%from the lab documentation
A = [ [0 0;0 0], [0 1;1 0]; -inv(M)*K ,[0 0;0 0]];

B = [[0 0;0 0];inv(M)]*[1;0];

C = [1 0 0 0; 0 1 0 0]; 

% checks
Lambda=eig(A) %eigenvalues


% %% Checking controlability %%%
% 
% Pc=ctrb(A,B) %computing controllability matrix
% Rank_c=rank(Pc) %computing the rank of the matrix
% 
% 
% %% pole placement %%%
% p=[ -10,-39.8549,-2.6731i,2.6731i]; %location of desired poles
% 
% k=place(A,B,p) %computed state-feedback gain
% 
% 
% %% checking observability %%%
% Po=obsv(A,C) %computing controllability matrix
% Rank_o=rank(Po) %computing the rank of the matrix
% 
% 
% %% state estimator (observer) design
% pe=[ -10,-39.8549,-2.6731i,2.6731i]; %location of desired poles
% LT=place(A',C',pe) %computing transpose of observer gain matrix
% L=LT'
% 
% 
% 
% 
% 
% 
