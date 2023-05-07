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

After this we can now simply integrate 
