{
TF1 f1("FitFunc","(x<[1]    ?   [0]*pow(x/[1],-[2])    :  [0]*pow(x/[1],-[3]) )",0.1,100);     //[0] is F0, [1] is Eb, [2] is n1, [3] is n2
f1.SetParLimits(1,1.8,2.6);
f1.SetParLimits(2,-0.41);
f1.SetParameter(3,0.63);
TGraphAsymmErrors* gr = new TGraphAsymmErrors("DATAS.txt");
gr->Fit("FitFunc","R");

TF1 f2("FitFuncCalore","(x<[1]    ?   x*x*[0]*pow(x/[1],-[2])    :  x*x*[0]*pow(x/[1],-[3]) )",0.1,100);     //[0] is F0, [1] is Eb, [2] is n1, [3] is n2
f2.FixParameter(1,2.06);
f2.FixParameter(2,1.42);
f2.FixParameter(3,2.63);
gr->Fit("FitFuncCalore","R");

TF1 f2("LogFunc","log10(exp(1))*exp(-pow(log10(x)-log10([0]),2)/(2*pow([1],2)))/(sqrt(2*3.14)*[1]*x)",1e28,1e34);  
TF1 f3("LogFuncL","x*log10(exp(1))*exp(-pow(log10(x)-log10([0]),2)/(2*pow([1],2)))/(sqrt(2*3.14)*[1]*x)",1e28,1e34);  
TGraphAsymmErrors* gr2 = new TGraphAsymmErrors("AIC.txt");
f2.SetParameter(1,0.94);
f2.SetParameter(0,4.3*1e30);
f3.SetParameter(1,0.94);
f3.SetParameter(0,4.3*1e30);
gr2->Fit("LogFunc","R");
f2.GetChisquare();   
f2.GetProb();
TGraph* gr3 = new TGraph("GLC.txt");
f2.SetParLimits(1,0.5,1);
f2.SetParLimits(0,0.5e34,1e34);
gr3->Fit("LogFunc","R");
f2.GetProb();
gPad->SetLogx();
gPad->SetLogy();
gr3->Draw();
f2.Draw("SAME");
double Lmin=0;
double Lmax=DBL_MAX;
double Lth=1e34;
f3.Integral(Lmin,Lmax,1e-16);
f2.Integral(Lth,Lmax,1e-16);




gPad->SetLogx();
gPad->SetLogy();
gr2->Draw("ALP");
f1.Draw();
}
