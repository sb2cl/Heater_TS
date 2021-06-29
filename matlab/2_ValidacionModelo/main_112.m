clear all;

data = load('CalEnf112.txt');

u112.t = data(:,1)/(60*1000); % min
u112.u = data(:,2);
u112.y = data(:,3);

data = load('CalEnf184.txt');

u184.t = data(:,1)/(60*1000); % min
u184.u = data(:,2);
u184.y = data(:,3);

a = 1.4/255;
b = 0.03;
T_amb = 29;
T_ini = 27.59;
T_end = 45;
t_espera=17.5;
u = 112;

out_hot = sim('simulador_01');



figure(1);
clf(1);

hold on;
grid on;

plot(u112.t,u112.y);
plot(out_hot.tout,out_hot.T);

ylabel('Temperatura $[^{\circ}C]$','interpreter','latex');
xlabel('Tiempo $[min]$','interpreter','latex');
ylim([20 40]);







