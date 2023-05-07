# SimulationofGCE
Simulation of arxiv: 2112.09699

# Problem:
Read ref. [2112.09699] carefully and try to grasp the main message.
- Reproduce some results about the total GCE flux in sec. 2.2. Notably, fig. 3 results for Calore et al 2015.
- Focus on sec. 4, and on the total number of MSPs, N_GCE
  * Consider the 3 benchmarks luminosity functions: AIC [42], disk [41] and GLC [34], and reproduce fig. 7
  * Reproduce N_GCE for the 3 benchmarks reported in Tab. 1

## (My) Solutions
### Point 1:

In order to correctly fit with the three methods expressed in figure 3 for Calore 2015 we need a fit with asymmetric error bars; as far as I know there is no method in Mathematica which can do this, which means we will need to go back to our ROOTs; with 

`TF1 f1("FitFunc","(x<[1]    ?   [0]*pow(x/[1],-[2])    :  [0]*pow(x/[1],-[3]) )",0.1,100);     //[0] is F0, [1] is Eb, [2] is n1, [3] is n2
TGraphAsymmErrors* gr = new TGraphAsymmErrors("DATAS.txt");
f1.SetParameter(1,2.06);
f1.SetParameter(2,-0.41);
f1.SetParameter(3,0.63);
gr->Fit("FitFunc","R");`

we obtain our Broken power Law Fit with every parameter kept free (I put as initial guesses the Calore 2015 values, but it doesn't really change much), while

`TF1 f2("FitFuncCalore","(x<[1]    ?   x*x*[0]*pow(x/[1],-[2])    :  x*x*[0]*pow(x/[1],-[3]) )",0.1,100);     //[0] is F0, [1] is Eb, [2] is n1, [3] is n2
f2.FixParameter(1,2.06);
f2.FixParameter(2,1.42);
f2.FixParameter(3,2.63);
gr->Fit("FitFuncCalore","R");`

can give us the parametrization with just one parameter free. Notice that for the Calore 2015 Fit we can't use the broken power law given in equation 2.2 and we have to instead refer to equation 5.3 of Calore et al.

After this we can now simply integrate the GCE Power Spectrum over 0.1 and 100 GeV (or 0.1 and 10 GeV) for the two fit functions described above (and also numerically directly on the binned spectrum).

### Point 2.1:
For this point we need to write three different functions; when it comes to GCL and DISK our reference just takes the data from the reference papers while for AIC our reference interpolates directly the function and then normalizes it. Talking about this interpolation, that is described in appendix C (and D, since we need to convert from Flux to Luminosity), doing the same with ROOT leads us to L0=4.3e32 erg/s, which is 2 orders of magnitudes greater than the value given from them! Notice that the value they give does not lead to the right interpolation, but is the value used for figure 7. 

### Point 2.2:
Now it comes the hardest part, which is finding NGCE! I have used both the "simplified" sensitivity model given by them and the "real" sensitivity model, obtaining:


AIC[Standard]: NGCE=3.64e5 

AIC[Simplified]: NGCE=3.62e5, Nr=61.9


GLC[Standard]: NGCE=667

GLC[Simplified]: NGCE=665, Nr=309


DISK[Standard]: NGCE=2.66e4 

DISK[Simplified]: NGCE=2.65e4, Nr=133

