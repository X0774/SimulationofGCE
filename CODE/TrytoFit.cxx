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

gPad->SetLogx();
gPad->SetLogy();
gr->Draw("ALP");
f1.Draw();
}
