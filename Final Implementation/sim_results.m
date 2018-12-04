% simulation results 
close all;
%% position 1
pos1 = load('equilibriumpositon_1_realsim.mat','outputy');
pos1 = pos1.outputy.signals.values;
figure; 
range = 1:2000;
disturbance = 43170:45050;
pos1(:,1) = pos1(:,1) + pi/2;
plot(pos1(range,:));
title('Position 1 Inverted Pendulum Results');
xlabel("time samples (n)");
ylabel("angle (radians)");
legend("q1","q2");
figure;
plot(pos1(disturbance,:));
title('Position 1 Inverted Pendulum Disturbance Results');
xlabel("time samples (n)");
ylabel("angle (radians)");
legend("q1","q2");
%% position 2
pos2 = load('equilibriumpositon_2_realsim.mat','outputy');
pos2 = pos2.outputy.signals.values;
disturbance = 38570:40060;
figure; 
range = 1:2000;
pos2(:,1) = pos2(:,1) + pi/2;
pos2(:,2) = pos2(:,2) + pi;
plot(pos2(range,:));
title('Position 2 Inverted Pendulum Results');
xlabel("time samples (n)");
ylabel("angle (radians)");
legend("q1","q2");
figure;
plot(pos2(disturbance,:));
title('Position 2 Inverted Pendulum Disturbance Results');
xlabel("time samples (n)");
ylabel("angle (radians)");
legend("q1","q2");