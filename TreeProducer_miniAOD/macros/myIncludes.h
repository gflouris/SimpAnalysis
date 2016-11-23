#ifndef MYINCLUDES
#define MYINCLUDES

// includes //
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <utility>
//
#include "TPaveText.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraph.h"
#include "TString.h"
#include "TCut.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TEntryList.h"
#include "TMath.h"
#include <TSelector.h>
#include "TEfficiency.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "TVirtualFitter.h"
//
#include "tdrstyle.h"

// namespaces //
using namespace std;

// structures //
struct STEP{
  double  T; // threshold
  TString c; // collection
  TString n; // name  of the type of step
  TString t; // title of the type of step
  //TString f; // filter name

  Int_t   C; // color
  Int_t   S; // style
  
  double pt;
  double phi;
  bool   pass;
  bool   serial;
};

struct PATH{
  TString nameP;
  TString namePath;
  UInt_t nSteps;
  vector<STEP> steps;
};


// Function Declarations //

// style
Int_t setStyle(TEfficiency* f, Int_t color, Int_t style);
Int_t setStyle(TH1* h, Int_t color);
Int_t setStyle(TH1* h, Int_t color, Int_t style, Float_t size, Bool_t fill);
Int_t setStyle(TH1* h, Int_t color, Int_t style, Float_t size,
	       Bool_t sumw, Bool_t fill);
Int_t setStyle(TF1*  f, Int_t color, Int_t style);
Int_t setStyle(TCanvas* c);
Int_t setStyle(TLegend* leg);

// json files
std::map<int, std::vector<std::pair<int, int> > > 
  readJSONFile(const std::string& inFileName);
std::map<int, std::vector<std::pair<int, int> > >
  readJSONFile(TString inFileName);
bool AcceptEventByRunAndLumiSection(const int& runId, const int& lumiId,
                                    std::map<int, std::vector<std::pair<int, int> > >& jsonMap);

// maths
Double_t ApproxErf(Double_t arg);
Double_t PowerLaw(double *x, double *par);
Double_t DoublePowerLaw(double *x, double *par);
Double_t PowerLawOffset(double *x, double *par);
Double_t Sigmoid(double *x, double *par);
Double_t ErfCB(double *x, double *par);
Double_t dichotomy(double eff, double a0, double b0, double relErr,
		   TF1 f, bool verbose);
Double_t QuadSum(Double_t x, Double_t y);
Double_t ErrorRatio(Double_t a, Double_t b, Double_t aErr, Double_t bErr);
Double_t DoubleCB(Double_t *xx,Double_t *pp);

// histos
pair<Double_t, Double_t> Integrate(TH1F* h);
pair<Double_t, Double_t> Integrate(TH2F* h);
Int_t CombineErrors(TH1F* hOut, TH1F** hIn, const UInt_t nH);
Int_t QuadSumHistos(TH1F* hOut, TH1F* hRef, TH1F** hIn, const UInt_t nH, Float_t sign);
Int_t SymmetrizeErrors(TH1F* h1, TH1F* h2, TH1F* hNominal);

// root objects
TGraphAsymmErrors* Divide(TEfficiency* t1, TEfficiency* t2, TString name, TString title, TString xtitle);

////////////////
// DEFINITION //
////////////////

Int_t SymmetrizeErrors(TH1F* hUp, TH1F* hDown, TH1F* hNominal)
{

  // Check nBins consistency
  Bool_t error=false;
  UInt_t nBins = hNominal->GetNbinsX();
  if(hUp  ->GetNbinsX()!=(Int_t)nBins) error=true;
  if(hDown->GetNbinsX()!=(Int_t)nBins) error=true;
  if(error) {
    cout << "ERROR: SymmetrizeErrors(): Inconsistent number of bins in input histograms." << endl;
    return -2;
  }

  Float_t y1, y2, y, shift;
  for(UInt_t iB=0 ; iB<nBins+2 ; iB++) {
    y1 = hUp     ->Integral(iB,iB);
    y2 = hDown   ->Integral(iB,iB);
    y  = hNominal->Integral(iB,iB);

    shift = TMath::Max( TMath::Abs(y1-y) , TMath::Abs(y2-y) );

    hUp  ->SetBinContent(iB, y+shift);
    hDown->SetBinContent(iB, y-shift);
  }

  return 0;
}

