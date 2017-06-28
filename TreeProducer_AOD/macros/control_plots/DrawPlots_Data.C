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
	TH1F *h_pt0 = hmap["Data"];
	TH1F *h_genpt0 = hmap["QCD"];
	TH1F *h_simp_m1 = hmap["SIMP_M1"];

	double max1 = h_pt0->GetBinContent(h_pt0->GetMaximumBin());

	h_pt0->GetXaxis()->SetTitle(x_label);
	h_pt0->SetMaximum(2.5*max1);

	if(SetLOGY){
		canvas->SetLogy();
		h_pt0->SetMinimum(0.00009);
		h_pt0->SetMaximum(15*max1);
	}

	h_genpt0->SetLineColor(kBlue-10);
	h_genpt0->SetFillColor(kBlue-10);
	h_genpt0->GetXaxis()->SetRangeUser(x_min,x_max);
  h_genpt0->Draw("hist");

	h_simp_m1->SetLineColor(2);
	h_simp_m1->Draw("hist same");


	h_pt0->SetLineColor(1);
	h_pt0->SetMarkerColor(1);
	h_pt0->SetMarkerStyle(7);
	h_pt0->Draw("same P");

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



int DrawPlots_Data(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	TFile *fqcd = TFile::Open("Analysis_Plots_QCD_13TeV_test.root");
	TFile *fdata = TFile::Open("Analysis_Plots_Run2016.root");
	TFile *fsignal = TFile::Open("Analysis_Plots_SIMP_13TeV.root");

	const int N_Plots = 11;
	TString histos[N_Plots] = {"pt0","eta","phi","jetcef0", "nch", "dis_pt", "dis_phi", "dis_eta", "dis_chf", "dis_nhf", "dis_nvtx"};

	TString xlabel[N_Plots] = {"p_{T}(GeV)","Jet #eta","Jet #phi", "Chf", "Ch. Multiplicity","p_{T}", "#phi", "#eta", "ChF", "NHF", "VTX" };
	int x_min[N_Plots] = {100, -3, -4, 0, 0,  0, -4, -4, 0, 0, 0 };
	int x_max[N_Plots] = {3000, 3, 4, 2, 100, 3000, 4, 4, 1, 1, 60};

	bool SETLOGY[N_Plots] = {true, false, false, false, false, false, false, false, false, false, false};


	for(int h=0; h<5; h++){
		cout<<histos[h]<<endl;
		TH1F *h_pt0 = (TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT300To500");
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT500To700"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT700To1000"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT1000To1500"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT1500To2000"));
		h_pt0->Add((TH1F*)fqcd->Get("h_"+histos[h]+"_QCD_HT2000ToInf"));

		cout<<"qcd\n";

	  TH1F *h_data = (TH1F*)fdata->Get("h_"+histos[h]+"_Run2016G");
		cout<<"data\n";

		TH1F *h_signal = (TH1F*)fsignal->Get("h_"+histos[h]+"_SIMP_M1");


		map<string, TH1F*> mh_pt0;
		mh_pt0["QCD"] = h_pt0;
		mh_pt0["Data"] = h_data;
		mh_pt0["SIMP_M1"] = h_signal;



		mh_pt0["QCD"]->Scale(7./36);
		mh_pt0["SIMP_M1"]->Scale(7./36);



		TCanvas *canvas_pt  = canvas_h1f("c_"+histos[h], xlabel[h], mh_pt0, x_min[h], x_max[h], SETLOGY[h] );
		canvas_pt->SaveAs("Plots/c_"+histos[h]+".png");
		canvas_pt->SaveAs("Plots/c_"+histos[h]+".pdf");
	}




/*



		TH2F *h_pt0 = (TH2F*)fqcd->Get("h2_pass_chf_QCD_HT300To500");
		h_pt0->Add((TH2F*)fqcd->Get("h2_pass_chf_QCD_HT500To700"));
		h_pt0->Add((TH2F*)fqcd->Get("h2_pass_chf_QCD_HT700To1000"));
		h_pt0->Add((TH2F*)fqcd->Get("h2_pass_chf_QCD_HT1000To1500"));
		h_pt0->Add((TH2F*)fqcd->Get("h2_pass_chf_QCD_HT1500To2000"));
		h_pt0->Add((TH2F*)fqcd->Get("h2_pass_chf_QCD_HT2000ToInf"));
		//h_pt0->RebinX(10);
		//h_pt0->RebinY(10);

		TCanvas *c2 = canvas_data_mc_2d(h_pt0, "PF ChF", "GEN ChF", 200,1500, true);
		c2->SaveAs("Plots/c_chf_genpf.png");
		c2->SaveAs("Plots/c_chf_genpf.pdf");


		TH2F *h_pt = (TH2F*)fqcd->Get("h2_pt_QCD_HT300To500");
		h_pt->Add((TH2F*)fqcd->Get("h2_pt_QCD_HT500To700"));
		h_pt->Add((TH2F*)fqcd->Get("h2_pt_QCD_HT700To1000"));
		h_pt->Add((TH2F*)fqcd->Get("h2_pt_QCD_HT1000To1500"));
		h_pt->Add((TH2F*)fqcd->Get("h2_pt_QCD_HT1500To2000"));
		h_pt->Add((TH2F*)fqcd->Get("h2_pt_QCD_HT2000ToInf"));
		TCanvas *c3 = canvas_data_mc_2d(h_pt, "PF p_{T}", "GEN p_{T}", 200,1500, true);
		c3->SaveAs("Plots/c_pt_genpf.png");
		c3->SaveAs("Plots/c_pt_genpf.pdf");


		TH2F *h_phi = (TH2F*)fqcd->Get("h2_phi_QCD_HT300To500");
		h_phi->Add((TH2F*)fqcd->Get("h2_phi_QCD_HT500To700"));
		h_phi->Add((TH2F*)fqcd->Get("h2_phi_QCD_HT700To1000"));
		h_phi->Add((TH2F*)fqcd->Get("h2_phi_QCD_HT1000To1500"));
		h_phi->Add((TH2F*)fqcd->Get("h2_phi_QCD_HT1500To2000"));
		h_phi->Add((TH2F*)fqcd->Get("h2_phi_QCD_HT2000ToInf"));
		TCanvas *c4 = canvas_data_mc_2d(h_phi, "PF #phi", "GEN #phi", 200,1500, true);
		c3->SaveAs("Plots/c_phi_genpf.png");
		c3->SaveAs("Plots/c_phi_genpf.pdf");


		TH2F *h_eta = (TH2F*)fqcd->Get("h2_eta_QCD_HT300To500");
		h_eta->Add((TH2F*)fqcd->Get("h2_eta_QCD_HT500To700"));
		h_eta->Add((TH2F*)fqcd->Get("h2_eta_QCD_HT700To1000"));
		h_eta->Add((TH2F*)fqcd->Get("h2_eta_QCD_HT1000To1500"));
		h_eta->Add((TH2F*)fqcd->Get("h2_eta_QCD_HT1500To2000"));
		h_eta->Add((TH2F*)fqcd->Get("h2_eta_QCD_HT2000ToInf"));
		TCanvas *c5 = canvas_data_mc_2d(h_eta, "PF #eta", "GEN #eta", 200,1500, true);
		c5->SaveAs("Plots/c_eta_genpf.png");
		c5->SaveAs("Plots/c_eta_genpf.pdf");
*/

	 	//mh_pt0["QCD"]->Scale(1./mh_pt0["QCD"]->Integral());



	return 0;
}
