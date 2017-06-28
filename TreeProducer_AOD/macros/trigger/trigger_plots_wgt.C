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
  pt_eff->SetStatisticOption(TEfficiency::kFWilson);
  pt_eff->SetPassedHistogram(data_num,"f");
  pt_eff->SetTotalHistogram(data_den,"f");

  TEfficiency *pt_eff_qcd = new TEfficiency("pt_eff_"+XLabel,"pt_eff_"+XLabel,80,400,800);
  pt_eff_qcd->SetStatisticOption(TEfficiency::kFWilson);
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




TCanvas* effic(TString HLTName,TH1F* data_num_in, TH1F* data_den_in){

  TH1F data_num = *data_num_in;
  TH1F data_den = *data_den_in;

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

  TCanvas *c1 = new TCanvas(name,name,800,600);
  c1->cd();

  TEfficiency *pt_eff = new TEfficiency("pt_eff_"+XLabel,"pt_eff_"+XLabel,80,400,800);
  pt_eff->SetPassedHistogram(data_num,"f");
  pt_eff->SetTotalHistogram(data_den,"f");
  pt_eff->SetTitle(HLTName+"; "+XLabel+"; Efficiency");
  auto graph = pt_eff->CreateGraph();
  graph->GetXaxis()->SetRangeUser(0,1000);
  graph->GetYaxis()->SetRangeUser(0,1.4);
  graph->Draw("AP");


  return c1;
}



int trigger_plots_wgt(){


   TFile *fqcd = TFile::Open("./Efficiency_MC_wgt_pt_test.root");
   TFile *fdata = TFile::Open("./Efficiency_Data_wgt_pt_test.root");


     TCanvas* c_chf01_Dijet430 = effic("HLT_DiCentralPFJet110_CFMax0p1", (TH1F*)fdata->Get("h_chfMax_Efficiency_HLT_170_0p1"), (TH1F*)fdata->Get("h_chfMax_Total_HLT_170_0p1"), (TH1F*)fqcd->Get("h_chfMax_Efficiency_HLT_170_0p1"), (TH1F*)fqcd->Get("h_chfMax_Total_HLT_170_0p1"));
     c_chf01_Dijet430->SaveAs("./Plots/chf_eff_01_wgt.png");
     c_chf01_Dijet430->SaveAs("./Plots/chf_eff_01_wgt.pdf");

     TCanvas* c_pt1_Dijet430 = effic("HLT_DiCentralPFJet110_CFMax0p1 ", (TH1F*)fdata->Get("h_pt1_Efficiency_HLT_170_0p1"), (TH1F*)fdata->Get("h_pt1_Total_HLT_170_0p1"), (TH1F*)fqcd->Get("h_pt1_Efficiency_HLT_170_0p1"), (TH1F*)fqcd->Get("h_pt1_Total_HLT_170_0p1"));
     c_pt1_Dijet430->SaveAs("./Plots/pt_eff_01_wgt.png");
     c_pt1_Dijet430->SaveAs("./Plots/pt_eff_01_wgt.pdf");



    return 0;
}
