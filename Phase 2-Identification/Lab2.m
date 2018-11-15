clear; clc; close all;
load Sys_Ident_Lab2.mat
load Sys_Verification_Lab2.mat

g = 9.81;
U_bar = zeros(60002,1);
j = 1;
for i = 1:2:length(torque)*2
    U_bar(i) = torque(j);
    j = j + 1;
end

total_time = 30;
delta_t = 30/length(q1);

for i = 1:(length(q1)-1)
    q1_dot(i,1) = (q1(i+1)-q1(i))/delta_t;
    q2_dot(i,1) = (q2(i+1)-q2(i))/delta_t;
end
    
for i = 1:(length(q1_dot)-1)
    q1_2dot(i,1) = (q1_dot(i+1)-q1_dot(i))/delta_t;
    q2_2dot(i,1) = (q2_dot(i+1)-q2_dot(i))/delta_t;
end
    
q1_dot(30001,1) = 0;
q2_dot(30001,1) = 0;
q1_2dot(30000,1) = 0;
q2_2dot(30000,1) = 0;
q1_2dot(30001,1) = 0;
q2_2dot(30001,1) = 0;

Y_bar = zeros(60002,5);
j = 1;
for i = 1:2:length(q1)*2
    Y_bar(i,1) = q1_2dot(j);
    Y_bar(i,2) = cos(q2(j))*(2*q1_2dot(j)+q2_2dot(j)) - sin(q2(j))*(q1_dot(j).^2+2*q1_dot(j)*q2_dot(j));
    Y_bar(i,3) = q2_2dot(j);
    Y_bar(i,4) = g*cos(q1(j));
    Y_bar(i,5) = g*cos(q1(j)+q2(j));
    Y_bar(i+1,1) = 0;
    Y_bar(i+1,2) = cos(q2(j))*q1_2dot(j) + sin(q2(j))*q1_dot(j).^2;
    Y_bar(i+1,3) = q1_2dot(j) + q2_2dot(j);
    Y_bar(i+1,4) = 0;
    Y_bar(i+1,5) = g*cos(q1(j)+q2(j));
    j = j + 1;
end
    
Theta_hat = inv((Y_bar'*Y_bar))*Y_bar'*U_bar;


Uv_bar = zeros(60002,1);
j = 1;
for i = 1:2:length(torque_v)*2
    Uv_bar(i) = torque_v(j);
    j = j + 1;
end

delta_t = 30/length(q1);

for i = 1:(length(q1_v)-1)
    q1v_dot(i,1) = (q1_v(i+1)-q1_v(i))/delta_t;
    q2v_dot(i,1) = (q2_v(i+1)-q2_v(i))/delta_t;
end
    
for i = 1:(length(q1v_dot)-1)
    q1v_2dot(i,1) = (q1v_dot(i+1)-q1v_dot(i))/delta_t;
    q2v_2dot(i,1) = (q2v_dot(i+1)-q2v_dot(i))/delta_t;
end
    
q1v_dot(30001,1) = 0;
q2v_dot(30001,1) = 0;
q1v_2dot(30000,1) = 0;
q2v_2dot(30000,1) = 0;
q1v_2dot(30001,1) = 0;
q2v_2dot(30001,1) = 0;

Yv_bar = zeros(60002,5);
j = 1;
for i = 1:2:length(q1_v)*2
    Yv_bar(i,1) = q1v_2dot(j);
    Yv_bar(i,2) = cos(q2_v(j))*(2*q1v_2dot(j)+q2v_2dot(j)) - sin(q2_v(j))*(q1v_dot(j).^2+2*q1v_dot(j)*q2v_dot(j));
    Yv_bar(i,3) = q2v_2dot(j);
    Yv_bar(i,4) = g*cos(q1_v(j));
    Yv_bar(i,5) = g*cos(q1_v(j)+q2_v(j));
    Yv_bar(i+1,1) = 0;
    Yv_bar(i+1,2) = cos(q2_v(j))*q1v_2dot(j) + sin(q2_v(j))*q1v_dot(j).^2;
    Yv_bar(i+1,3) = q1v_2dot(j) + q2v_2dot(j);
    Yv_bar(i+1,4) = 0;
    Yv_bar(i+1,5) = g*cos(q1_v(j)+q2_v(j));
    j = j + 1;
end
    

U_tilda = Yv_bar*Theta_hat - Uv_bar;
