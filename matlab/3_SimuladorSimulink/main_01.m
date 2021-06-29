clear all;

%data = load('CalEnf112.txt');

%hot.t = data(:,1)/(60*1000); % min
%hot.u = data(:,2);
%hot.y = data(:,3);

%data = load('CurvaEnfriamiento.txt');

%cold.t = data(:,1)./60./1000; % min
%cold.u = data(:,2);
%cold.y = data(:,3);

Ref=36;
Kp=30;
Ki=10;
a = 1.4/255;
b = 0.03;
T_amb = 29.63;
T_ini = 27.59;
T_end = 45;
u = 112;

out_hot = sim('simulador_Ref');

%a = 1.4/255;
%b = 0.03;
%T_amb = 29.63;
%T_ini = 36.15;
%T_end = 23;
%u = 0;

%out_cold = sim('simulador_01');

figure(1);
clf(1);

hold on;
grid on;

%plot(hot.t,hot.y);
%plot(cold.t,cold.y);
subplot(211);
plot(out_hot.tout,out_hot.Ref);

title('Constante Seguridad 0.1');
hold on;
plot(out_hot.tout,out_hot.T);
%plot(out_cold.tout+19.67,out_cold.T); %retraso enfriamiento de 19 min con respecto al inicio
ylabel('Temperatura $[^{\circ}C]$','interpreter','latex');
xlabel('Tiempo $[min]$','interpreter','latex');
legend('Referencia','Temperatura');
ylim([20 40]);

subplot(212);
plot(out_hot.tout,out_hot.u*(12/255));
ylabel('Accion Control $[V]$','interpreter','latex');
xlabel('Tiempo $[min]$','interpreter','latex');
legend('Acción de control');
ylim([0 15]);






