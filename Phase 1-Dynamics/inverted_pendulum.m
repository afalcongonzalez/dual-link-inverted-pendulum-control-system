function [sys,x0,str,ts,simStateCompliance] = inverted_pendulum(t,x,u,flag)
switch flag,
  %%%%%%%%%%%%%%%%%%
  % Initialization %
  %%%%%%%%%%%%%%%%%%
  case 0,
    [sys,x0,str,ts,simStateCompliance]=mdlInitializeSizes();

  %%%%%%%%%%%%%%%
  % Derivatives %
  %%%%%%%%%%%%%%%
  case 1,
    sys=mdlDerivatives(t,x,u);

  %%%%%%%%%%
  % Update %
  %%%%%%%%%%
  case 2
    sys=mdlUpdate(t,x,u);

  %%%%%%%%%%%
  % Outputs %
  %%%%%%%%%%%
  case 3,
    sys=mdlOutputs(t,x,u);

  %%%%%%%%%%%%%%%%%%%%%%%
  % GetTimeOfNextVarHit %
  %%%%%%%%%%%%%%%%%%%%%%%
  case 4,
    sys=mdlGetTimeOfNextVarHit(t,x,u);

  %%%%%%%%%%%%%
  % Terminate %
  %%%%%%%%%%%%%
  case 9,
    sys=mdlTerminate(t,x,u);

  %%%%%%%%%%%%%%%%%%%%
  % Unexpected flags %
  %%%%%%%%%%%%%%%%%%%%
  otherwise
    DAStudio.error('Simulink:blocks:unhandledFlag', num2str(flag));

end

% end sfuntmpl

%
%=============================================================================
% mdlInitializeSizes
% Return the sizes, initial conditions, and sample times for the S-function.
%=============================================================================
%
function [sys,x0,str,ts,simStateCompliance]=mdlInitializeSizes()

%
% call simsizes for a sizes structure, fill it in and convert it to a
% sizes array.
%
% Note that in this example, the values are hard coded.  This is not a
% recommended practice as the characteristics of the block are typically
% defined by the S-function parameters.
%
sizes = simsizes;

sizes.NumContStates  = 4;
sizes.NumDiscStates  = 0;
sizes.NumOutputs     = 1;
sizes.NumInputs      = 1;
sizes.DirFeedthrough = 1;
sizes.NumSampleTimes = 1;   % at least one sample time is needed

sys = simsizes(sizes);

%
% initialize the initial conditions
%
x0  = [pi,0,0, 0];

%
% str is always an empty matrix
%
str = [];

%
% initialize the array of sample times
%
ts  = [0 0];

% Specify the block simStateCompliance. The allowed values are:
%    'UnknownSimState', < The default setting; warn and assume DefaultSimState
%    'DefaultSimState', < Same sim state as a built-in block
%    'HasNoSimState',   < No sim state
%    'DisallowSimState' < Error out when saving or restoring the model sim state
simStateCompliance = 'UnknownSimState';

% end mdlInitializeSizes

%
%=============================================================================
% mdlDerivatives
% Return the derivatives for the continuous states.
%=============================================================================
%
function sys=mdlDerivatives(t,x,u)
m1=11;
m2 = 11; 
g= 10;
k = 0.4;
bf1 = 3;
bf2 = 0.2;
lc1 = 5; 
lc2 = 5; 
l1 = 10; 
I1 = 4; 
I2 = 3;  
A = [ 0 0 1 0; 0 0 0 1; 0  0 bf1/(((I2 + m2*(lc2 + l1*lc2))^2/((m2*lc2^2 + I2)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2))) - 1)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2))) -(bf2*(I2 + m2*(lc2 + l1*lc2)))/(((I2 + m2*(lc2 + l1*lc2))^2/((m2*lc2^2 + I2)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2))) - 1)*(m2*lc2^2 + I2)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2))); 0 0 bf1/((((m2*lc2^2 + I2)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2)))/(I2 + m2*(lc2 + l1*lc2))^2 - 1)*(I2 + m2*(lc2 + l1*lc2)))  -(bf2*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2)))/((((m2*lc2^2 + I2)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2)))/(I2 + m2*(lc2 + l1*lc2))^2 - 1)*(I2 + m2*(lc2 + l1*lc2))^2)];
B=[ 0 , 0 , -k/(((I2 + m2*(lc2 + l1*lc2))^2/((m2*lc2^2 + I2)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2))) - 1)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2))), -k/((((m2*lc2^2 + I2)*(I1 + I2 + lc1^2*m1 + m2*(l1^2 + 2*l1*lc2 + lc2^2)))/(I2 + m2*(lc2 + l1*lc2))^2 - 1)*(I2 + m2*(lc2 + l1*lc2)))];
sys = A*x+B*[u ;u; u; u];

% end mdlDerivatives

%
%=============================================================================
% mdlUpdate
% Handle discrete state updates, sample time hits, and major time step
% requirements.
%=============================================================================
%
function sys=mdlUpdate(t,x,u)

sys = [];

% end mdlUpdate

%
%=============================================================================
% mdlOutputs
% Return the block outputs.
%=============================================================================
%
function sys=mdlOutputs(t,x,u)
C=[1 0 0 0];
D=0;
sys = C*x+D*u;

% end mdlOutputs

%
%=============================================================================
% mdlGetTimeOfNextVarHit
% Return the time of the next hit for this block.  Note that the result is
% absolute time.  Note that this function is only used when you specify a
% variable discrete-time sample time [-2 0] in the sample time array in
% mdlInitializeSizes.
%=============================================================================
%
function sys=mdlGetTimeOfNextVarHit(t,x,u)

sampleTime = 1;    %  Example, set the next hit to be one second later.
sys = t + sampleTime;

% end mdlGetTimeOfNextVarHit

%
%=============================================================================
% mdlTerminate
% Perform any end of simulation tasks.
%=============================================================================
%
function sys=mdlTerminate(t,x,u)

sys = [];

% end mdlTerminate
