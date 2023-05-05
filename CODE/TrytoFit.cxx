{
TF1 f1("FitFunc","(x<[1]    ?   [0]*pow(x/[1],-[2])    :  [0]*pow(x/[1],-[3]) )",0.1,100);     //[0] is F0, [1] is Eb, [2] is n1, [3] is n2
f1.SetParameter(1,2.06);
f1.SetParameter(2,-0.41);
f1.SetParameter(3,0.63);
TGraphAsymmErrors* gr = new TGraphAsymmErrors("DATAS.txt");
gr->Fit("FitFunc","R");

TF1 f2("FitFuncCalore","(x<[1]    ?   x*x*[0]*pow(x/[1],-[2])    :  x*x*[0]*pow(x/[1],-[3]) )",0.1,100);     //[0] is F0, [1] is Eb, [2] is n1, [3] is n2
f2.FixParameter(1,2.06);
f2.FixParameter(2,1.42);
f2.FixParameter(3,2.63);
gr->Fit("FitFuncCalore","R");

TF1 f2("LogFunc","log10(exp(1))*exp(-pow(log10(x)-log10([0]),2)/(2*pow([1],2)))/(sqrt(2*3.14)*[1]*x)",1e28,1e34);  
TGraphAsymmErrors* gr2 = new TGraphAsymmErrors("AIC.txt");
f2.SetParameter(1,0.94);
f2.SetParameter(0,4.3*1e32);
gr2->Fit("LogFunc","R");
f2.GetChisquare();   
f2.GetProb();

gPad->SetLogx();
gPad->SetLogy();
gr2->Draw("ALP");
f1.Draw();
}