Int_t QuadSumHistos(TH1F* hOut, TH1F* hRef, TH1F** hIn, const UInt_t nH, Float_t sign)
{

  // Check size
  if(nH==0) {
    cout << "ERROR: Call CombineErrors() with 0 input histograms." << endl;
    return -2;
  }

  // Check nBins consistency
  Bool_t error=false;
  UInt_t nBins = hIn[0]->GetNbinsX();
  for(UInt_t iH=0 ; iH<nH ; iH++) {
    if(hIn[iH]->GetNbinsX()!=(Int_t)nBins) error=true;
  }
  if(hRef->GetNbinsX()!=(Int_t)nBins) error=true;
  if(hOut->GetNbinsX()!=(Int_t)nBins) error=true;
  if(error) {
    cout << "ERROR: Inconsistent number of bins in input histograms." << endl;
    return -2;
  }
  
  // Combine histos
  Float_t binOut;
  for(UInt_t iB=0 ; iB<nBins+2 ; iB++) {
    binOut=0;
    for(UInt_t iH=0 ; iH<nH ; iH++) {
      binOut += TMath::Power( (hIn[iH]->GetBinContent(iB) - hRef->GetBinContent(iB)) ,2);
    }
    binOut = TMath::Sqrt(binOut);
    hOut->SetBinContent(iB, hRef->GetBinContent(iB) + sign*binOut );
  }

  return 0;

}

Int_t CombineErrors(TH1F* hOut, TH1F** hIn, const UInt_t nH)
{

  // Check size
  if(nH==0) {
    cout << "ERROR: Call CombineErrors() with 0 input histograms." << endl;
    return -2;
  }

  // Check nBins consistency
  Bool_t error=false;
  UInt_t nBins = hIn[0]->GetNbinsX();
  for(UInt_t iH=0 ; iH<nH ; iH++) {
    if(hIn[iH]->GetNbinsX()!=(Int_t)nBins) error=true;
  }
  if(hOut->GetNbinsX()!=(Int_t)nBins) error=true;
  if(error) {
    cout << "ERROR: Inconsistent number of bins in input histograms." << endl;
    return -2;
  }
  
  // Combine errors
  Float_t errOut;
  for(UInt_t iB=0 ; iB<nBins ; iB++) {
    errOut=0;
    for(UInt_t iH=0 ; iH<nH ; iH++) {
      errOut += TMath::Power(hIn[iH]->GetBinError(iB),2);
    }
    errOut = TMath::Sqrt(errOut);
    hOut->SetBinError(iB, errOut);
  }

  return 0;
}

TGraphAsymmErrors* Divide(TEfficiency* t1, TEfficiency* t2, 
			  TString name, TString title, TString xtitle)
{

  TH1F* hTot1 = (TH1F*) t1->GetCopyTotalHisto();
  TH1F* hTot2 = (TH1F*) t2->GetCopyTotalHisto();

  const UInt_t nBins1 = hTot1->GetNbinsX() ; 
  const UInt_t nBins2 = hTot2->GetNbinsX() ; 

  if(nBins1!=nBins2) {
    cout << "ERROR: t1 has " << nBins1 
	 << " bins while t2 has " << nBins2 
	 << " bins ! exit..." << endl;
    return 0; // this is a pointer
  }

  if(!t1 || !t2) {
    cout << "ERROR:" ;
    if(!t1) cout << " t1 is missing!";
    if(!t2) cout << " t2 is missing!";
    cout << " exit..." << endl;
    return 0; // this is a pointer
  }

  Double_t eff1, errLow1, errUp1;
  Double_t eff2, errLow2, errUp2;
  Double_t ratio, errLow, errUp;

  Double_t x[nBins1], y[nBins1];
  Double_t exlow[nBins1], exhigh[nBins1];
  Double_t eylow[nBins1], eyhigh[nBins1];

  for(UInt_t iB=1 ; iB<=nBins1 ; iB++) {

    eff1    = t1->GetEfficiency(iB);
    errLow1 = t1->GetEfficiencyErrorLow(iB);
    errUp1  = t1->GetEfficiencyErrorUp(iB);

    eff2    = t2->GetEfficiency(iB);
    errLow2 = t2->GetEfficiencyErrorLow(iB);
    errUp2  = t2->GetEfficiencyErrorUp(iB);

    ratio  = eff2!=0 ? eff1/eff2 : -0.001 ;
    errLow = QuadSum(errLow1, errLow2);
    errUp  = QuadSum(errUp1 , errUp2);

    // fill arrays for TGraphAsymmErrors
    y[iB-1]     = ratio;
    eylow[iB-1] = errLow;
    eyhigh[iB-1]= errUp;

    x[iB-1]     = hTot1->GetBinCenter(iB);
    exlow[iB-1] = x[iB-1] - hTot1->GetBinLowEdge(iB);
    exhigh[iB-1]= hTot1->GetBinLowEdge(iB+1) - x[iB-1];
  }
  
  TGraphAsymmErrors* tg = new TGraphAsymmErrors(nBins1, x, y, exlow, exhigh, eylow, eyhigh); 
  tg->SetNameTitle(name,title);
  tg->GetXaxis()->SetTitle(xtitle);

  return tg;
}

