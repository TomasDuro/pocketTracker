function [J, grad] = costFunctionReg(theta, X, y, lambda)
%Computes the cost and the gradient for logistic regression with regularization

m = length(y); % number of training examples
J = 0;
grad = zeros(size(theta));

sigtX=sigmoid(X*theta);
J=(-y'*log(sigtX)-(1-y)'*log(1-sigtX))/m+(lambda/(2*m))*(sum(theta.^2)-theta(1).^2);
grad=((sigtX-y)'*X)/m;

ALP=X'*(sigtX-y);
grad(2:length(grad))=(ALP(2:end))/m+(lambda/m)*theta(2:length(grad));

end
