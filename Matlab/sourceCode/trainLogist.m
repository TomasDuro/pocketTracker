function theta = trainLogist(X,y)
%code that uses fminunc to optimize the parameters of the logistic
%regression

[m, n] = size(X);
initial_theta = zeros(n, 1);
% X = [ones(m, 1) X];
% initial_theta = zeros(n + 1, 1);

lambda = 1000;

fprintf('calculating stuff');

options = optimset('Display','iter','GradObj', 'on', 'MaxIter', 10000);
[theta, J, exit_flag] = ...
	fminunc(@(t)(costFunctionReg(t, X, y, lambda)), initial_theta, options);
end