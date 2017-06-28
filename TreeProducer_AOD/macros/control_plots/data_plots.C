#include "../classes/SANtuple.h"
#include "../classes/analysis.C"


Analysis analysis(string inf, string label){

	Analysis data_Run2016B(250.,2.0,2.0);
	for(int f=1; f<200; f++){
	 std::stringstream a;
	 a<<inf;
	 a<<f; a<<".root";
	 data_Run2016B.setFileName((a.str()).c_str());
	}
  data_Run2016B.setLabel(label);
	data_Run2016B.setIsData(true);
	data_Run2016B.producePlots();
  return data_Run2016B;
}

void WritePlots(TFile* outf, Analysis data_Run2016B){
  outf->cd();
  std::map<std::string, TH1F*> plot_data_Run2016B = data_Run2016B.getHistos();
  std::map<std::string, TH2F*> plot2d_data_Run2016B = data_Run2016B.get2DHistos();
  for (std::pair<std::string, TH1F*> element : plot_data_Run2016B) {
  	 TH1F* histo = element.second;
  	 histo->Write();
  }
  for (std::pair<std::string, TH2F*> element : plot2d_data_Run2016B) {
  	 TH2F* histo = element.second;
  	 histo->Write();
  }
}


int data_plots(){




  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

	// Analysis data_Run2016B = analysis("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016B_rereco_AOD/170403_190549/0000/Data_AOD_test_", "Run2016B");
  // Analysis data_Run2016C = analysis("ssrm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016C_rereco_AOD/170403_190623/0000/Data_AOD_test_", "Run2016C");
  // Analysis data_Run2016D = analysis("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016D_rereco_AOD/170403_190657/0000/Data_AOD_test_", "Run2016D");
  // Analysis data_Run2016E = analysis("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016E_rereco_AOD/170403_190730/0000/Data_AOD_test_", "Run2016E");
  //Analysis data_Run2016F = analysis("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016F_rereco_AOD/170403_190806/0000/Data_AOD_test_", "Run2016F");
   Analysis data_Run2016G = analysis("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016G_rereco_AOD/170403_190918/0000/Data_AOD_test_", "Run2016G");
  // Analysis data_Run2016H_v2 = analysis("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016Hv2_rereco_AOD/170403_190951/0000/Data_AOD_test_", "Run2016H_v2");
  //Analysis data_Run2016H_v3 = analysis("srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/isdebruy/JetHT/SIMPs_JetHT_2016Hv3_rereco_AOD/170403_191030/0000/Data_AOD_test_", "Run2016H_v3");

   TFile * file_out = new TFile("Analysis_Plots_Run2016.root", "RECREATE");
  //  WritePlots(file_out, data_Run2016B);
  //  WritePlots(file_out, data_Run2016C);
  //  WritePlots(file_out, data_Run2016D);
  //  WritePlots(file_out, data_Run2016E);
   //WritePlots(file_out, data_Run2016F);
    WritePlots(file_out, data_Run2016G);
  //  WritePlots(file_out, data_Run2016H_v2);
  // WritePlots(file_out, data_Run2016H_v3);

  file_out->Close();

	return 0;
}
