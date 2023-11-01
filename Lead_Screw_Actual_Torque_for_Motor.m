Payload_mass = 2;%linspace(min_mass,max_mass,120);
g = 9.81;
F = g.*Payload_mass;      % payload capacity (0.1 kg - 2.0 kg)
Dist_F = F./5;                  % weight distributed over 5 finger DIP part.
motor_weight = 9.81*(12.15/1000);   %Acquired motor is 12.15 g
u = 0.42;                       % Coefficient of friction between screw and nut (Stainless-Steel dry)
lead = 0.35/1000; %mm/rev to m/rev
lead_screw_dia = 2.5/1000; %mm to m
alpha = atan(lead/(pi*lead_screw_dia)); %alpha(thread angle) = arctan(lead/pi*diameter) 
beta = atan(u);                 %Friction angle
%n = (1-(u*tan(alpha)))/(1+(u*cot(alpha)))
n=tan(alpha)/tan(alpha+beta);   %Lead-Screw efficiency
Tough_density = 1.07; %g/cm^3
%% Motor torque for Index DIP:
% l_1 = 15.62 % mm : motor base to hinge
% l_2 = 24.31 % mm : hinge to nut
% Finger_angle = linspace(111.31,61.78,120);
% l_3 = sqrt(l_1^2 + l_2^2 - 2*l_1*l_2*cosd(Finger_angle)); % lead screw contracting length.

