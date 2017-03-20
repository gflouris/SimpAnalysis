#include "TH1F.h"
#include "TH2I.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TDirectoryFile.h"
#include "TStyle.h"
#include "TString.h"

#include "../classes/SANtuple.h"

#include <iostream>

#include "/user/gflouris/Tools/CMSPlots/tdrstyle.C"
#include "/user/gflouris/Tools/CMSPlots/CMS_lumi.C"

#include <boost/progress.hpp>



TCanvas *canvas_h1f(TString name, TString x_label, map<string, TH1F*> hmap, int x_min, int x_max, bool SetLOGY){

	TCanvas *canvas  = new TCanvas(name,name,1000,800);
	TH1F *h_pt0 = hmap["QCD"];
	TH1F *h_genpt0 = hmap["QCD_GEN"];

	double max1 = h_pt0->GetBinContent(h_pt0->GetMaximumBin());

	h_pt0->GetXaxis()->SetTitle(x_label);
	h_pt0->SetMaximum(2.5*max1);

	if(SetLOGY){
		canvas->SetLogy();
		h_pt0->SetMinimum(0.00009);
		h_pt0->SetMaximum(15*max1);
	}

	h_pt0->SetLineColor(kBlue-10);
	h_pt0->SetFillColor(kBlue-10);
	h_pt0->GetXaxis()->SetRangeUser(x_min,x_max);
	h_pt0->Draw("hist");
  h_genpt0->Draw("same");

	TLegend *leg;
	leg = new TLegend(0.63,0.63,0.90,0.90);
	leg->AddEntry(h_pt0, "QCD Madgraph+Pythia8", "f");

	leg->SetTextFont(42);
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetBorderSize(0);
	leg->Draw();

	// writing the lumi information and the CMS "logo"
  CMS_lumi( canvas, 0, 11 );
	return canvas;

}


int DrawPlots(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	TFile *fqcd = TFile::Open("Analysis_Plots_QCD_13TeV.root");

	const int N_Plots = 5;
	TString histos[N_Plots] = {"pt0","eta","phi","jetcef0", "jetArea0"};

	TString xlabel[N_Plots] = {"p_{T}(GeV)","Jet #eta","Jet #phi", "Chf", "JetArea"};
	int x_min[N_Plots] = {200, -3, -4, 0, 0};
	int x_max[N_Plots] = {3000, 3, 4, 2, 2};

	bool SETLOGY[N_Plots] = {true, false, false, false, false};


	for(int h=0; h<4; h++){

		TH1F *h_pt0 = (TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT300To500");
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT500To700"));
		//TH1F *h_pt0 = (TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT500To700");
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT700To1000"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT1000To1500"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT1500To2000"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT2000ToInf"));


	  TH1F *h_genpt0 = (TH1F*)fqcd->Get("h_gen"+histos[h]+"_QCD_HT300To500");
		h_genpt0->Add((TH1F*)fqcd->Get("h_gen"+histos[h]+"_QCD_HT500To700"));
		//TH1F *h_genpt0 = (TH1F*)fqcd->Get("h_gen"+histos[h]+"_QCD_HT500To700");
		h_genpt0->Add((TH1F*)fqcd->Get("h_gen"+histos[h]+"_QCD_HT700To1000"));
		h_genpt0->Add((TH1F*)fqcd->Get("h_gen"+histos[h]+"_QCD_HT1000To1500"));
		h_genpt0->Add((TH1F*)fqcd->Get("h_gen"+histos[h]+"_QCD_HT1500To2000"));
		h_genpt0->Add((TH1F*)fqcd->Get("h_gen"+histos[h]+"_QCD_HT2000ToInf"));

		map<string, TH1F*> mh_pt0;
		mh_pt0["QCD"] = h_pt0;
		mh_pt0["QCD_GEN"] = h_genpt0;


	 	//mh_pt0["QCD"]->Scale(1./mh_pt0["QCD"]->Integral());



		TCanvas *canvas_pt  = canvas_h1f("c_"+histos[h], xlabel[h], mh_pt0, x_min[h], x_max[h], SETLOGY[h] );
		//canvas_pt->SaveAs("Plots/c_"+histos[h]+".png");
		//canvas_pt->SaveAs("Plots/c_"+histos[h]+".pdf");
	}



	return 0;
}
