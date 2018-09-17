function [sys,x0,str,ts] = rlc(t,x,u,flag)
% CSFUNC An example M-file S-function for defining a system of
% continuous state equations:
% x' = Ax + Bu
% y = Cx + Du
%
% Generate a continuous linear system:
R=.5;L=1;C=1;

A=[-R/L,-1/L;
    1/C,0];
B=[ 1/L,0;0,0];
C=eye(2);%[1,0;0,1];
D=[0,0;0,0];
%
% Dispatch the flag.
%
switch flag,
case 0
[sys,x0,str,ts]=mdlInitializeSizes(A,B,C,D); % Initialization
case 1
sys = mdlDerivatives(t,x,u,A,B,C,D); % Calculate derivatives
case 3
sys = mdlOutputs(t,x,u,A,B,C,D); % Calculate outputs
case { 2, 4, 9 } % Unused flags
sys = [];
otherwise
error(['Unhandled flag = ',num2str(flag)]); % Error handling
end
% End of csfunc.

%==============================================================
% mdlInitializeSizes
% Return the sizes, initial conditions, and sample times for the
% S-function.
%==============================================================
%
function [sys,x0,str,ts] = mdlInitializeSizes(A,B,C,D)
%
% Call simsizes for a sizes structure, fill it in and convert it
% to a sizes array.
%
sizes = simsizes;
sizes.NumContStates = 2;
sizes.NumDiscStates = 0;
sizes.NumOutputs = 2;
sizes.NumInputs = 2;
sizes.DirFeedthrough = 1; % Matrix D is nonempty.
sizes.NumSampleTimes = 1;
sys = simsizes(sizes);
%
% Initialize the initial conditions.
%
x0 = [0;0];
%
% str is an empty matrix.
%
str = [];
%
% Initialize the array of sample times; in this example the sample
% time is continuous, so set ts to 0 and its offset to 0.
%
ts = [0 0];
% End of mdlInitializeSizes.
%
%==============================================================
% mdlDerivatives
% Return the derivatives for the continuous states.
%==============================================================
function sys = mdlDerivatives(t,x,u,A,B,C,D)
sys = A*x + B*u;



% End of mdlDerivatives.
%
%==============================================================
% mdlOutputs
% Return the block outputs.
%==============================================================
%
function sys = mdlOutputs(t,x,u,A,B,C,D)
sys = C*x + D*u;
% End of mdlOutputs.