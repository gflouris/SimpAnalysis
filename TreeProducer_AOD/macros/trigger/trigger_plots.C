#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TDirectoryFile.h"
#include "TDirectory.h"
#include "TCut.h"
#include "TBranch.h"
#include "TString.h"
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include <algorithm>
#include "TH1F.h"
#include "TMath.h"

#include <vector>
#include "TEfficiency.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "../classes/SANtuple.h"


TCanvas* effic(TString HLTName,TH1F* data_num_in, TH1F* data_den_in, TH1F* mc_num_in, TH1F* mc_den_in){

  TH1F data_num = *data_num_in;
  TH1F data_den = *data_den_in;
  TH1F mc_num = *mc_num_in;
  TH1F mc_den = *mc_den_in;

  TString XLabel = "Jet p_{T2}";
  TString name = data_num.GetName();
  cout<<name<<endl;
  int rebin = 2;
  if(name.Contains("chf")) {
    rebin = 5;
    XLabel = "Max ChF";
  }
  data_num.Rebin(rebin);
  data_den.Rebin(rebin);
  mc_num.Rebin(rebin);
  mc_den.Rebin(rebin);

  TCanvas *c1 = new TCanvas(name,name,800,600);
  c1->cd();



  TEfficiency *pt_eff = new TEfficiency("pt_eff_"+XLabel,"pt_eff_"+XLabel,80,400,800);
  pt_eff->SetPassedHistogram(data_num,"f");
  pt_eff->SetTotalHistogram(data_den,"f");

  TEfficiency *pt_eff_qcd = new TEfficiency("pt_eff_"+XLabel,"pt_eff_"+XLabel,80,400,800);
  pt_eff_qcd->SetPassedHistogram(mc_num, "f");
  pt_eff_qcd->SetTotalHistogram(mc_den, "f");


  pt_eff->SetTitle(HLTName+"; "+XLabel+"; Efficiency");
  auto graph = pt_eff->CreateGraph();
  graph->GetXaxis()->SetRangeUser(0,1000);
  graph->GetYaxis()->SetRangeUser(0,1.4);
  graph->Draw("AP");

  auto graphqcd = pt_eff_qcd->CreateGraph();
  graphqcd->SetLineColor(kRed);
  graphqcd->SetMarkerColor(kRed);
  graphqcd->Draw("Psame");

  // TLegend *leg = new TLegend(0.4,0.61,0.88,0.88);
  // mc_num_in->SetLineColor(kRed);
  // // leg->AddEntry(data_num_in, "HLT_Singlejet170_CF / HLT_Dijet430  p_{T,2}>500", "");
  // // leg->AddEntry(data_num_in, " Data", "l");
  // // leg->AddEntry(mc_num_in, " MC", "l");
  // leg->AddEntry(data_num_in, "MC - HLT_Singlejet170_CF / HLT_Dijet170  p_{T,2}>250", "l");
  // leg->AddEntry(mc_num_in, "MC - HLT_Singlejet170_CF / HLT_Dijet430  p_{T,2}>500", "l");
  // leg->SetTextFont(42);
  // leg->SetFillColor(kWhite);
  // leg->SetLineColor(kWhite);
  // leg->SetBorderSize(0);
  // leg->Draw();

  return c1;
}