/////////////////////
// IMPLEMENTATIONS //
/////////////////////

pair<Double_t, Double_t> Integrate(TH1F* h) 
{

  if(!h) {
    cout << "ERROR: called Integrate on a NULL histogram pointer... Abort."
	 << endl;
    return make_pair(-888,-777);
  }

  Double_t norm  = h->Integral(0, h->GetNbinsX() + 1);
  Double_t ent   = h->GetEntries();
  Double_t error = ent>0 ? TMath::Sqrt(ent) * (norm/ent) : -999;

  return make_pair(norm,error);
}

pair<Double_t, Double_t> Integrate(TH2F* h) 
{

  if(!h) {
    cout << "ERROR: called Integrate on a NULL histogram pointer... Abort."
	 << endl;
    return make_pair(-888,-777);
  }

  Double_t norm  = h->Integral(0, h->GetNbinsX() + 1, 0, h->GetNbinsY() + 1);
  Double_t ent   = h->GetEntries();
  Double_t error = ent>0 ? TMath::Sqrt(ent) * (norm/ent) : -999;

  return make_pair(norm,error);
}

Int_t setStyle(TF1* f, Int_t color, Int_t style)
{
  f->SetLineColor(  color);
  f->SetMarkerColor(color);
  f->SetMarkerStyle(style);
  return 0;
}

Int_t setStyle(TEfficiency* f, Int_t color, Int_t style)
{
  f->SetLineColor(  color);
  f->SetMarkerColor(color);
  f->SetMarkerStyle(style);
  return 0;
}

Int_t setStyle(TH1* h, Int_t color, Int_t style, Float_t size,
	       Bool_t sumw, Bool_t fill)
{
  if(sumw) h->Sumw2();
  h->SetMarkerSize(size);
  h->SetMarkerStyle(style);
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  if(fill) h->SetFillColor(color);
  return 0;
}

Int_t setStyle(TH1* h, Int_t color, Int_t style, Float_t size, Bool_t fill)
{

  h->SetMarkerSize(size);
  h->SetMarkerStyle(style);
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  if(fill) h->SetFillColor(color);
  return 0;
}

Int_t setStyle(TH1* h, Int_t color)
{
  h->Sumw2();
  h->SetMarkerSize(0.5);
  h->SetMarkerStyle(kPlus);
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->SetFillColor(color);
  return 0;
}

Int_t setStyle(TCanvas* c)
{
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  return 0;
}

Int_t setStyle(TLegend* leg)
{
  leg->SetLineColor(1);
  leg->SetTextColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.0244755);
  leg->SetShadowColor(kWhite);
  leg->SetFillColor(kWhite);  
  
  return 0;
}

