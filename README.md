Dielectric Fitter
=================
Dielectric Fitter will be a tool to fit multiple dielectric spectra, and export fit parameters; There are tools that do that and are quite nice, but this is my way of learning C++;

As of now it fits data with up to three Cole-Cole functions.  
##List of things to implement:##

* Complex Levenberg-Marquardt fitting using Havriliak Negami function, or multiple such functions;
Done for Cole-cole functions - they are better for most crystalline solids anyway. Proper Havriliak Negami code must be constrained one - and this is still not implemented;
* Constructing Arrhenius graph, and fitting it to retrieve activation energy; (Construction works now, but fitting needs some concept work - there doesn't need to be just one activation energy - for example for systems with phase transitions. I have to think out some neat way to choose limits)
* Same with Vogel-Fulcher plot;
* Some form of weighting
* logarithmic least squares
* conductivity
