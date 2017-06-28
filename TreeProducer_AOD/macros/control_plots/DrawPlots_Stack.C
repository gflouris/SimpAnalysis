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
#include "THStack.h"

#include "../classes/SANtuple.h"

#include <iostream>

#include "/user/gflouris/Tools/CMSPlots/tdrstyle.C"
#include "/user/gflouris/Tools/CMSPlots/CMS_lumi.C"

#include <boost/progress.hpp>


TCanvas *canvas_h1f(TString name, TString x_label, map<string, TH1F*> hmap, int x_min, int x_max, bool SetLOGY){

	TCanvas *canvas  = new TCanvas(name,name,1000,800);
	TH1F *h_pt0 = hmap["QCD"];
	TH1F *h_wjets = hmap["QCD_GEN"];

	double max1 = h_pt0->GetBinContent(h_pt0->GetMaximumBin());

	h_pt0->GetXaxis()->SetTitle(x_label);
	h_pt0->SetMaximum(2.5*max1);

	if(SetLOGY){
		canvas->SetLogy();
		h_pt0->SetMinimum(0.00009);
		h_pt0->SetMaximum(15*max1);
	}

	h_wjets->SetLineColor(kBlue-10);
	h_wjets->SetFillColor(kBlue-10);
	h_wjets->GetXaxis()->SetRangeUser(x_min,x_max);
  h_wjets->Draw("hist");
	h_pt0->Draw("same");

	// TLegend *leg;
	// leg = new TLegend(0.63,0.63,0.90,0.90);
	// leg->AddEntry(h_pt0, "QCD Madgraph+Pythia8", "f");
	//
	// leg->SetTextFont(42);
	// leg->SetFillColor(kWhite);
	// leg->SetLineColor(kWhite);
	// leg->SetBorderSize(0);
	// leg->Draw();

	// writing the lumi information and the CMS "logo"
  CMS_lumi( canvas, 0, 11 );
	return canvas;

}



TCanvas *canvas_data_mc_2d(TH2F *h_2d, TString xlabel,TString ylabel, int minx, int maxx, bool bline){

    // TLegend *leg;
    // leg = new TLegend(0.18,0.83,0.43,0.90);
    // leg->AddEntry(h_2d,"#font[62]{CMS Internal}", "");
    // leg->AddEntry(h_2d,"Neutron Gun", "");
		//
    // leg->SetTextFont(42);
    // leg->SetFillColor(kWhite);
    // leg->SetLineColor(kWhite);
    // leg->SetBorderSize(0);

    TCanvas *canvas = new TCanvas("canvas"+xlabel,"canvas"+xlabel,700,700);
    canvas->cd();
		//canvas->SetLogz();
    gPad->SetRightMargin(0.15);

    h_2d->GetYaxis()->SetTitle(ylabel);
    h_2d->GetXaxis()->SetTitle(xlabel);
    h_2d->GetXaxis()->SetRangeUser(minx,maxx);
    h_2d->GetYaxis()->SetRangeUser(minx,maxx);

    h_2d->Draw("COLZ");
    //leg->Draw();

    if(bline){
      TLine *l1 = new TLine(200,200,1500,1500);
      l1->SetLineColor(kRed);
      l1->SetLineWidth(2);
      l1->Draw("same");
    }
    return canvas;
}



int DrawPlots_Stack(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	TFile *fqcd = TFile::Open("Analysis_Plots_QCD_13TeV.root");
	TFile *fwjets = TFile::Open("Analysis_Plots_WJets_13TeV.root");

	const int N_Plots = 10;
	TString histos[N_Plots] = {"pt0","eta","phi","jetcef0", "METHT", "dis_phi", "dis_eta", "dis_chf", "dis_nhf", "dis_nvtx"};

	TString xlabel[N_Plots] = {"p_{T}(GeV)","Jet #eta","Jet #phi", "Chf", "#slash{E}_{T}/H_{T}", "#phi", "#eta", "ChF", "NHF", "VTX" };
	int x_min[N_Plots] = {100, -3, -4, 0, 0, -4, -4, 0, 0, 0 };
	int x_max[N_Plots] = {3000, 3, 4, 2, 1, 4, 4, 1, 1, 60};

	bool SETLOGY[N_Plots] = {true, false, false, false, false, false, false, false, false, false};


	for(int h=0; h<5; h++){
		cout<<histos[h]<<endl;
		TH1F *h_pt0 = (TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT300To500");
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT500To700"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT700To1000"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT1000To1500"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT1500To2000"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT2000ToInf"));


	  TH1F *h_wjets = (TH1F*)fwjets->Get("h_"+histos[h]+"_WJetsToQQ");

		TCanvas *canvas = new TCanvas("c_"+histos[h], "c_"+histos[h], 800, 800 );
		canvas->cd();
		canvas->SetLogy();
		h_pt0->SetFillColor(kMagenta-4);
		h_pt0->SetMarkerColor(kMagenta-4);
		h_pt0->GetXaxis()->SetTitle(xlabel[h]);

		h_wjets->SetFillColor(kOrange+6);
		h_wjets->SetMarkerColor(kOrange+6);
    h_wjets->Scale(2.14);
		h_wjets->GetXaxis()->SetTitle(xlabel[h]);

		double max1 = h_pt0->GetBinContent(h_pt0->GetMaximumBin());

		THStack *hs = new THStack("hs"+histos[h],"hs"+histos[h]);
		hs->Add(h_wjets);
		hs->Add(h_pt0);
		hs->SetMinimum(0.9);
		//hs->GetXaxis()->SetTitle("#slash{E}_{T}/#scale[0.7]{#sum} E_{T}");
  //hs->GetHistogram()->GetXaxis()->SetTitle("Reset X title");
		hs->Draw("hist");
		hs->GetXaxis()->SetTitle(xlabel[h]);
		hs->SetMaximum(10.*max1);

		canvas->Modified();

		h_pt0->SetLineColor(kBlack);
		h_pt0->SetMarkerColor(kBlack);
		h_pt0->Draw("same");

		TLegend *leg;
		leg = new TLegend(0.67,0.82,0.95,0.90);
		leg->AddEntry(h_pt0,"QCD", "p");
		leg->AddEntry(h_pt0,"QCD", "f");
		leg->AddEntry(h_wjets,"WJetsToQQ", "f");

		leg->SetTextFont(42);
		leg->SetFillColor(kWhite);
		leg->SetLineColor(kWhite);
		leg->SetBorderSize(0);
		leg->Draw();

		cout<<h_wjets->Integral()<<endl;
		cout<<h_pt0->Integral()<<endl;
		cout<<h_wjets->Integral()/h_pt0->Integral()<<endl;
		// map<string, TH1F*> mh_pt0;
		// mh_pt0["QCD"] = h_pt0;
		// mh_pt0["QCD_GEN"] = h_wjets;
		// TCanvas *canvas_pt  = canvas_h1f("c_"+histos[h], xlabel[h], mh_pt0, x_min[h], x_max[h], SETLOGY[h] );
		 canvas->SaveAs("Plots/c_stack_"+histos[h]+".png");
		 canvas->SaveAs("Plots/c_stack_"+histos[h]+".pdf");
	}




	return 0;
}