std::map<int, std::vector<std::pair<int, int> > >
readJSONFile(const std::string& inFileName)
{
  std::ifstream inFile(inFileName.c_str(), std::ios::in);
  
  std::string line;
  while(!inFile.eof())
    {
      std::string buffer;
      inFile >> buffer;
      line += buffer;
    }
  
  
  
  // define map with result
  std::map<int, std::vector<std::pair<int, int> > > jsonMap;
    
  
  
  // loop on JSON file
  for(std::string::const_iterator it = line.begin(); it < line.end(); ++it)
    {
      // find run number
      if( (*(it) == '"') && (*(it+7) == '"') )   
	{
	  std::string run(it+1, it+7);
	  //std::cout << "found run " << run << std::endl;
      
      
      
	  // find lumi sections
	  std::vector<std::pair<int, int> > lumisections;
	  for(std::string::const_iterator it2 = it+10; it2 < line.end(); ++it2)
	    {
	      if( (*(it2) == ']') && (*(it2-1) == ']') ) break;
	      if( *(it2) != '[' ) continue;
        
	      std::string::const_iterator it_beg = it2;
	      std::string::const_iterator it_mid;
	      std::string::const_iterator it_end;
        
	      for(std::string::const_iterator it3 = it_beg; it3 < line.end(); ++it3)
		{
		  if( *(it3) == ',' ) it_mid = it3;
		  if( *(it3) == ']' )
		    {
		      it_end = it3;
		      break;
		    }
		}
            
            
            
	      std::string lumi_beg(it_beg+1, it_mid);
	      std::string lumi_end(it_mid+1, it_end);
	      //std::cout << "[" << lumi_beg;
	      //std::cout << ",";
	      //std::cout << lumi_end << "]" << std::endl;
        
	      std::pair<int, int> tempLS(atoi(lumi_beg.c_str()), atoi(lumi_end.c_str()));
	      lumisections.push_back(tempLS);
        
	      it2 = it_end;
	    }
      
      
	  jsonMap[atoi(run.c_str())] = lumisections;
	} // find run number
    
    } // loop on JSON file
  
  
  
  return jsonMap;
}


std::map<int, std::vector<std::pair<int, int> > >
readJSONFile(TString inFileName)
{
  string input = inFileName.Data();
  return readJSONFile(input);
}


bool AcceptEventByRunAndLumiSection(const int& runId, const int& lumiId,
                                    std::map<int, std::vector<std::pair<int, int> > >& jsonMap)
{
  // select by runId
  if( jsonMap.find(runId) == jsonMap.end() ) return false;
  
  
  
  // select by lumiId
  std::vector<std::pair<int, int> > lumisections = jsonMap[runId];
  
  int skipEvent = true;
  for(unsigned int i = 0; i < lumisections.size(); ++i)
    if( (lumiId >= lumisections.at(i).first) &&
        (lumiId <= lumisections.at(i).second) )
      skipEvent = false;
  
  if( skipEvent == true ) return false;
  
  
  return true;
}

Double_t ErfCB(double *x, double *par)
{ 
  double m = x[0];
  double m0 = par[0];
  double sigma = par[1];
  double alpha = par[2];
  double n = par[3];
  double norm = par[4];
  
  const double sqrtPiOver2 = 1.2533141373; // sqrt(pi/2)
  const double sqrt2 = 1.4142135624;

  Double_t sig = fabs((Double_t) sigma);
  Double_t t = (m - m0)/sig ;
  
  if (alpha < 0)
    t = -t;

  Double_t absAlpha = fabs(alpha / sig);
  Double_t a = TMath::Power(n/absAlpha,n)*exp(-0.5*absAlpha*absAlpha);
  Double_t b = absAlpha - n/absAlpha;

  Double_t aireGauche = (1 + ApproxErf( absAlpha / sqrt2 )) * sqrtPiOver2 ;
  Double_t aireDroite = ( a * 1/TMath::Power(absAlpha - b,n-1)) / (n - 1);
  Double_t aire = aireGauche + aireDroite;

  if ( t <= absAlpha ){
    return norm * (1 + ApproxErf( t / sqrt2 )) * sqrtPiOver2 / aire ;
  }
  else{
    return norm * (aireGauche +  a * (1/TMath::Power(t-b,n-1) - 1/TMath::Power(absAlpha - b,n-1)) / (1 - n)) / aire ;
  }
  
} 