int trigger_plots(){

   TString Label=  "Data_test";
   TFile *fin = TFile::Open("./ROOTFiles/Efficiency_"+Label+".root");
   //fin->cd();

   TString LabelQCD=  "MC_SIMP";
   TFile *fqcd = TFile::Open("./ROOTFiles/Efficiency_"+LabelQCD+".root");
   //fqcd->cd();

     TCanvas* c_pt330 = effic("HLT_DiCentralPFJet330_CFMax0p5", (TH1F*)fin->Get("h_pt_num_330"), (TH1F*)fin->Get("h_pt_den_330"), (TH1F*)fqcd->Get("h_pt_num_330"), (TH1F*)fqcd->Get("h_pt_den_330"));
     c_pt330->SaveAs("./Plots/pt_eff_05_"+Label+LabelQCD+".png");
     c_pt330->SaveAs("./Plots/pt_eff_05_"+Label+LabelQCD+".pdf");

     TCanvas* c_pt110 = effic("HLT_DiCentralPFJet170_CFMax0p1", (TH1F*)fin->Get("h_pt_num_170_chf1"), (TH1F*)fin->Get("h_pt_num_170_chf1"), (TH1F*)fqcd->Get("h_pt_num_170_chf1"), (TH1F*)fqcd->Get("h_pt_num_170_chf1"));
     c_pt110->SaveAs("./Plots/pt_eff_01_"+Label+LabelQCD+".png");
     c_pt110->SaveAs("./Plots/pt_eff_01_"+Label+LabelQCD+".pdf");

     TCanvas* c_chf01 = effic("HLT_DiCentralPFJet170_CFMax0p1", (TH1F*)fin->Get("h_chf170_num"), (TH1F*)fin->Get("h_chf170_den"), (TH1F*)fqcd->Get("h_chf170_num"), (TH1F*)fqcd->Get("h_chf170_den"));
     c_chf01->SaveAs("./Plots/chf_eff_01_"+Label+LabelQCD+".png");
     c_chf01->SaveAs("./Plots/chf_eff_01_"+Label+LabelQCD+".pdf");

     TCanvas* c_chf05 = effic("HLT_DiCentralPFJet330_CFMax0p5", (TH1F*)fin->Get("h_chf330_num"), (TH1F*)fin->Get("h_chf330_den"), (TH1F*)fqcd->Get("h_chf330_num"), (TH1F*)fqcd->Get("h_chf330_den"));
     c_chf05->SaveAs("./Plots/chf_eff_05_"+Label+LabelQCD+".png");
     c_chf05->SaveAs("./Plots/chf_eff_05_"+Label+LabelQCD+".pdf");

     TCanvas* c_chf01_Dijet430 = effic("HLT_DiCentralPFJet170_CFMax0p1", (TH1F*)fin->Get("h_chf170_Dijet430_num"), (TH1F*)fin->Get("h_chf170_Dijet430_den"), (TH1F*)fqcd->Get("h_chf170_Dijet430_num"), (TH1F*)fqcd->Get("h_chf170_Dijet430_den"));
     c_chf01_Dijet430->SaveAs("./Plots/chf_eff_01_Dijet430_"+Label+LabelQCD+".png");
     c_chf01_Dijet430->SaveAs("./Plots/chf_eff_01_Dijet430_"+Label+LabelQCD+".pdf");

   TCanvas* c_chf_single_mc= effic("HLT_SingleCentralPFJet170_CFMax0p1", (TH1F*)fqcd->Get("h_chf0_HLT_Singlejet170_CF"), (TH1F*)fqcd->Get("h_chf0_HLT_Dijet170"), (TH1F*)fqcd->Get("h_chf0_HLT_Singlejet170_CF_pt500"), (TH1F*)fqcd->Get("h_chf0_HLT_Dijet430_pt500"));
   c_chf_single_mc->SaveAs("./Plots/pt_singlejet_"+LabelQCD+".pdf");
   c_chf_single_mc->SaveAs("./Plots/pt_singlejet_"+LabelQCD+".png");

  //  TCanvas* c_chf_single= effic("HLT_SingleCentralPFJet170_CFMax0p1", (TH1F*)fin->Get("h_chf0_HLT_Singlejet170_CF_pt500"), (TH1F*)fin->Get("h_chf0_HLT_Dijet430_pt500"), (TH1F*)fqcd->Get("h_chf0_HLT_Singlejet170_CF_pt500"), (TH1F*)fqcd->Get("h_chf0_HLT_Dijet430_pt500"));
  // c_chf_single->SaveAs("./Plots/pt_singlejet_"+Label+LabelQCD+"33.png");
  // c_chf_single->SaveAs("./Plots/pt_singlejet_"+Label+LabelQCD+"33.pdf");

    return 0;
}
