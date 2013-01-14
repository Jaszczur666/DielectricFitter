#Notes to myself#
1. What I iplemented is plain gradient descent. It's slow, but at least it's working, but not with alpha parameter;
I'm thinking about rewriting the code to take vector values. It would be easier to implement proper Leveberg-Marquardt method then.
To implement next method I must probably change notation;
2. I think I need to move data storage to some class, and make it global or static;
##Problems to solve before Levenberg-Marquardt method can be implemented##
1. It turns out I need to differentiate derivatives of residuals, not my chi squared function. This isn't good. Jacobi matrix will get large - 42x4 (84x4 actually - function to minimize is complex (i.e. it has non-zero imaginary part)). And I need to calculate Hessian which will be 84x84 and inverse it after applying some minor corrections.
2. Inverting large matrix isn't the best idea ever, but I don't know what else can I do. I lack free time now, but I stiil keep an eye for solution. 