Double_t ApproxErf(Double_t arg)
{
  static const double erflim = 5.0;
  if( arg > erflim )
    return 1.0;
  if( arg < -erflim )
    return -1.0;
  
  return TMath::Erf(arg);
}

Double_t PowerLawOffset(double *x, double *par)
{ 
  return par[0] * TMath::Exp(par[1]*x[0]) + par[2];
}

Double_t PowerLaw(double *x, double *par)
{ 
  return par[0] * TMath::Exp(par[1]*x[0]);
}

Double_t DoublePowerLaw(double *x, double *par)
{ 
  return (par[0] * TMath::Exp(par[1]*x[0])) + (par[2] * TMath::Exp(par[3]*x[0]));
}

Double_t Sigmoid(double *x, double *par)
{ 
  return par[2] / (1 + TMath::Exp(-par[1]*(x[0] - par[0])));
} 

Double_t dichotomy(double eff, double a0, double b0, double relErr,
		   TF1 f, bool verbose) 
{
  
  double dicho, effApprox, a, b;
  
  if(a0<b0) {
    a = a0;
    b = b0;
  } else if(a0>b0) {
    a = b0;
    b = a0;
  }
  else {
    cout << "PLEASE CHOOSE DIFFERENT VALUES FOR a AND b" << endl;
    return -999;
  }

  // Test bounds
  if( (f.Eval(a) > eff) || (f.Eval(b) < eff) ) {
    cout << "Bounds not large enough : eff(a)=" << f.Eval(a) 
	 << " ; eff(b)=" << f.Eval(b) << " ; tested eff=" << eff
	 << endl;
    return -999;
  }

  do {
    dicho = (a+b)/2 ;
    effApprox = f.Eval(dicho);

    if( effApprox < eff ) {
      a = dicho;
    } else {
      b = dicho;
    }
  }
  while( (fabs(effApprox-eff) / eff) > relErr );

  if(verbose) {
    cout << "relative precision asked (" << relErr*100 << " %) reached !"
	 << endl
	 << "found value of eT : " << dicho << " GeV" 
	 << endl
      //<< "efficiency value : " << 100*efficiency(dicho,mean,sigma,alpha,n,norm) << " %"
	 << endl;
  }

  return dicho;

}

Double_t QuadSum(Double_t x, Double_t y) 
{
  return TMath::Sqrt( TMath::Power(x,2) + TMath::Power(y,2) );
}

Double_t ErrorRatio(Double_t a, Double_t b, Double_t aErr, Double_t bErr)
{
  if(a==0 || b==0) return -999;
  Double_t ratio = a/b;
  Double_t aRel  = aErr/a;
  Double_t bRel  = bErr/b;
  Double_t abVar = TMath::Power(aRel, 2) + TMath::Power(bRel, 2);
  Double_t var   = (TMath::Power(ratio, 2)) * abVar;
  return TMath::Sqrt( var );
}

Double_t DoubleCB(Double_t *xx,Double_t *pp)
{
  Double_t x   = xx[0];
  // gaussian core
  Double_t N   = pp[0];//norm
  Double_t mu  = pp[1];//mean
  Double_t sig = pp[2];//variance
  // transition parameters
  Double_t a1  = pp[3];
  Double_t p1  = pp[4];
  Double_t a2  = pp[5];
  Double_t p2  = pp[6];
  
  Double_t u   = (x-mu)/sig;
  Double_t A1  = TMath::Power(p1/TMath::Abs(a1),p1)*TMath::Exp(-a1*a1/2);
  Double_t A2  = TMath::Power(p2/TMath::Abs(a2),p2)*TMath::Exp(-a2*a2/2);
  Double_t B1  = p1/TMath::Abs(a1) - TMath::Abs(a1);
  Double_t B2  = p2/TMath::Abs(a2) - TMath::Abs(a2);

  Double_t result(N);
  if      (u<-a1) result *= A1*TMath::Power(B1-u,-p1);
  else if (u<a2)  result *= TMath::Exp(-u*u/2);
  else            result *= A2*TMath::Power(B2+u,-p2);
  return result;
}

#endif