% Thumb pieces volume [cm^3]:
T_IP = 3.5;
T_MCP = 3.5;
T_CMC = 4.5;

% Actuation parts:
motor_holder = 0.342;
lead = 0.06;
hex_nut = 0.007;

% Choosing SS 316 as our material with 7.98 g/cm^3, mass of hex nut and lead screw is:
SS_density = 7.98; %g/cm^3
mass_hex_nut = SS_density*hex_nut;


% Choosing Tough 1500 as our material with 1.175 g/cm^3, mass of each part is:
Tough_density = 1.175; %g/cm^3
mass_parts = Tough_density.*[T_IP T_MCP T_CMC motor_holder lead];
motor_mass = 12; % 9g (Encoder mass + Motor mass + wire mass + Lead screw mass)

% Mass per finger:
m_T = (mass_parts(1) + mass_parts(2) + mass_parts(3) + 2*(motor_mass + mass_parts(4) + mass_parts(5) + mass_hex_nut))/1000;

%Range of motion of each finger:
theta_T = 1.5875515; %rad or xx degrees

% Radii for each finger:
r_T = (13/2)/100; % m

%Torque requirement for each finger:
g = 9.81; %m/s^2
T_T = m_T*g*r_T; % N-m

% Power requirements:
t = 0.5; % sec
W = theta_T/t; % rad/s
P_T = T_T*W; % N-m/s or W

% Teeth Number on different gears:
N_worm_gear_CMC = 18.461;
N_worm = 1;

f = 0.2; % Coefficient of friction of Rigid 10K resin
friction_angle = atand(f);
lambda = 4.7933; % deg, Lead angle
phi = 14.5; % deg, Pressure angle
n_worm = (cosd(phi) - f*tand(lambda))/((cosd(phi) + f*cotd(lambda))); % Worm efficiency

N_GR_T = (N_worm_gear_CMC/N_worm);

T_m_T = T_T/(n_worm*N_GR_T)

