%% Volume of each part:
% Index Finger (cm^3):
I_DIP = 3.618;
I_PIP = 3.162;
I_MCP = 3.641;
I_Below_MCP = 3.282;

% Middle Finger (cm^3):
M_DIP = 4.914;
M_PIP = 3.621;
M_MCP = 3.031;

% Ring Finger (cm^3):
R_DIP = 4.35;
R_PIP = 3.26;
R_MCP = 2.783;
R_Below_MCP = 3.282;

% Pinky Finger (cm^3):
P_DIP = 4.224;
P_PIP = 2.856;
P_MCP = 2.735;
P_Below_MCP = 3.275;

% Thumb (cm^3):
Th_IP = 3.126;
Th_MCP = 3.794;
Th_CMC = 4.225;

% Finger actuation unit:
Finger_actuation = 12.15; % Motor_leadscrew_Encoder_wires_hexnut (grams)
Motor_holder_knuckle = 0.904; % (cm^3)
Motor_holder_finger = 0.740; % (cm^3)
Lead_for_nut = 0.09; % (cm^3)

%Palm parts (cm^3):
Knuckle_holder = 95.979;
Shaft = 4.191;
Pinion = 0.491;
Thumb_worm = 2.036;


Knuckle_bearing = 2.3; %grams
Feetech_FT90R_Digital_Servo = 9; % grams (Abduction Adduction Servo Motor)
Thumb_motor = 40; % grams

% Wrist (cm^3):
Worm_Gear_Wrist_1 = 4.21;
Below_Palm = 49.683;
Wrist_motor_1_spur_gear = 0.339;
Wrist_1_motor = 27.24; %grams
AUBO_Base = 45.695;
Worm_Gear_Wrist_2 = 4.316;

% Pins (cm^3):
Finger_Pin = 0.04;
Below_MCP_Pin = 0.119;
Thumb_Pin = 0.107;
Wrist_1_Pin = 1.174;
Wrist_2_Pin = 0.433;

%% Densities of materials being used (g/cm^3):
Tough_1500_Density = 1.175; %g/cm^3
Rigid_10K_Density = 1.63; % g/cm^3

%% Mass per finger (grams):

m_I = Tough_1500_Density*(I_DIP + I_PIP + I_MCP + (2*Motor_holder_finger) + Motor_holder_knuckle + (3*Lead_for_nut) + (3*Finger_Pin) + Below_MCP_Pin) + Rigid_10K_Density*I_Below_MCP + (3*Finger_actuation);
m_M = Tough_1500_Density*(M_DIP + M_PIP + M_MCP + (2*Motor_holder_finger) + Motor_holder_knuckle + (3*Lead_for_nut) + (3*Finger_Pin)) + (3*Finger_actuation);
m_R = Tough_1500_Density*(R_DIP + R_PIP + R_MCP + (2*Motor_holder_finger) + Motor_holder_knuckle + (3*Lead_for_nut) + (3*Finger_Pin) + Below_MCP_Pin) + Rigid_10K_Density*R_Below_MCP + (3*Finger_actuation);
m_P = Tough_1500_Density*(P_DIP + P_PIP + P_MCP + (2*Motor_holder_finger) + Motor_holder_knuckle + (3*Lead_for_nut) + (3*Finger_Pin) + Below_MCP_Pin) + Rigid_10K_Density*P_Below_MCP + (3*Finger_actuation);
m_Th = Tough_1500_Density*(Th_IP + Th_MCP + Motor_holder_finger + Motor_holder_knuckle + (2*Lead_for_nut) + Thumb_Pin) + Rigid_10K_Density*(Th_CMC) + (2*Finger_actuation);

% Mass of the Palm (grams):

m_Palm = Tough_1500_Density*Knuckle_holder + Rigid_10K_Density*(Shaft + Pinion + Thumb_worm) + (2*Knuckle_bearing) + Feetech_FT90R_Digital_Servo + Thumb_motor;

% Payload masss (grams):
Payload = 2000;

% Mass of the entire hand:
M_Hand = (m_I + m_M + m_R + m_P + m_Th + m_Palm + Payload)/1000; %kg
g = 9.81; % m/s^2

% Mass of the wrist-1 (Abduction - Adduction Region):

m_wrist_1 = (Tough_1500_Density*(Below_Palm + Wrist_1_Pin) + Rigid_10K_Density*(Wrist_motor_1_spur_gear + Worm_Gear_Wrist_1) + 2*Knuckle_bearing + Wrist_1_motor)/1000; %kg

phi = [-30:0.1:30]; % Desired_abduction-adduction range (degrees)
phi_2 = [-50:0.1:50]; % Desired_flexion-extension range (degrees)

R = 64.12/1000; % Entire Hand radius till CoM (m)
R2 = (64.12+48)/1000; % Entire Hand radius till CoM + radius of the below palm i.e., hinge to hinge distance (m)

T_wrist_abduction = -R.*sind(phi)*M_Hand*g;
figure(1)
plot(phi,1000.*abs(T_wrist_abduction));
title("Wrist radial-ulnar deviation, with payload (Wrist - 1 module)")
xlabel("Radial-Ulnar deviation Range [deg.]");
ylabel("Wrist Torque [mNm]")
grid on;

T_wrist_flexion = -R2.*sind(phi_2).*(M_Hand + m_wrist_1)*g;
figure(2)
plot(phi_2,1000.*abs(T_wrist_flexion));
title("Wrist flexion-extension, with payload (Wrist - 2 module)")
xlabel("Flexion-Extension Range [deg.]");
ylabel("Wrist Torque [mNm]")
grid on;
%% Motor Torque Estimation For Wrist Abduction-Adduction (Wrist - 1):

N_worm_wheel_1 = 40;
N_worm_1 = 1;
N_worm_spur_1 = 24;
N_wrist_1_motor_spur = 12;
N_GR_W1 = (N_worm_spur_1/N_wrist_1_motor_spur)*(N_worm_wheel_1/N_worm_1);

f = 0.25; % Coefficient of friction of Tough 1500 resin
lambda = 6.3621; % deg, Lead angle
phi = 14.5; % deg, Pressure angle
n_W1 = (cosd(phi) - f*tand(lambda))/((cosd(phi) + f*cotd(lambda))); % Worm efficiency

T_m_W1 = max(T_wrist_abduction)/(n_W1*N_GR_W1)

%% Motor Torque Estimation for Wrist Flexion - Extension (Wrist-2):

N_worm_wheel_2 = 60;
N_worm_2 = 1;
N_worm_spur_2 = 24;
N_wrist_2_motor_spur = 12;
N_GR_W2 = (N_worm_spur_2/N_wrist_2_motor_spur)*(N_worm_wheel_2/N_worm_2);
n_W2 = n_W1;
T_m_W2 = max(T_wrist_flexion)/(n_W2*N_GR_W2)

m_wrist_2 = (Tough_1500_Density*(AUBO_Base + (2*Wrist_2_Pin)) + Rigid_10K_Density*(Wrist_motor_1_spur_gear + Worm_Gear_Wrist_2) + 2*Knuckle_bearing + Wrist_1_motor)/1000; %kg


