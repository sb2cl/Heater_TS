load CurvaCalentamiento.txt;
t=CurvaCalentamiento(:,1);
y=CurvaCalentamiento(:,3);
u=(CurvaCalentamiento(:,2)/255)*12;

load CurvaEnfriamiento.txt;
t2=CurvaEnfriamiento(:,1);
y2=CurvaEnfriamiento(:,3);
u2=CurvaEnfriamiento(:,2)-1.88235294117647;
systemIdentification;