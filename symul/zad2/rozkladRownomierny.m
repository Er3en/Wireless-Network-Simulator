clear;
close all;
% % figure(1);
% % A = importdata('generator_rownomierny.txt')';
% % H1=histogram(A,100);
% % xlim([0, 1]);
% % title('Rozkład równomierny')
% % %A = histogram('BinEdges',a,'BinCounts',a);
% % 
% % figure(2);
% % B = importdata('generator_wykladniczy.txt')';
% % histogram(B,100);
% % xlim([0, 12]);
% % title('Rozkład wykładniczy')
% % 
% % figure(3)
% % C = importdata('generator_zero_jedynkowy.txt')';
% % histogram(C,100);
% % xlim([0, 1]);
% % title('Rozkład zero jedynkowy')
% 
% figure(4)
% C = importdata('histogram_srednich_przeplywnosci_uzytkownikow.txt')';
% histogram(C,50);
% xlim([0, 80]);
% title('histogram_srednich_przeplywnosci_uzytkownikow')
% 
% 
% % D1 = importdata('AVERAGE_SYSTEM_BITRATE_1_.txt')';
% % D2 = importdata('AVERAGE_SYSTEM_BITRATE_2_.txt')';
% % D3 = importdata('AVERAGE_SYSTEM_BITRATE_3_.txt')';
% % D4 = importdata('AVERAGE_SYSTEM_BITRATE_4_.txt')';
% % D5 = importdata('AVERAGE_SYSTEM_BITRATE_5_.txt')';
% % D6 = importdata('AVERAGE_SYSTEM_BITRATE_6_.txt')';
% % D7 = importdata('AVERAGE_SYSTEM_BITRATE_7_.txt')';
% % D8 = importdata('AVERAGE_SYSTEM_BITRATE_8_.txt')';
% % D9 = importdata('AVERAGE_SYSTEM_BITRATE_9_.txt')';
% % D10 = importdata('AVERAGE_SYSTEM_BITRATE_10_.txt')';
% 
% 
% Dwynik = (D1+D2+D3+D4+D5+D6+D7+D8+D9+D10)/10;
% dlmwrite('lambda_0_220_1000_wyznaczanie_fazy.txt',Dwynik')
% dlmwrite('lambda_0_215_1000_wyznaczanie_fazy.txt',Dwynik')
% dlmwrite('lambda_0_210_1000_wyznaczanie_fazy.txt',Dwynik')
% dlmwrite('lambda_0_205_1000_wyznaczanie_fazy.txt',Dwynik')
% dlmwrite('lambda_0_2_1000_wyznaczanie_fazy.txt',Dwynik')

% lambda0_220= importdata('lambda_0_220_1000_wyznaczanie_fazy.txt')'
% lambda0_215 = importdata('lambda_0_215_1000_wyznaczanie_fazy.txt')'
% lambda0_210 = importdata('lambda_0_210_1000_wyznaczanie_fazy.txt')'
% lambda0_205 = importdata('lambda_0_205_1000_wyznaczanie_fazy.txt')'
% lambda0_2 = importdata('lambda_0_2_1000_wyznaczanie_fazy.txt')'
% 
% t=0:5:995;
% figure(5)
% plot(t,lambda0_220,'b');
% hold on
% plot(t,lambda0_215,'g');
% hold on
% plot(t,lambda0_210,'r');
% hold on
% plot(t,lambda0_205,'c');
% hold on
% plot(t,lambda0_2,'m');
% hold on
% grid minor
% legend({'lambda = 0.220','lambda = 0.215','lambda = 0.210','lambda = 0.205','lambda = 0.200'},'Location','northwest','NumColumns',2)
% xlabel('Czas symulacji [ms]')
% ylabel('Średnia przepustowość systemu [kb/s]')
% title('Wyznaczenie fazy początkowej')


% figure(6)
% lambda=1.41:0.01:1.5;
% wyznaczenie_lambdy= importdata('Wyznaczanie_lambdy.txt')';
% v_error=[3.049857561	4.530589967	6.781350138	10.7559066	13.31980289	18.02130964	23.15815937	23.47438543	29.81337323	32.2817621]
% h=errorbar(lambda,wyznaczenie_lambdy,v_error)
% 
% D1 = importdata('ŚREDNI_HIS_UŻ1_.txt')';
% D2 = importdata('ŚREDNI_HIS_UŻ2_.txt')';
% D3 = importdata('ŚREDNI_HIS_UŻ3_.txt')';
% D4 = importdata('ŚREDNI_HIS_UŻ4_.txt')';
% D5 = importdata('ŚREDNI_HIS_UŻ5_.txt')';
% D6 = importdata('ŚREDNI_HIS_UŻ6_.txt')';
% D7 = importdata('ŚREDNI_HIS_UŻ7_.txt')';
% D8 = importdata('ŚREDNI_HIS_UŻ8_.txt')';
% D9 = importdata('ŚREDNI_HIS_UŻ9_.txt')';
% D10 = importdata('ŚREDNI_HIS_UŻ10_.txt')';
% 
% Dwynik = ((D1+D2+D3+D4+D5+D6+D7+D8+D9+D10)/10)';
% h = histogram(Dwynik,80)
% 
% %histogram(Dwynik);
% xlim([0, 110]);
% title('Histogram przepływności użytkowników')
% 
% 


% lambda=1.485;
% wyznaczenie_lambdy= 9185.4;
% v_error=[53.41949702]
% errorbar(lambda,wyznaczenie_lambdy,v_error)


t=0.1:0.1:2.1;

S = importdata('AVERAGE_U.txt')';





plot(t,S);
hold on
grid minor
%legend({'lambda = 0.220','lambda = 0.215','lambda = 0.210','lambda = 0.205','lambda = 0.200'},'Location','northwest','NumColumns',2)
xlabel('lambda')
ylabel(' średnia przepływność użytkownika [kb/s]')
title('wykres średniej przepływności w funkcji wartości λ')


