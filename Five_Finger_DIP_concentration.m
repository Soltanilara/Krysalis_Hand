F = 9.81.*[0.1:0.1:2]; %N
Dist_F = F./5;
%% Length of Index joints
L_Index_DIP = (31/2)/1000; %m
% Length of Middle joints
L_Middle_DIP = (40.4/2)/1000; %m
% Length of Pinky joints
L_Pinky_DIP = (37/2)/1000; %m
% Length of Thumb joints:
L_Thumb_IP = (38.2/2)/1000; %m

%% Angles of Dist_F vector to x-axis:
theta_I_Dist_F = 110.9; % Dist_F vector from Index DIP to the center of the payload (Degrees)
theta_M_Dist_F = 115.20; % Dist_F vector from Middle DIP to the center of the payload (Degrees)
theta_P_Dist_F = 119.84; % Dist_F vector from Pinky DIP to the center of the payload (Degrees)
theta_T_Dist_F = 61.44; % Dist_F vector from Thumb IP to the center of the payload (Degrees)
%% Angles of MCP, PIP, & DIP joints:
theta_I_DIP = 19.67;
theta_I_PIP = 35.03;
theta_I_MCP = 70.48;

theta_M_DIP = 25.33;
theta_M_PIP = 37.85;
theta_M_MCP = 69.04;

theta_P_DIP = 29.69;
theta_P_PIP = 40.74;
theta_P_MCP = 70.1;
%theta_T_Dist_F = 9.62;
theta_T_IP = 12.04;
theta_T_MCP = -8.53;
theta_T_CMC = -51.48;
%% Force components on Index DIP:
Fx_Index = (Dist_F)*cosd(theta_I_Dist_F);
Fy_Index = (Dist_F)*sind(theta_I_Dist_F);
%% Force components on Pinky DIP:
Fx_Pinky = (Dist_F)*cosd(theta_P_Dist_F);
Fy_Pinky = (Dist_F)*sind(theta_P_Dist_F);
%% Force components on Middle DIP:
Fx_Middle = (Dist_F)*cosd(theta_M_Dist_F);
Fy_Middle = (Dist_F)*sind(theta_M_Dist_F);
%% Force components on IP:
Fx_thumb = (Dist_F)*cosd(theta_T_Dist_F);
Fy_thumb = (Dist_F)*sind(theta_T_Dist_F);
%% Length to MCP and PIP on Index:
L_Index_PIP = 55.31/1000; %m
L_Index_MCP = 84.76/1000; %m
%% Length to MCP and PIP on Middle:
L_Middle_MCP = 85.27/1000; %m
L_Middle_PIP = 64.0/1000; %m
%% Length to MCP and PIP on Pinky:
L_Pinky_MCP = 83.61/1000; %m
L_Pinky_PIP = 58.61/1000; %m
%% Length to thumb MCP and CMC:
L_Thumb_MCP = 56.12/1000; %m
L_Thumb_CMC = 78.05/1000; %m
%% Torques on MCP, PIP, DIP
% Index Finger
T_Index_DIP = L_Index_DIP*sind(theta_I_DIP)*Fx_Index - L_Index_DIP*cosd(theta_I_DIP)*Fy_Index;
T_Index_PIP = L_Index_PIP*sind(theta_I_PIP)*Fx_Index - L_Index_PIP*cosd(theta_I_PIP)*Fy_Index;
T_Index_MCP = L_Index_MCP*sind(theta_I_MCP)*Fx_Index - L_Index_MCP*cosd(theta_I_MCP)*Fy_Index;
% Middle Finger
T_Middle_DIP = L_Middle_DIP*sind(theta_M_DIP).*Fx_Middle - L_Middle_DIP*cosd(theta_M_DIP).*Fy_Middle;
T_Middle_PIP = L_Middle_PIP*sind(theta_M_PIP).*Fx_Middle - L_Middle_PIP*cosd(theta_M_PIP).*Fy_Middle;
T_Middle_MCP = L_Middle_MCP*sind(theta_M_MCP).*Fx_Middle - L_Middle_MCP*cosd(theta_M_MCP).*Fy_Middle;
% Pinky Finger
T_Pinky_DIP = L_Pinky_DIP*sind(theta_P_DIP).*Fx_Pinky - L_Pinky_DIP*cosd(theta_P_DIP).*Fy_Pinky;
T_Pinky_PIP = L_Pinky_PIP*sind(theta_P_PIP).*Fx_Pinky - L_Pinky_PIP*cosd(theta_P_PIP).*Fy_Pinky;
T_Pinky_MCP = L_Pinky_MCP*sind(theta_P_MCP).*Fx_Pinky - L_Pinky_MCP*cosd(theta_P_MCP).*Fy_Pinky;
%% Torques on Thumb IP, and MCP:
T_Th_IP = L_Thumb_IP*sind(theta_T_IP).*Fx_thumb + L_Thumb_IP*cosd(theta_T_IP).*Fy_thumb;
T_Th_MCP = L_Thumb_MCP*sind(theta_T_MCP).*Fx_thumb + L_Thumb_MCP*cosd(theta_T_MCP).*Fy_thumb;
T_Th_CMC = L_Thumb_CMC*sind(theta_T_CMC).*Fx_thumb + L_Thumb_CMC*cosd(theta_T_CMC).*Fy_thumb;
plot(Dist_F,T_Index_DIP,'-r',Dist_F,T_Index_PIP,'-g',Dist_F,T_Index_MCP,'-b',Dist_F,T_Middle_DIP,'--r',Dist_F,T_Middle_PIP,'--g',Dist_F,T_Middle_MCP,'--b', ...
    Dist_F,T_Pinky_DIP,'-.r',Dist_F,T_Pinky_PIP,'-.g',Dist_F,T_Pinky_MCP,'-.b',Dist_F,T_Th_IP,'-*r',Dist_F,T_Th_MCP,'-*g',Dist_F,T_Th_CMC,'-*b');
legend('Torque DIP Index','Torque PIP Index','Torque MCP Index','Torque DIP Middle','Torque PIP Middle', ...
    'Torque MCP Middle','Torque DIP Pinky','Torque PIP Pinky','Torque MCP Pinky','Torque IP Thumb','Torque MCP Thumb','Torque CMC Thumb','location','northeastoutside')
xlabel('Distributed Force on five finger DIPs (N)')
title('Five Finger DIP Concentrated Estimated Torque')
ylabel('Torque (Nm)')
grid on