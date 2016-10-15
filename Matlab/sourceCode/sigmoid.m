function g = sigmoid(z)
%computes the sigmoid function

g = zeros(size(z));
g=1./(1+exp(-z));

end