angle_I_DIP_flx = 50.88; % DIP Flexion angle between Y-axis and r
angle_I_DIP_ext = 64.1;  % DIP Extension angle between Y-axis and r
angle_I_DIP = linspace(angle_I_DIP_ext,angle_I_DIP_flx,120); % Angle between Y-axis and line joining DIP hinge to DIP motor.
F_nut_I_DIP = -Dist_F.*tand(angle_I_DIP);
T_m_I_DIP = F_nut_I_DIP.*(lead_screw_dia/2).*tan(beta - alpha);  % For formula look at (https://engineeringstatics.org/Chapter_09-screw-friction.html)
T_m_I_DIP_mNm = 1000*(T_m_I_DIP);
% figure 
% plot(F_nut_DIP,T_m_I_DIP_mNm); grid on;
% xlabel("Angle from the horizontal [deg.]");
% ylabel("Motor Torque [mN-m]");
min_T_m_I_DIP = min(T_m_I_DIP_mNm)
max_T_m_I_DIP = max(T_m_I_DIP_mNm)

%% Motor torque for Index PIP:
R1_I_PIP_min = 49/1000;          % PIP Hinge to DIP nut minimum (in m)
R1_I_PIP_max = 64.84/1000;       % PIP Hinge to DIP nut maximum (in m)
R1_I_PIP = linspace(R1_I_PIP_max,R1_I_PIP_min,120);     % PIP Hinge to DIP nut array (in m)

r1_I_PIP = 22.09/1000;           % PIP Hinge to PIP Nut (in m)

angle_I_PIP_R1_ext = 81.1;       % PIP Extension angle between Y-axis and R1
angle_I_PIP_R1_flx = 49.05;      % PIP Flexion angle between Y-axis and R1
angle_I_PIP_R1 = linspace(angle_I_PIP_R1_ext,angle_I_PIP_R1_flx,120);  % PIP Angle between Y-axis and R1 array

angle_I_PIP_r1_ext = 52.88;      % PIP Extension angle between Y-axis and r1  
angle_I_PIP_r1_flx = 34.35;      % PIP Flexion angle between Y-axis and r1
angle_I_PIP_r1 = linspace(angle_I_PIP_r1_ext,angle_I_PIP_r1_flx,120); % PIP Angle between Y-axis and r1 array

angle_I_PIP_Dist_F_ext = 5.60;  % PIP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_I_PIP_Dist_F_flx = 73.70; % PIP Flexion angle between Y-axis and Dist_F vector
angle_I_PIP_Dist_F = linspace(angle_I_PIP_Dist_F_ext,angle_I_PIP_Dist_F_flx,120);  % PIP Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_I_PIP = (-Dist_F.*R1_I_PIP.*(cosd(angle_I_PIP_Dist_F).*sind(angle_I_PIP_R1) + sind(angle_I_PIP_Dist_F).*cosd(angle_I_PIP_R1)))./(r1_I_PIP.*(cosd(angle_I_PIP_r1)));
T_m_I_PIP = F_nut_I_PIP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_I_PIP_mNm = 1000*(T_m_I_PIP);

min_T_m_I_PIP = min(T_m_I_PIP_mNm)
max_T_m_I_PIP = max(T_m_I_PIP_mNm)

%% Motor torque for Index MCP:
R2_I_MCP_min = 69.35/1000;
R2_I_MCP_max = 104.41/1000;
R2_I_MCP = linspace(R2_I_MCP_max,R2_I_MCP_min,120); % MCP Hinge to DIP nut

r2_I_MCP = 15.09/1000;                      % MCP Hinge to MCP Nut

angle_I_MCP_R2_ext = 101.82;    % MCP Extension angle between Y-axis and R2
angle_I_MCP_R2_flx = 35.92;     % MCP Flexion angle between Y-axis and R2
angle_I_MCP_R2 = linspace(angle_I_MCP_R2_ext,angle_I_MCP_R2_flx,120); % Angle between Y-axis and R2 array

angle_I_MCP_r2_ext = 44.08;  % MCP extension angle between Y-Axis and r2
angle_I_MCP_r2_flx = 5.70;   % MCP flexion angle between Y-Axis and r2
angle_I_MCP_r2 = linspace(angle_I_MCP_r2_ext,angle_I_MCP_r2_flx,120); % Angle between Y-axis and r2 array

angle_I_MCP_Dist_F_ext = 3.75;  % MCP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_I_MCP_Dist_F_flx = 124.58; % MCP Flexion angle between Y-axis and Dist_F vector
angle_I_MCP_Dist_F = linspace(angle_I_MCP_Dist_F_ext,angle_I_MCP_Dist_F_flx,120);  % Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_I_MCP = (-Dist_F.*R2_I_MCP.*(cosd(angle_I_MCP_Dist_F).*sind(angle_I_MCP_R2) + sind(angle_I_MCP_Dist_F).*cosd(angle_I_MCP_R2)))./(r2_I_MCP.*cosd(angle_I_MCP_r2));
T_m_I_MCP = F_nut_I_MCP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_I_MCP_mNm = 1000*(T_m_I_MCP);

min_T_m_I_MCP = min(T_m_I_MCP_mNm);
max_T_m_I_MCP = max(T_m_I_MCP_mNm);

%% Motor torque for Middle DIP:

angle_M_DIP_flx = 41.63; % DIP Flexion angle between Y-axis and r
angle_M_DIP_ext = 58.47;  % DIP Extension angle between Y-axis and r
angle_M_DIP = linspace(angle_M_DIP_ext,angle_M_DIP_flx,120); % Angle between Y-axis and line joining DIP hinge to DIP motor.
F_nut_M_DIP = -Dist_F.*tand(angle_M_DIP);
T_m_M_DIP = F_nut_M_DIP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_M_DIP_mNm = 1000*(T_m_M_DIP);
min_T_m_M_DIP = min(T_m_M_DIP_mNm);
max_T_m_M_DIP = max(T_m_M_DIP_mNm);

%% Motor torque for Middle PIP:
R1_M_PIP_min = 54.78/1000;          % PIP Hinge to DIP nut minimum
R1_M_PIP_max = 68.14/1000;       % PIP Hinge to DIP nut maximum
R1_M_PIP = linspace(R1_M_PIP_max,R1_M_PIP_min,120);     % PIP Hinge to DIP nut array

r1_M_PIP = 22.77/1000;           % PIP Hinge to PIP Nut

angle_M_PIP_R1_ext = 83.55;       % PIP Extension angle between Y-axis and R1
angle_M_PIP_R1_flx = 56.11;      % PIP Flexion angle between Y-axis and R1
angle_M_PIP_R1 = linspace(angle_M_PIP_R1_ext,angle_M_PIP_R1_flx,120);  % PIP Angle between Y-axis and R1 array

angle_M_PIP_r1_ext = 56.73;      % PIP Extension angle between Y-axis and r  
angle_M_PIP_r1_flx = 39.67;      % PIP Flexion angle between Y-axis and r
angle_M_PIP_r1 = linspace(angle_M_PIP_r1_ext,angle_M_PIP_r1_flx,120); % PIP Angle between Y-axis and r1 array

angle_M_PIP_Dist_F_ext = 3.78;  % PIP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_M_PIP_Dist_F_flx = 69.08; % PIP Flexion angle between Y-axis and Dist_F vector
angle_M_PIP_Dist_F = linspace(angle_M_PIP_Dist_F_ext,angle_M_PIP_Dist_F_flx,120);  % PIP Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_M_PIP = (-Dist_F.*R1_M_PIP.*(cosd(angle_M_PIP_Dist_F).*sind(angle_M_PIP_R1) + sind(angle_M_PIP_Dist_F).*cosd(angle_M_PIP_R1)))./(r1_M_PIP.*cosd(angle_M_PIP_r1));
T_m_M_PIP = F_nut_M_PIP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_M_PIP_mNm = 1000.*T_m_M_PIP;

min_T_m_M_PIP = min(T_m_M_PIP_mNm);
max_T_m_M_PIP = max(T_m_M_PIP_mNm);

%% Motor torque for Middle MCP:
R2_M_MCP_min = 77.75/1000;
R2_M_MCP_max = 110.15/1000;
R2_M_MCP = linspace(R2_M_MCP_max,R2_M_MCP_min,120); % MCP Hinge to DIP nut

r2_M_MCP = 14.97/1000;                      % MCP Hinge to MCP Nut

angle_M_MCP_R2_ext = 94.92;    % MCP Extension angle between Y-axis and R2
angle_M_MCP_R2_flx = 26.95;     % MCP Flexion angle between Y-axis and R2
angle_M_MCP_R2 = linspace(angle_M_MCP_R2_ext,angle_M_MCP_R2_flx,120); % Angle between Y-axis and R2 array

angle_M_MCP_r2_ext = 44.23;  % MCP extension angle between Y-Axis and r1
angle_M_MCP_r2_flx = 5.40;   % MCP flexion angle between Y-Axis and r1
angle_M_MCP_r2 = linspace(angle_M_MCP_r2_ext,angle_M_MCP_r2_flx,120); % Angle between Y-axis and r2 array

angle_M_MCP_Dist_F_ext = 5.53;  % MCP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_M_MCP_Dist_F_flx = 131.86; % MCP Flexion angle between Y-axis and Dist_F vector
angle_M_MCP_Dist_F = linspace(angle_M_MCP_Dist_F_ext,angle_M_MCP_Dist_F_flx,120);  % Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_M_MCP = (-Dist_F.*R2_M_MCP.*(cosd(angle_M_MCP_Dist_F).*sind(angle_M_MCP_R2) + sind(angle_M_MCP_Dist_F).*cosd(angle_M_MCP_R2)))./(r2_M_MCP.*cosd(angle_M_MCP_r2));
T_m_M_MCP = F_nut_M_MCP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_M_MCP_mNm = 1000.*T_m_M_MCP;

min_T_m_M_MCP = min(T_m_M_MCP_mNm);
max_T_m_M_MCP = max(T_m_M_MCP_mNm);

%% Motor torque for Ring DIP:

angle_R_DIP_flx = 42.65; % DIP Flexion angle between Y-axis and r
angle_R_DIP_ext = 58.90;  % DIP Extension angle between Y-axis and r
angle_R_DIP = linspace(angle_R_DIP_ext,angle_R_DIP_flx,120); % Angle between Y-axis and line joining DIP hinge to DIP motor.
F_nut_R_DIP = -Dist_F.*tand(angle_R_DIP);
T_m_R_DIP = F_nut_R_DIP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_R_DIP_mNm = 1000.*T_m_R_DIP;

min_T_m_R_DIP = min(T_m_R_DIP_mNm);
max_T_m_R_DIP = max(T_m_R_DIP_mNm);

%% Motor torque for Ring PIP:
R1_R_PIP_min = 52.07/1000;          % PIP Hinge to DIP nut minimum
R1_R_PIP_max = 66.47/1000;       % PIP Hinge to DIP nut maximum
R1_R_PIP = linspace(R1_R_PIP_max,R1_R_PIP_min,120);     % PIP Hinge to DIP nut array

r1_R_PIP = 21.08/1000;           % PIP Hinge to PIP Nut

angle_R_PIP_R1_ext = 68.37;       % PIP Extension angle between Y-axis and R1
angle_R_PIP_R1_flx = 35.58;      % PIP Flexion angle between Y-axis and R1
angle_R_PIP_R1 = linspace(angle_R_PIP_R1_ext,angle_R_PIP_R1_flx,120);  % PIP Angle between Y-axis and R1 array

angle_R_PIP_r1_ext = 41.46;      % PIP Extension angle between Y-axis and r1 
angle_R_PIP_r1_flx = 18.70;      % PIP Flexion angle between Y-axis and r1
angle_R_PIP_r1 = linspace(angle_R_PIP_r1_ext,angle_R_PIP_r1_flx,120); % PIP Angle between Y-axis and r1 array

angle_R_PIP_Dist_F_ext = 26.38;  % PIP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_R_PIP_Dist_F_flx = 94.38; % PIP Flexion angle between Y-axis and Dist_F vector
angle_R_PIP_Dist_F = linspace(angle_R_PIP_Dist_F_ext,angle_R_PIP_Dist_F_flx,120);  % PIP Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_R_PIP = (-Dist_F.*R1_R_PIP.*(cosd(angle_R_PIP_Dist_F).*sind(angle_R_PIP_R1) + sind(angle_R_PIP_Dist_F).*cosd(angle_R_PIP_R1)))./(r1_R_PIP.*cosd(angle_R_PIP_r1));
T_m_R_PIP = F_nut_R_PIP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_R_PIP_mNm = 1000.*T_m_R_PIP;

min_T_m_R_PIP = min(T_m_R_PIP_mNm);
max_T_m_R_PIP = max(T_m_R_PIP_mNm);

%% Motor torque for Ring MCP:
R2_R_MCP_min = 70.70/1000;
R2_R_MCP_max = 104.06/1000;
R2_R_MCP = linspace(R2_R_MCP_max,R2_R_MCP_min,120); % MCP Hinge to DIP nut

r2_R_MCP = 14.14/1000;                      % MCP Hinge to MCP Nut

angle_R_MCP_R2_ext = 90.00;    % MCP Extension angle between Y-axis and R2
angle_R_MCP_R2_flx = 24.50;     % MCP Flexion angle between Y-axis and R2
angle_R_MCP_R2 = linspace(angle_R_MCP_R2_ext,angle_R_MCP_R2_flx,120); % Angle between Y-axis and R2 array

angle_R_MCP_r2_ext = 45.50;  % MCP extension angle between Y-Axis and r1
angle_R_MCP_r2_flx = 3.48;   % MCP flexion angle between Y-Axis and r1
angle_R_MCP_r2 = linspace(angle_R_MCP_r2_ext,angle_R_MCP_r2_flx,120); % Angle between Y-axis and r2 array

angle_R_MCP_Dist_F_ext = 20.30;  % MCP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_R_MCP_Dist_F_flx = 143.50; % MCP Flexion angle between Y-axis and Dist_F vector
angle_R_MCP_Dist_F = linspace(angle_R_MCP_Dist_F_ext,angle_R_MCP_Dist_F_flx,120);  % Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_R_MCP = (-Dist_F.*R2_R_MCP.*(cosd(angle_R_MCP_Dist_F).*sind(angle_R_MCP_R2) + sind(angle_R_MCP_Dist_F).*cosd(angle_R_MCP_R2)))./(r2_R_MCP.*cosd(angle_R_MCP_r2));
T_m_R_MCP = F_nut_R_MCP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_R_MCP_mNm = 1000.*T_m_R_MCP;

min_T_m_R_MCP = min(T_m_R_MCP_mNm);
max_T_m_R_MCP = max(T_m_R_MCP_mNm);

%% Motor torque for Pinky DIP:

angle_P_DIP_flx = 54.69; % DIP Flexion angle between Y-axis and r
angle_P_DIP_ext = 67.24;  % DIP Extension angle between Y-axis and r
angle_P_DIP = linspace(angle_P_DIP_ext,angle_P_DIP_flx,120); % Angle between Y-axis and line joining DIP hinge to DIP motor.
F_nut_P_DIP = -Dist_F.*tand(angle_P_DIP);
T_m_P_DIP = F_nut_P_DIP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_P_DIP_mNm = 1000.*T_m_P_DIP;

min_T_m_P_DIP = min(T_m_P_DIP_mNm);
max_T_m_P_DIP = max(T_m_P_DIP_mNm);

%% Motor torque for Pinky PIP:
R1_P_PIP_min = 49.77/1000;          % PIP Hinge to DIP nut minimum
R1_P_PIP_max = 65.50/1000;       % PIP Hinge to DIP nut maximum
R1_P_PIP = linspace(R1_P_PIP_max,R1_P_PIP_min,120);     % PIP Hinge to DIP nut array

r1_P_PIP = 20.08/1000;           % PIP Hinge to PIP Nut

angle_P_PIP_R1_ext = 71.47;       % PIP Extension angle between Y-axis and R1
angle_P_PIP_R1_flx = 32.97;      % PIP Flexion angle between Y-axis and R1
angle_P_PIP_R1 = linspace(angle_P_PIP_R1_ext,angle_P_PIP_R1_flx,120);  % PIP Angle between Y-axis and R1 array

angle_P_PIP_r1_ext = 45.12;      % PIP Extension angle between Y-axis and r1 
angle_P_PIP_r1_flx = 22.31;      % PIP Flexion angle between Y-axis and r1
angle_P_PIP_r1 = linspace(angle_P_PIP_r1_ext,angle_P_PIP_r1_flx,120); % PIP Angle between Y-axis and r1 array

angle_P_PIP_Dist_F_ext = 14.93;  % PIP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_P_PIP_Dist_F_flx = 91.40; % PIP Flexion angle between Y-axis and Dist_F vector
angle_P_PIP_Dist_F = linspace(angle_P_PIP_Dist_F_ext,angle_P_PIP_Dist_F_flx,120);  % PIP Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_P_PIP = (-Dist_F.*R1_P_PIP.*(cosd(angle_P_PIP_Dist_F).*sind(angle_P_PIP_R1) + sind(angle_P_PIP_Dist_F).*cosd(angle_P_PIP_R1)))./(r1_P_PIP.*cosd(angle_P_PIP_r1));
T_m_P_PIP = F_nut_P_PIP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_P_PIP_mNm = 1000.*T_m_P_PIP;

min_T_m_P_PIP = min(T_m_P_PIP_mNm);
max_T_m_P_PIP = max(T_m_P_PIP_mNm);

%% Motor torque for Pinky MCP:
R2_P_MCP_min = 67.38/1000;
R2_P_MCP_max = 104.34/1000;
R2_P_MCP = linspace(R2_P_MCP_max,R2_P_MCP_min,120); % MCP Hinge to DIP nut

r2_P_MCP = 14.67/1000;                      % MCP Hinge to MCP Nut

angle_P_MCP_R2_ext = 92.60;    % MCP Extension angle between Y-axis and R2
angle_P_MCP_R2_flx = 25.97;     % MCP Flexion angle between Y-axis and R2
angle_P_MCP_R2 = linspace(angle_P_MCP_R2_ext,angle_P_MCP_R2_flx,120); % Angle between Y-axis and R2 array

angle_P_MCP_r2_ext = 44.74;  % MCP extension angle between Y-Axis and r1
angle_P_MCP_r2_flx = 4.72;   % MCP flexion angle between Y-Axis and r1
angle_P_MCP_r2 = linspace(angle_P_MCP_r2_ext,angle_P_MCP_r2_flx,120); % Angle between Y-axis and r2 array

angle_P_MCP_Dist_F_ext = 7.49;  % MCP Extension angle between Y-axis and Dist_F vector (located on DIP nut)
angle_P_MCP_Dist_F_flx = 138.72; % MCP Flexion angle between Y-axis and Dist_F vector
angle_P_MCP_Dist_F = linspace(angle_P_MCP_Dist_F_ext,angle_P_MCP_Dist_F_flx,120);  % Angle between Y-axis and Dist_F vector (located on DIP nut)

F_nut_P_MCP = (-Dist_F.*R2_P_MCP.*(cosd(angle_P_MCP_Dist_F).*sind(angle_P_MCP_R2) + sind(angle_P_MCP_Dist_F).*cosd(angle_P_MCP_R2)))./(r2_P_MCP.*cosd(angle_P_MCP_r2));
T_m_P_MCP = F_nut_P_MCP.*(lead_screw_dia/2).*tan(beta - alpha);
T_m_P_MCP_mNm = 1000.*T_m_P_MCP;

min_T_m_P_MCP = min(T_m_P_MCP_mNm);
max_T_m_P_MCP = max(T_m_P_MCP_mNm);

%% Tabulation of all the torques:

Joints = ["Index_DIP";"Index_PIP";"Index_MCP";"Middle_DIP";"Middle_PIP";"Middle_MCP";"Ring_DIP";"Ring_PIP";"Ring_MCP";"Pinky_DIP";"Pinky_PIP";"Pinky_MCP"];
Maximum_Torque_mNm = [min_T_m_I_DIP;min_T_m_I_PIP;min_T_m_I_MCP;min_T_m_M_DIP;min_T_m_M_PIP;min_T_m_M_MCP;min_T_m_R_DIP;min_T_m_R_PIP;min_T_m_R_MCP;min_T_m_P_DIP;min_T_m_P_PIP;min_T_m_P_MCP];
Minimum_Torque_mNm = [max_T_m_I_DIP;max_T_m_I_PIP;max_T_m_I_MCP;max_T_m_M_DIP;max_T_m_M_PIP;max_T_m_M_MCP;max_T_m_R_DIP;max_T_m_R_PIP;max_T_m_R_MCP;max_T_m_P_DIP;max_T_m_P_PIP;max_T_m_P_MCP];

Torque_table = table(Joints,Minimum_Torque_mNm,Maximum_Torque_mNm)
