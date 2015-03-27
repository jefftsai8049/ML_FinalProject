c = [-5:1:14]'; %20
gamma = [-15:1:2]'; %18
%gamma = gamma(:,ones(20,1))
data = reshape(VarName2,18,20);
data2 = reshape(VarName3,18,20);
%ribbon(gamma,data,0.5)
figure(1)

%zlabel('Accuracy');
contourf(c,gamma,data,8);
xlabel('C (power of 2)');
ylabel('Gamma (power of 2)');


figure(2);
mesh(c,gamma,data2);
xlabel('C (power of 2)');
ylabel('Gamma (power of 2)');
zlabel('Time (msec)');

timeMean_noPCA = mean(mean(data2))


data3 = reshape(VarName5,18,20);
data4 = reshape(VarName6,18,20);
%ribbon(gamma,data,0.5)

figure(3)
%zlabel('Accuracy');
contourf(c,gamma,data3,8,'ShowText','on');
xlabel('C (power of 2)');
ylabel('Gamma (power of 2)');


figure(4);
mesh(c,gamma,data4);
xlabel('C (power of 2)');
ylabel('Gamma (power of 2)');
zlabel('Time (msec)');

timeMean_PCA = mean(mean(data4))
