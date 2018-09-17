clear
clc
T=1/1000
Ts=T;

Zita=0.7;
Fc=40;

%       S*wn^2
%-----------------------
%  S^2+2*zita*wn*S+wn^2

sys=tf([0 1],[1/(2*pi*Fc)^2 2*Zita/(2*pi*Fc) 1]);
sys=c2d(sys,Ts,'tustin');  %tustin
[num,den]=tfdata(sys,'v'); 
NewPanto = 1;     %IMPORTANT SET TO 1 for newer systems otherwise 0


%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Station 1&4 , NewPanto=1