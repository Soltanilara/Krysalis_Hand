%Finger part Volume [cm^3]:
I_DIP = 3.624;
I_PIP = 3.492;
I_MCP = 3.129;
M_DIP = 4.360;
M_PIP = 4.214;
M_MCP = 3.037;
MCP_base_part = 1.387;
R_DIP = 3.955;
R_PIP = 4.090;
R_MCP = 3.339;
P_DIP = 3.645;
P_PIP = 3.595;
P_MCP = 3.020;
% Actuation parts:
motor_plate = 0.342;
lead = 0.06;
hex_nut = 0.007;
lead_screw = 0.024105;
% Choosing SS 316 as our material with 7.98 g/cm^3, mass of hex nut and lead screw is:
SS_density = 7.98; %g/cm^3
mass_hex_nut = SS_density*hex_nut;
mass_lead_screw = SS_density*lead_screw;
% Choosing PLA as our material with 1.24 g/cm^3, mass of each part is:
PLA_density = 1.24; %g/cm^3
mass_parts = PLA_density.*[I_DIP I_PIP I_MCP R_DIP R_PIP R_MCP P_DIP P_PIP P_MCP MCP_base_part motor_plate lead];
motor_mass = 9; % 9g
wires = 3; % g
% Mass per finger:
m_I = (mass_parts(1) + mass_parts(2) + mass_parts(3) + mass_parts(10) + wires + 3*(motor_mass + mass_parts(11) + mass_parts(12) + mass_lead_screw + mass_hex_nut))/1000;
m_R = (mass_parts(4) + mass_parts(5) + mass_parts(6) + mass_parts(10) + wires + 3*(motor_mass + mass_parts(11) + mass_parts(12) + mass_lead_screw + mass_hex_nut))/1000;
m_P = (mass_parts(7) + mass_parts(8) + mass_parts(9) + mass_parts(10) + wires + 3*(motor_mass + mass_parts(11) + mass_parts(12) + mass_lead_screw + mass_hex_nut))/1000;
%Range of motion of each finger:
theta_I = 0.43580871; %rad or 24.97 degrees measuring from vertical y - axis
theta_R = -theta_I; % rad or 24.97 degrees measuring from vertical y - axis
theta_P = -0.6765; % rad or 38.76 degrees
% Radii for each finger:
r_I = (12.72/2)/100; % m
r_R = (13.52/2)/100; % m
r_P = (12.72/2)/100; % m
%Torque requirement for each finger:
g = 9.81; %m/s^2
T_I = m_I*g*r_I*sin(theta_I); % N-m
T_R = m_R*g*r_R*sin(theta_R); % N-m
T_P = m_P*g*r_P*sin(theta_P); % N-m

% Power requirements:
t = 0.75; % sec
W = [theta_I theta_R theta_P]./t; % rad/s
P_I = T_I*W(1); % N-m/s or W
P_R = T_R*W(2); % N-m/s or W
P_P = T_P*W(3); % N-m/s or W

% Teeth Number on different gears:
N_bevel = 12;
N_pinion = 24; % change
N_worm = 1;
N_I =  38;
N_R =N_I;
N_P = 26;

N_GR_I = (N_pinion/N_bevel)*(N_I/N_worm);

f = 0.25; % Coefficient of friction of Tough 1500 resin
lambda = 10; % deg, Lead angle
phi = 20; % deg, Pressure angle
n_I = (cosd(phi) - f*tand(lambda))/((cosd(phi) + f*cotd(lambda))); % Worm efficiency

n_bevel = 0.94; % Bevel Gear Efficiency

T_m_I = T_I/(n_I*n_bevel*N_GR_I);

N_GR_R = (N_pinion/N_bevel)*(N_R/N_worm);
n_R = n_I;

T_m_R = T_R/(n_R*n_bevel*N_GR_R);

N_GR_P = (N_pinion/N_bevel)*(N_P/N_worm);
n_P = n_I;
T_m_P = T_P/(n_R*n_bevel*N_GR_P);

% Total motor torque required for Abduction-Adduction:
T_m = T_m_I + T_m_R + T_m_P